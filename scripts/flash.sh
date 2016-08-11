DIRECTORY="../build_sh"

avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:$DIRECTORY/main.hex

echo "Done flashing"
