#include "main.h"
#include "pins.h"
#include "led.h"
#include "motor_driver.h"
#include "motor_states.h"

#include <avr/io.h>
#include <util/delay.h>

static const short BLINK_DELAY_MS = 300;

void initialize() 
{
	//set bits 0, 4, and 5 on PORTB as output
	DDRB |= 0x01 | 0x10 | 0x20; //_BV(DDB5) | ... ;
	DDRD |= 0xFC;
}

int main() {

	initialize();
	
	while(1){
		/*
		all_leds_on();
		_delay_ms(BLINK_DELAY_MS);
		all_leds_off();
		_delay_ms(BLINK_DELAY_MS);	*/

		b1();
		_delay_ms(BLINK_DELAY_MS);
		b2();
		_delay_ms(BLINK_DELAY_MS);
		b3();		
		_delay_ms(BLINK_DELAY_MS);
	}
	return 0;
}



/*

int main() {
 	//set pin 5 of PORTB for output
 	DDRB |= _BV(DDB5);
 
 	while(1) {
 		//set pin 5 high to turn led on 
 		PORTB |= _BV(PORTB5);
 		_delay_ms(BLINK_DELAY_MS);
 
 		//set pin 5 low to turn led off 
 		PORTB &= ~_BV(PORTB5);
 		_delay_ms(BLINK_DELAY_MS);
 	}

 	return 0;
}
*/