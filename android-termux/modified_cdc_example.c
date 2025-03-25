/*
 * This is a simple example to communicate with a CDC-ACM USB device
 * using libusb.
 *
 * Author: Christophe Augier <christophe.augier@gmail.com>
 */
// NOTE: https://www.silabs.com/documents/public/application-notes/AN758.pdf
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <libusb-1.0/libusb.h>

#define ACM_CTRL_DTR   0x01
#define ACM_CTRL_RTS   0x02

/* We use a global variable to keep the device handle
 */
static struct libusb_device_handle *devh = NULL;

/* The Endpoint address are hard coded. You should use lsusb -v to find
 * the values corresponding to your device.
 */
static int ep_in_addr  = 0x83;
static int ep_out_addr = 0x04; // UNO

int main(int argc, char **argv)
{
    libusb_context * ctx;
    int rc;

    if (argc != 2) {
        fprintf(stderr, "Usage: termux-usb -e %s /dev/bus/usb/00?/00? 3>&1\n", argv[0]);
        exit(1);
    }

    /* Set debugging output to max level.
     */
    libusb_set_debug(NULL, 3);

    /* Initialize libusb
     */
    libusb_set_option(NULL, LIBUSB_OPTION_NO_DEVICE_DISCOVERY);
    rc = libusb_init(&ctx);
    if (rc < 0) {
        fprintf(stderr, "Error initializing libusb: %s\n", libusb_error_name(rc));
        exit(1);
    }

    /* Look for a specific device and open it.
     */
    int fd;
    rc = sscanf(argv[1], "%d", &fd);
    if (rc != 1) {
        fprintf(stderr, "Failed to read fd: %d\n", rc);
        exit(1);
    }
    rc = libusb_wrap_sys_device(ctx, (intptr_t) fd, &devh);
    if (rc != 0) {
        fprintf(stderr, "Failed to wrap fd %d: %s\n", fd, libusb_error_name(rc));
        exit(1);
    }

    for (int if_num = 0; if_num < 2; if_num++) {
        if (libusb_kernel_driver_active(devh, if_num)) {
            libusb_detach_kernel_driver(devh, if_num);
        }
        rc = libusb_claim_interface(devh, if_num);
        if (rc < 0) {
            fprintf(stderr, "Error claiming interface: %s\n",
                    libusb_error_name(rc));
            goto out;
        }
    }

    /* Start configuring the device:
     * - set line state
     */
    rc = libusb_control_transfer(devh, 0x21, 0x22, ACM_CTRL_DTR | ACM_CTRL_RTS,
                                0, NULL, 0, 0);
    if (rc < 0) {
        fprintf(stderr, "Error during control transfer: %s\n",
                libusb_error_name(rc));
        goto out;
    }

    /* - set line encoding: here 9600 8N1
     * 9600 = 0x2580 ~> 0x80, 0x25 in little endian
     */
    unsigned char encoding[] = { 0x80, 0x25, 0x00, 0x00, 0x00, 0x00, 0x08 };
    rc = libusb_control_transfer(devh, 0x21, 0x20, 0, 0, encoding,
                                sizeof(encoding), 0);
    if (rc < 0) {
        fprintf(stderr, "Error during control transfer: %s\n",
                libusb_error_name(rc));
        goto out;
    }

    /* We can now start sending or receiving data to the device
     */
    unsigned char buf[1024];
    int inputlen;

    fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);

    fprintf(stderr, "Connected.\n");

    while(1) {
	inputlen = read(0, buf, sizeof(buf));
        if (inputlen < 0 && errno != EAGAIN) {
            perror("read");
            break;
        }
	if (inputlen > 0) {
	    int outputlen;
	    int rc = libusb_bulk_transfer(devh, ep_out_addr, buf, inputlen, &outputlen, 0);
	    if (rc < 0) {
		fprintf(stderr, "Error sending: %s\n", libusb_error_name(rc));
		break;
	    }
	    if (outputlen < inputlen) {
		fprintf(stderr, "Short send.\n");
		break;
	    }
	}
	int rc = libusb_bulk_transfer(devh, ep_in_addr, buf, sizeof(buf), &inputlen, 200);
	if (rc < 0) {
	    if (rc == LIBUSB_ERROR_TIMEOUT) {
		 continue;
	    }
	    fprintf(stderr, "Error recieving: %s\n", libusb_error_name(rc));
	    break;
	}
	rc = write(3, buf, inputlen);
	if (rc < inputlen) {
	    if (rc < 0) {
                perror("write");
	    } else {
                fprintf(stderr, "Short write to user interface.\n");
	    }
	    break;
	}
    }

    libusb_release_interface(devh, 0);

out:
    if (devh)
            libusb_close(devh);
    libusb_exit(ctx);
    return rc;
}
