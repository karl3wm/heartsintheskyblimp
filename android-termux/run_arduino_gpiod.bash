DEV="$(termux-usb -l | jq -r .[0])"
if ! termux-usb -e true "$DEV"
then
	echo "Requesting permissions for $DEV . Please confirm on device screen. This will then pause for a long time (insufficiently resolved termux bug)."
	echo "Good time to run ./build_pigpio_termux.bash while waiting."
	termux-usb -r "$DEV"
fi
echo starting
termux-usb -e ./socat_wrapper.bash "$DEV"
