#include "motor_driver.h"
#include "motor_states.h"
#include "pins.h"
#include "led.h"

//#include <stdbool.h>
//#include <stdint.h>
#include <util/delay.h>
//#include <avr/io.h>
#include <avr/interrupt.h>
/*
volatile bool motor_off = true;//had extern
volatile bool motor_forwards = true; //had extern
volatile uint8_t expected_motor_state = 1;//had extern
volatile bool motor_emergency_stop_flag = false;

volatile bool back_emf_zero_crossing_flag = false;
volatile uint8_t back_emf_PORTC_state = 0x00;
*/

void init_motor_driver()
{
	motor_stop(); //shuts off all motor gates

	motor_off = true;//had extern
	motor_forwards = true; //had extern
	expected_motor_state = 1;//had extern
	motor_emergency_stop_flag = false;

	back_emf_zero_crossing_flag = false;
	back_emf_PORTC_state = 0x00;

	sum_of_time_between_states = new_simple_moving_average(MOTOR_STATE_CYCLES_PER_FULL_ROTATION * 3);

	//Set up PCINT1 interrupt for back-EMF sensing from analog comparator
	PCICR |= (1 << PCIE1); //enable interrupts for PORTC (analog pins on Arduino)
	PCMSK1 = (1 << PCINT13)|(1 << PCINT12)|(1 << PCINT11); //enable on A3-A5 specifically (PORTC bits 3-5)

	/*
	//Motor state timer
	TCCR1B |= (1 << WGM12); // Configure timer 1 for CTC mode
	OCR1A   = 155; // Set CTC compare value to 100Hz at 16MHz AVR clock, with a prescaler of 1024
	TIMSK1 |= (1 << OCIE1A); // Enable CTC interrupt
	TCCR1B |= ((1 << CS10) | (1 << CS12)); // Start timer at Fcpu/1024
	*/
}

void delay_100us(unsigned us) 
{
	while(us--) {
		_delay_ms(0.1);
	}
}

//in 100's of microseconds, to provide greater precision than ms without use of floating-point numbers
void cycle_f(unsigned us100) 
{
	f1();
	delay_100us(us100);
	f2();
	delay_100us(us100);
	f3();
	delay_100us(us100);
}

//in 100's of microseconds, to provide greater precision than ms without use of floating-point numbers
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

const uint8_t cycle_delays1[5] = { 40,30,20,20,20 };

bool startup_f1()
{
	if(motor_emergency_stop_flag) {
		return false;
	}

	//disable EMF interrupt
	PCICR &= ~(1 << PCIE1); 

	//disable timer interrupt
	TIMSK1 &= ~(1 << OCIE1A); 

	//clear_flash_green();

	motor_off = false;
	motor_forwards = true;

	//Startup routine (cli and sei will cause a long delay in periodic interrupts...)
	f1();
	_delay_ms(7);
	f2();
	_delay_ms(6);
	f3();
	_delay_ms(5);
	uint8_t cycles = 0;
	while(!motor_emergency_stop_flag && cycles < 5) {
		cycle_f(cycle_delays1[cycles++]);
	}

	// Enable CTC interrupt
	TIMSK1 |= (1 << OCIE1A); 
	TCNT1 = 0; 

	//enable EMF interrupt
	PCICR |= (1 << PCIE1); //enable interrupts for PORTC (analog pins on Arduino)

	return true;
}

void change_motor_state()
{
	//cli();
	//check if motor_off or triggered by high->low
	//TODO: check if there's a more efficient way to do this
	uint8_t local_back_emf_PORTC_state = back_emf_PORTC_state;

	if(motor_off || motor_emergency_stop_flag || (!(local_back_emf_PORTC_state & 0x08) && !(local_back_emf_PORTC_state & 0x10) && !(local_back_emf_PORTC_state & 0x20)) ) { 

		//motor_stop();

		TOG_LED_GREEN();
		//toggle_led_green();
		//_delay_ms(100);

		PCIFR |= (1 << PCIF1); //clear the flag for this interrupt

		//TODO: consider else instead of return
		return;
	}

	cli();
	get_simple_moving_sum(sum_of_time_between_states, TCNT1);
	sei();
	//toggle_led_red();
	//_delay_ms(100);

	if(motor_forwards) {
		//if f1, check A5 (bit 5)
		if(expected_motor_state == 1 && local_back_emf_PORTC_state & _BV(4)) {

			f1(); 
			//cli();
			expected_motor_state = 2;
		} else

		//if f2, check A3 (bit 3)
		if(expected_motor_state == 2 && local_back_emf_PORTC_state & _BV(5)) {

			f2();
			//cli();
			expected_motor_state = 3;
		} else

		//if f3, check A4 (bit 4)
		if(expected_motor_state == 3 && local_back_emf_PORTC_state & _BV(3)) {

			f3();
			//cli();
			expected_motor_state = 1;
		}
	} else {
		//if b1, check A5 (bit 5)
		if(expected_motor_state == 1 && local_back_emf_PORTC_state & _BV(3)) {

			b1();
			//cli();
			expected_motor_state = 2;
		} else

		//if b2, check A4 (bit 4)
		if(expected_motor_state == 2 && local_back_emf_PORTC_state & _BV(5)) {

			b2();
			//cli();
			expected_motor_state = 3;
		} else

		//if b3, check A3 (bit 3)
		if(expected_motor_state == 3 && local_back_emf_PORTC_state & _BV(4)) {

			b3();
			//cli();
			expected_motor_state = 1;
		}
	}
	//sei();
}


uint16_t get_rotations_per_second()
{
	cli();
	return 15625 / peek_simple_moving_sum(sum_of_time_between_states);	
	sei();
}

ISR(TIMER1_COMPA_vect)
{
	motor_stop();
	if(!motor_off) {
		motor_emergency_stop_flag = true;
		motor_off = true;
		set_flash_green();
	}
}

//TODO: remove all delays from ISR
ISR (PCINT1_vect) 
{
	back_emf_PORTC_state = PINC;
	back_emf_zero_crossing_flag = true;
	
	PCIFR |= (1 << PCIF1); //clear the flag for this interrupt
}  