#include "main.h"
#include "pins.h"
#include "led.h"
#include "motor_driver.h"
#include "motor_states.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

static const short BLINK_DELAY_MS = 250;
/*
//handle pin change interrupt for D8 to D13 here
ISR (PCINT2_vect) 
{    
    if //pin 1 or 0 is HIGH
}
*/

volatile bool green_on = false;

ISR (/*PCINT0_vect*/PCINT1_vect) 
{
	if(!(PINC & 0x10)) {
		if(green_on == true) {
			SET_LED_GREEN();
			green_on = false;
		} else {
			CLR_LED_GREEN();
			green_on = true;
		}
	}
	f1();
	_delay_ms(BLINK_DELAY_MS);
	f2();
	_delay_ms(BLINK_DELAY_MS);
	f3();		
	_delay_ms(BLINK_DELAY_MS);
	/*
	if(green_on == true) {
		SET_LED_GREEN();
		green_on = false;
	} else {
		CLR_LED_GREEN();
		green_on = true;
	}*/
	_delay_ms(50);
	//cli();
	//sei();
	PCIFR |= (1 << PCIF1); //clear the flag for this interrupt
	//PCIFR &= ~(1 << PCIF1);
}  

void initialize() 
{
	DDRB = 0x31; 	//set bits 0, 4, and 5 on PORTB as output, clear all others
	//TODO: turn on pull up resistors
	PORTB &= ~0xFF; //disable pull-up resistors for bits 1-3,6,7 and turn off bits 0,4,5

	DDRC &= ~0x3F; 	//set bits 0-5 on PORTC as input
	//TODO: turn on pull up resistors
	PORTC |= 0X3F; //disable pull-up resistors for bits 0-5

	DDRD = 0xFC;	//set bits 2-7 on PORTD as output, clear 0,1 
	//TODO: turn on pull up resistors
	PORTD = 0x00;	//turn off bits 2-7, disable pull-up resistors on pins 0,1



	//PCICR |= 0x07;
	/*
	//so enable PCINT0 interrupt
	PCICR |= (1 << PCIE0); 
	//choose pins for interrupt 
	PCMSK0 = (1<<PCINT0)|(1<<PCINT1); //pins PB0, PB1
	*/

	PCICR |= (1 << PCIE1); //enable interrupts for PORC (analog pins on Arduino)
	PCMSK1 = (1 << PCINT13)|(1 << PCINT12)|(1 << PCINT11); //enable on A3-A5 specifically (PORTC bits 3-5)
	
	sei();			//global enable interrupts

	motor_stop(); //shuts off all motor gates
}

int main() {

	initialize();

	while(1){
		_delay_ms(BLINK_DELAY_MS*4);
		SET_LED_YELLOW();
		_delay_ms(BLINK_DELAY_MS*4);
		CLR_LED_YELLOW();

		//_delay_ms(BLINK_DELAY_MS);
		
		//delay_and_flash_100ms(3);
		/*
		f1();
		_delay_ms(BLINK_DELAY_MS);
		//delay_and_flash_100ms(3);
		f2();
		_delay_ms(BLINK_DELAY_MS);
		//delay_and_flash_100ms(3);
		f3();		
		_delay_ms(BLINK_DELAY_MS);
		//delay_and_flash_100ms(3);SET_LED_GREEN();
		*/
		
	}

	return 0;
}