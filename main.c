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

	//LED timer
	TCCR0A |= (1 << WGM01); // Configure timer 0 for CTC mode
	OCR0A = 255; // delay of ~114 ms after the counter in the ISR
	TIMSK0 |= (1 << OCIE0A);  //Enable CTC interrupt (TIMER0_COMPA_vect)
	TCCR0B |= ((1 << CS02) | (1 << CS00)); // Start timer 0 at Fcpu/1024
	//The value of this timer is stored in TCNT0

	//TODO: complete motor state timer implementation
	//Motor state timer
	TCCR1B |= (1 << WGM12); // Configure timer 1 for CTC mode
	OCR1A   = 1562; // Set CTC compare value to 10Hz at 16MHz AVR clock, with a prescaler of 1024
	TIMSK1 |= (1 << OCIE1A); // Enable CTC interrupt
	TCCR1B |= ((1 << CS10) | (1 << CS12)); // Start timer at Fcpu/1024

	motor_off = true;
	motor_forwards = true;
	expected_motor_state = 1;

	motor_stop(); //shuts off all motor gates

	sei();			//global enable interrupts
}

int main() {

	initialize();

	motor_off = false;
	motor_forwards = false;

	//set_flash_green();
	//set_flash_red();
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