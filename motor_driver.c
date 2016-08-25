#include "motor_driver.h"
#include "motor_states.h"
#include "pins.h"
#include "led.h"

//#include <stdbool.h>
//#include <stdint.h>
#include <util/delay.h>
//#include <avr/io.h>
#include <avr/interrupt.h>

void delay_100us(unsigned us) 
{
	while(us--) {
		_delay_ms(0.1);
	}
}

void cycle_f(unsigned us100) 
{
	f1();
	delay_100us(us100);
	f2();
	delay_100us(us100);
	f3();
	delay_100us(us100);
}

void cycle_b(unsigned us100) 
{
	b1();
	delay_100us(us100);
	b2();
	delay_100us(us100);
	b3();
	delay_100us(us100);
}

void simple1()
{
	for(unsigned i = 0; i < 100; i++) {
		cycle_f(30);
	}
}

void startup_f1()
{
	//disable EMF interrupt
	PCICR &= ~(1 << PCIE1); 

	//disable timer interrupt
	TIMSK1 &= ~(1 << OCIE1A); 

	motor_off = false;

	//Startup routine
	for(uint8_t i = 0; i < 3; i++){
		break;
	}
	for(uint8_t i = 0; i < 3; i++){
		break;
	}
	for(uint8_t i = 0; i < 3; i++){
		break;
	}
	for(uint8_t i = 0; i < 3; i++){
		break;
	}

	// Enable CTC interrupt
	TIMSK1 |= (1 << OCIE1A); 
	TCNT1 = 0; 

	//enable EMF interrupt
	PCICR |= (1 << PCIE1); //enable interrupts for PORTC (analog pins on Arduino)
}

volatile bool motor_off = true;//had extern
volatile bool motor_forwards = true; //had extern
volatile uint8_t expected_motor_state = 1;//had extern


ISR(TIMER1_COMPA_vect)
{
	motor_stop();
	if(motor_off) {
		set_flash_red();
		set_flash_green();
	}
}


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
		if(expected_motor_state == 1 && PINC_state & _BV(4)) {

			f1();
			expected_motor_state = 2;
		} else

		//if f2, check A3 (bit 3)
		if(expected_motor_state == 2 && PINC_state & _BV(5)) {

			f2();
			expected_motor_state = 3;
		} else

		//if f3, check A4 (bit 4)
		if(expected_motor_state == 3 && PINC_state & _BV(3)) {

			f3();
			expected_motor_state = 1;
		}
	} else {
		//if b1, check A5 (bit 5)
		if(expected_motor_state == 1 && PINC_state & _BV(3)) {

			b1();
			expected_motor_state = 2;
		} else

		//if b2, check A4 (bit 4)
		if(expected_motor_state == 2 && PINC_state & _BV(5)) {

			b2();
			expected_motor_state = 3;
		} else

		//if b3, check A3 (bit 3)
		if(expected_motor_state == 3 && PINC_state & _BV(4)) {

			b3();
			expected_motor_state = 1;
		}
	}

	PCIFR |= (1 << PCIF1); //clear the flag for this interrupt
}  