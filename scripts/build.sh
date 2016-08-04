echo "Building"

DIRECTORY="../build"

if [ ! -d "$DIRECTORY" ]; then
	mkdir "$DIRECTORY"
fi

avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o $DIRECTORY/main.o ../main.c
avr-gcc -mmcu=atmega328p $DIRECTORY/main.o -o $DIRECTORY/main.e
avr-objcopy -O ihex -R .eeprom $DIRECTORY/main.e $DIRECTORY/main.hex


#avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o main.o main.c
#avr-gcc -mmcu=atmega328p main.o -o main
#avr-objcopy -O ihex -R .eeprom main main.hex

echo "Done building"
