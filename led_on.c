#include <avr/io.h>
#include <util/delay.h>
 
int main() {
 	//set pin 5 of PORTB for output
 	DDRB |= _BV(DDB5);
 
 	//set pin 5 high to turn led on 
 	PORTB |= _BV(PORTB5);

 	return 0;
}