#include "main.h"
#include "pins.h"
#include "led.h"
#include "motor_driver.h"
#include "motor_states.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

static const uint8_t 	BLINK_DELAY_MS = 15;
static const uint8_t	MAX_TIME_IN_STATE_MS = 10;

volatile bool		motor_off;
volatile bool 		motor_forwards;
volatile uint8_t	expected_motor_state;

//TODO: remove all delays from ISR
ISR (PCINT1_vect) 
{
	//TODO: check if this is the correct way to do it
	uint8_t PINC_state = PINC;

	//check if motor_off or triggered by high->low
	//TODO: check if there's a more efficient way to do this

	if(motor_off || (!(PINC_state & 0x08) && !(PINC_state & 0x10) && !(PINC_state & 0x20)) ) { 

		//motor_stop();

		TOG_LED_GREEN();
		//toggle_led_green();
		//_delay_ms(100);

		PCIFR |= (1 << PCIF1); //clear the flag for this interrupt

		//TODO: consider else instead of return
		return;
	}

	//toggle_led_red();
	//_delay_ms(100);

	if(motor_forwards) {
		//if f1, check A5 (bit 5)
		if(expected_motor_state == 1 && PINC_state & _BV(5)) {

			f1();
			expected_motor_state = 2;
		} else

		//if f2, check A3 (bit 3)
		if(expected_motor_state == 2 && PINC_state & _BV(3)) {

			f2();
			expected_motor_state = 3;
		} else

		//if f3, check A4 (bit 4)
		if(expected_motor_state == 3 && PINC_state & _BV(4)) {

			f3();
			expected_motor_state = 1;
		}
	} else {
		//if b1, check A5 (bit 5)
		if(expected_motor_state == 1 && PINC_state & _BV(5)) {

			b1();
			expected_motor_state = 2;
		} else

		//if b2, check A4 (bit 4)
		if(expected_motor_state == 2 && PINC_state & _BV(4)) {

			b2();
			expected_motor_state = 3;
		} else

		//if b3, check A3 (bit 3)
		if(expected_motor_state == 3 && PINC_state & _BV(3)) {

			b3();
			expected_motor_state = 1;
		}
	}

	PCIFR |= (1 << PCIF1); //clear the flag for this interrupt

	/*
	static volatile bool teston = true;
	static volatile bool teston2 = true;
	if(teston) {
		SET_LED_RED();
		teston = false;
	}
	else {
		CLR_LED_RED();
		teston = true;
	}
	return;
	if(teston2) {
		SET_LED_GREEN();
		teston2 = false;
	}
	else {
		CLR_LED_GREEN();
		teston2 = true;
	}*/
	
	/*
	static volatile bool green_on = false;

	if(!(PINC & 0x10)) {
		if(green_on == true) {
			SET_LED_GREEN();
			SET_LED_RED();
			green_on = false;
		} else {
			CLR_LED_GREEN();
			CLR_LED_RED();
			green_on = true;
		}
	}
	f1();
	_delay_ms(BLINK_DELAY_MS);
	f2();
	_delay_ms(BLINK_DELAY_MS);
	f3();		
	_delay_ms(BLINK_DELAY_MS);
	motor_stop();
	_delay_ms(BLINK_DELAY_MS);

	PCIFR |= (1 << PCIF1); //clear the flag for this interrupt
	*/
}  

//TODO: Use internal clock, function like systick (to limit time in one motor state)
//TODO: Make some functions inline (line motor states, or pin accessors)
//TODO: implement temperature sensing on MOSFETs
//TODO: SPI communications
void initialize() 
{
	DDRB = 0x31; 	//set bits 0, 4, and 5 on PORTB as output, clear all others
	PORTB |= ~0x31;	//enable pull-up resisors for pins 1-3, 6-7
	PORTB &= ~0x31;	//clears bits 0,4,5

	DDRC &= ~0x3F; 	//set bits 0-5 on PORTC as input
	PORTC &= ~0x3F; //disable pull-up resistors for bits 0-5
	//PORTC |= 0X3F;	//enable pull-up resistors for bits 0-5

	DDRD = 0xFC;	//set bits 2-7 on PORTD as output, clear 0,1 
	PORTD |= ~0xFC;	//enable pull-up resistors at pins 0,1
	PORTD &= ~0xFC;	//clear bits 2,7

	PCICR |= (1 << PCIE1); //enable interrupts for PORC (analog pins on Arduino)
	PCMSK1 = (1 << PCINT13)|(1 << PCINT12)|(1 << PCINT11); //enable on A3-A5 specifically (PORTC bits 3-5)
	
	sei();			//global enable interrupts

	motor_off = true;
	motor_forwards = true;
	expected_motor_state = 1;

	motor_stop(); //shuts off all motor gates
}

int main() {

	initialize();

	motor_off = false;
	motor_forwards = false;

	set_flash_green();
	set_flash_red();
	set_flash_yellow();
	
	while(1){
		//TOG_LED_YELLOW();
		_delay_ms(BLINK_DELAY_MS);

		



		//ACTUAL REPEATED CODE
		//take timestamp
		//if motor is running, compare timestamp with last change
			//if difference is greater than MAX_tiME_IN_STATE_US
				//turn off motor, motor_off = true

		if(motor_state_change_flag == true) {
			//take timestamp
			//compare timestamp with last

			//if 
			TOG_LED_RED();
			motor_state_change_flag = false;
		}
		
	}

	return 0;
}