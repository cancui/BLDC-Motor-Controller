CC = avr-gcc
BIN = main.hex
FL = avrdude 

all: $(BIN)

$(BIN): main
	avr-objcopy -O ihex -R .eeprom $* $@

main: main.o 
	$(CC) -mmcu=atmega328p $^ -o $@

main.o: main.c 
	$(CC) -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o $@ $<





clean:
	rm *.o 

flash:
	$(FL) -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:$(BIN)

constLED: led_on.hex
	#$(FL) -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:$<

led_on.hex: $*
	avr-objcopy -O ihex -R .eeprom $* $@

led_on: led_on.o
	$(CC) -mmcu=atmega328p $^ -o $@

led_on.o: led_on.c
	$(CC) -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o $@ $<



