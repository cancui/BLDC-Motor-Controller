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
	DDRB |= 0x01 | 0x10 | 0x20; //set bits 0, 4, and 5 on PORTB as output
	DDRD |= 0xFC;				//set bits 7-2 on PORTD as output



	motor_stop(); //shuts off all motor gates
}

int main() {

	initialize();

	while(1){
		/*
		all_leds_on();		
		_delay_ms(BLINK_DELAY_MS);
		all_leds_off();
		_delay_ms(BLINK_DELAY_MS);
		*/
		//delay_and_flash_100ms(3);
		
		f1();
		_delay_ms(BLINK_DELAY_MS);
		//delay_and_flash_100ms(3);
		f2();
		_delay_ms(BLINK_DELAY_MS);
		//delay_and_flash_100ms(3);
		f3();		
		_delay_ms(BLINK_DELAY_MS);
		//delay_and_flash_100ms(3);
		
	}

	return 0;
}