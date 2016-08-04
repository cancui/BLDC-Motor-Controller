echo "Building and flashing LED code"

DIRECTORY="../build"

if [ ! -d "$DIRECTORY" ]; then
	mkdir "$DIRECTORY"
fi

avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o $DIRECTORY/led_on.o ../led_on.c
avr-gcc -mmcu=atmega328p $DIRECTORY/led_on.o -o $DIRECTORY/led_on.e
avr-objcopy -O ihex -R .eeprom $DIRECTORY/led_on.e $DIRECTORY/led_on.hex
avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:$DIRECTORY/led_on.hex

echo "Done"
