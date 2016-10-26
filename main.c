#include "pins.h"
#include "led.h"
#include "thermal.h"
#include "motor_driver.h"
#include "motor_states.h"
#include "uart.h"
#include "task_prioritizer.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define REPEAT while(true) 

void initialize() 
{
	//Set up PORTB
	DDRB = 0x3D; 	//set bits 0, 2,3,4, and 5 on PORTB as output, clear all others
	PORTB |= ~0x3D;	//enable pull-up resisors for pins 1, 6-7
	PORTB &= ~0x3D;	//clears bits 0,2,3,4,5

	//Set up PORTC
	DDRC &= ~0x3F; 	//set bits 0-5 on PORTC as input
	PORTC &= ~0x38; //disable pull-up resistors for bits 3-5
	PORTC |= 0x07;	//enable pull-up resistors for bits 0-2

	//Set up PORTD
	DDRD = 0xFC;	//set bits 2-7 on PORTD as output, clear 0,1 
	PORTD |= 0x0F;	//enable pull-up resistors at pins 0,1,2,3
	PORTD &= ~0xF0;	//clear bits 4-7

	//Set up motor driver
	init_motor_driver();

	//Set up thermal monitoring
	init_thermal();

	//Set up UART
	init_UART(UBRR_UART);

	init_task_prioritizer();

	//Task scheduler timer (Used for LED flashing and thermal monitoring)
	TCCR0A |= (1 << WGM01); // Configure timer 0 for CTC mode
	OCR0A = 255; // for LED; delay of ~114 ms after additional delay from the counter in the ISR
	TIMSK0 |= (1 << OCIE0A);  // for LED; Enable CTC interrupt (TIMER0_COMPA_vect)
	TCCR0B |= ((1 << CS02) | (1 << CS00)); // Start timer 0 at Fcpu/1024
	//The value of this timer is stored in TCNT0

	sei();	//global enable interrupts
}

int main() {

	initialize();
	set_flash_green();

	//startup_f1(); //Just during testing

	REPEAT {
		
		if(back_emf_zero_crossing_flag){
			change_motor_state();
			back_emf_zero_crossing_flag = false;
		} else if(!do_task(tasks_high_priority)) {
			do_task(tasks_low_priority);
		}
	}

	return 0;
}

//Schedules the following processes: thermal monitoring, UART send, UART receive, led flashing
ISR(TIMER0_COMPA_vect)
{
	for(uint8_t i = 0; i < tx_queue_length; i++){
		enqueue_task(tasks_low_priority, UART_write);
	}

	if(rx_queue_length > 0){
		enqueue_task(tasks_high_priority, UART_interpret);
	}

	if(rx_overflow_flag){
		UART_enqueue_string("!o"); //string indicating warning from motor stop due to state stagnation 
		//do something about overflow
		rx_overflow_flag = false;
	}
	
	static uint8_t cycle_count = 1;

	if(cycle_count == 2){
		//sample_gate_temperatures_flag = true;
		enqueue_task(tasks_low_priority, sample_gate_temperatures);
	} else if(cycle_count == 4 && motor_emergency_stop_flag == true){
		//schedule check_if_safe_to_restart();
		enqueue_task(tasks_low_priority, check_if_safe_to_restart);
	} else if(cycle_count >= 6){
		//flash_leds_flag = true;
		//cycle_count = 0;
		enqueue_task(tasks_low_priority, flash_leds);
		cycle_count = 0;
	}

	cycle_count++;
}
