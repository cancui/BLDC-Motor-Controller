avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o led_on.o led_on.c
avr-gcc -mmcu=atmega328p led_on.o -o led_on
avr-objcopy -O ihex -R .eeprom led_on led_on.hex
avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:led_on.hex

echo "Done"
