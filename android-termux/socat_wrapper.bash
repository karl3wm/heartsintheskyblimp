fd="$1"
socat -x -d4 -lf /dev/stdout EXEC:"./modified_cdc_example '$fd'",fdout=2 TCP-LISTEN:8888,fork
