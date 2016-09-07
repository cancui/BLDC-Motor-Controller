#include "motor_driver.h"
#include "motor_states.h"
#include "pins.h"
#include "led.h"
#include "thermal.h"
#include "uart.h"
#include "task_prioritizer.h"

#include <util/delay.h>
#include <avr/interrupt.h>

#define LONG_MOTOR_TIMER_FOR_TEST

void init_motor_driver()
{
	motor_stop(); //shuts off all motor gates

	motor_off = true;//had extern
	motor_forwards = true; //had extern
	expected_motor_state = 1;//had extern
	motor_emergency_stop_flag = false;

	back_emf_zero_crossing_flag = false;
	back_emf_PORTC_state = 0x00;

	//sum_of_time_between_states = new_simple_moving_average(MOTOR_STATE_CYCLES_PER_FULL_ROTATION * 3);

	//Set up PCINT1 interrupt for back-EMF sensing from analog comparator
	PCICR |= (1 << PCIE1); //enable interrupts for PORTC (analog pins on Arduino)
	PCMSK1 = (1 << PCINT13)|(1 << PCINT12)|(1 << PCINT11); //enable on A3-A5 specifically (PORTC bits 3-5)

	//Motor state timer
	TCCR1B |= (1 << WGM12); // Configure timer 1 for CTC mode
#ifdef LONG_MOTOR_TIMER_FOR_TEST
	OCR1A   = 155 * 200;
#else
	OCR1A   = 155; // Set CTC compare value to 100Hz at 16MHz AVR clock, with a prescaler of 1024
#endif
	TIMSK1 |= (1 << OCIE1A); // Enable CTC interrupt
	TCCR1B |= ((1 << CS10) | (1 << CS12)); // Start timer at Fcpu/1024
	
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

const uint8_t cycle_delays1[5] = { 80,60,40,40,40 };
const uint8_t cycle_delays2[5] = { 120,90,60,60,60 };

bool startup_f1()
{
	if(motor_emergency_stop_flag || (motor_off == false && motor_forwards == false)) {
		return false;
	}

	PCICR &= ~(1 << PCIE1); //disable EMF interrupts (disable all external interrupts on PORTC)

	TIMSK1 &= ~(1 << OCIE1A); //disable motor CTC interrupt

	motor_off = false;
	motor_forwards = true;

	f1();
	_delay_ms(14);
	f2();
	_delay_ms(12);
	f3();
	_delay_ms(10);
	uint8_t cycles = 0;
	
	while(!motor_emergency_stop_flag && cycles < 5) {
		cycle_f(cycle_delays1[cycles++]);
	}

	TIMSK1 |= (1 << OCIE1A); //enable motor CTC interrupt
	TCNT1 = 0; 

	PCICR |= (1 << PCIE1); //enable EMF interrupts

	return true;
}

bool startup_b1()
{
	if(motor_emergency_stop_flag || (motor_off == false && motor_forwards == true)) {
		return false;
	}

	PCICR &= ~(1 << PCIE1); //disable EMF interrupts (disable all external interrupts on PORTC)

	TIMSK1 &= ~(1 << OCIE1A); //disable motor CTC interrupt

	motor_off = false;
	motor_forwards = false;

	b1();
	_delay_ms(14);
	b2();
	_delay_ms(12);
	b3();
	_delay_ms(10);
	uint8_t cycles = 0;

	while(!motor_emergency_stop_flag && cycles < 5) {
		cycle_b(cycle_delays1[cycles++]);
	}

	TIMSK1 |= (1 << OCIE1A); //enable motor CTC interrupt
	TCNT1 = 0; 

	PCICR |= (1 << PCIE1); //enable EMF interrupts

	return true;
}

bool startup_f2()
{
	if(motor_emergency_stop_flag || (motor_off == false && motor_forwards == false)) {
		return false;
	}

	PCICR &= ~(1 << PCIE1); //disable EMF interrupts (disable all external interrupts on PORTC)

	TIMSK1 &= ~(1 << OCIE1A); //disable motor CTC interrupt

	motor_off = false;
	motor_forwards = true;

	f1();
	_delay_ms(20);
	f2();
	_delay_ms(16);
	f3();
	_delay_ms(14);
	uint8_t cycles = 0;
	
	while(!motor_emergency_stop_flag && cycles < 5) {
		cycle_f(cycle_delays2[cycles++]);
	}

	TIMSK1 |= (1 << OCIE1A); //enable motor CTC interrupt
	TCNT1 = 0; 

	PCICR |= (1 << PCIE1); //enable EMF interrupts

	return true;
}

bool startup_b2()
{
	if(motor_emergency_stop_flag || (motor_off == false && motor_forwards == true)) {
		return false;
	}

	PCICR &= ~(1 << PCIE1); //disable EMF interrupts (disable all external interrupts on PORTC)

	TIMSK1 &= ~(1 << OCIE1A); //disable motor CTC interrupt

	motor_off = false;
	motor_forwards = false;

	b1();
	_delay_ms(20);
	b2();
	_delay_ms(16);
	b3();
	_delay_ms(14);
	uint8_t cycles = 0;

	while(!motor_emergency_stop_flag && cycles < 5) {
		cycle_b(cycle_delays2[cycles++]);
	}

	TIMSK1 |= (1 << OCIE1A); //enable motor CTC interrupt
	TCNT1 = 0; 

	PCICR |= (1 << PCIE1); //enable EMF interrupts

	return true;
}

void force_motor_stop()
{
	f1();
	_delay_ms(10);
	b1();
	_delay_ms(10);
	motor_stop();

	motor_off = true;

	PCICR &= ~(1 << PCIE1); //disable EMF interrupt
	TIMSK1 &= ~(1 << OCIE1A); //disable motor CTC interrupt	
}

void change_motor_state()
{
	//TODO: consider state machine implementation
	uint8_t local_back_emf_PORTC_state = back_emf_PORTC_state;

	if(motor_off || motor_emergency_stop_flag || (!(local_back_emf_PORTC_state & 0x08) && !(local_back_emf_PORTC_state & 0x10) && !(local_back_emf_PORTC_state & 0x20)) ) { 
		//PCIFR |= (1 << PCIF1); //clear the flag for this interrupt
		return;
	}

	//get_simple_moving_sum(sum_of_time_between_states, TCNT1);
	
	if(motor_forwards) {
		//if f1, check A5 (bit 5)
		if(expected_motor_state == 1 && local_back_emf_PORTC_state & _BV(4)) {

			f1(); 
			expected_motor_state = 2;
		} else

		//if f2, check A3 (bit 3)
		if(expected_motor_state == 2 && local_back_emf_PORTC_state & _BV(5)) {

			f2();
			expected_motor_state = 3;
		} else

		//if f3, check A4 (bit 4)
		if(expected_motor_state == 3 && local_back_emf_PORTC_state & _BV(3)) {

			f3();
			expected_motor_state = 1;
		}
	} else {
		//if b1, check A5 (bit 5)
		if(expected_motor_state == 1 && local_back_emf_PORTC_state & _BV(3)) {

			b1();
			expected_motor_state = 2;
		} else

		//if b2, check A4 (bit 4)
		if(expected_motor_state == 2 && local_back_emf_PORTC_state & _BV(5)) {

			b2();
			expected_motor_state = 3;
		} else

		//if b3, check A3 (bit 3)
		if(expected_motor_state == 3 && local_back_emf_PORTC_state & _BV(4)) {

			b3();
			expected_motor_state = 1;
		}
	}
	//sei();
}

void check_if_safe_to_restart()
{
	//Note that lower ADC reading means hotter
	if(hottest_adc_reading >= high_adc_reading){
		clear_flash_red();
		CLR_LED_RED();
		motor_emergency_stop_flag = false;
		EIMSK |= (1 << INT1); //turn on interrupt for severe thermal warning again
	}
}

ISR(TIMER1_COMPA_vect)
{
	motor_stop();
	if(!motor_off) {
		motor_emergency_stop_flag = true;
		motor_off = true;
		set_flash_red();
		UART_enqueue_string("!s"); //string indicating warning from motor stop due to state stagnation 
	}
}

ISR (PCINT1_vect) 
{
	back_emf_PORTC_state = PINC; //save the state of the PORTC input pins
	back_emf_zero_crossing_flag = true; //enqueue_task(tasks_high_priority, change_motor_state);
	PCIFR |= (1 << PCIF1); //clear the flag for this interrupt
}  