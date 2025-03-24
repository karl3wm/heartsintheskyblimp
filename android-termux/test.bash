fd="$1"
{ echo -ne '\x01\x00\x00\x00\x04\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'; sleep 60; } | ./modified_cdc_example "$fd" 2>&1| hexdump -v -e '1/1 "%02x\n"' 1>&2
