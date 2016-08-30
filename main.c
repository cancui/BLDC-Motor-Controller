//#include "main.h"
#include "pins.h"
#include "led.h"
#include "thermal.h"
#include "motor_driver.h"
#include "motor_states.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

static const uint8_t 	BLINK_DELAY_MS = 15;
static const uint8_t	MAX_TIME_IN_STATE_MS = 10;

#define REPEAT while(true) 

//TODO: Can another interrupt of a different ISR be queued during first interrupt? If no, allow nested interrupts
//TODO: communications (no speed control, but forwards and backwards control)
//TODO: EEPROM settings and logging system
//TODO: Serial
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

	motor_stop(); //shuts off all motor gates

	temperatures_adc0 = new_simple_moving_average(MA_MAX_SIZE);
	temperatures_adc1 = new_simple_moving_average(MA_MAX_SIZE);
	temperatures_adc2 = new_simple_moving_average(MA_MAX_SIZE);

	//Set up ADC
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); //Sets ADC prescaler to 128, so frequency is 125 kHz
	ADMUX |= (1 << REFS0); //Sets ADC reference voltage to AVCC
	ADCSRA |= (1 << ADATE); //Enable auto-trigger, free running mode already enabled
	ADMUX |= (1 << ADLAR); //Reduces precision from 10 to 8 bits from faster reading (only read from ADCH
	ADCSRA |= (1 << ADEN); //Enable ADC
	ADCSRA |= (1 << ADSC); //ADC start conversion

	//Set up INT1 interrupt for severe thermal warning (PD3)
	EICRA &= ~((1 << ISC11)|(1 << ISC10)); //redundant line (low level of PD3 generates interrupt request)
	EIMSK |= (1 << INT1);

	//Set up PCINT1 interrupt for back-EMF sensing from analog comparator
	PCICR |= (1 << PCIE1); //enable interrupts for PORTC (analog pins on Arduino)
	PCMSK1 = (1 << PCINT13)|(1 << PCINT12)|(1 << PCINT11); //enable on A3-A5 specifically (PORTC bits 3-5)

	//LED timer
	TCCR0A |= (1 << WGM01); // Configure timer 0 for CTC mode
	OCR0A = 255; // for LED; delay of ~114 ms after additional delay from the counter in the ISR
	TIMSK0 |= (1 << OCIE0A);  // for LED; Enable CTC interrupt (TIMER0_COMPA_vect)
	TCCR0B |= ((1 << CS02) | (1 << CS00)); // Start timer 0 at Fcpu/1024
	//The value of this timer is stored in TCNT0

	//Thermal timer
	TCCR2A |= (1 << WGM21);
	OCR2A = 250;
	TIMSK2 |= (1 << OCIE2A);
	TCCR2B |= ((1 << CS22) | (1 << CS21) | (1 << CS20)); // Start timer at Fcpu/1024

/*
	//TODO: complete motor state timer implementation
	//Motor state timer
	TCCR1B |= (1 << WGM12); // Configure timer 1 for CTC mode
	OCR1A   = 31; // Set CTC compare value to 500Hz at 16MHz AVR clock, with a prescaler of 1024
	TIMSK1 |= (1 << OCIE1A); // Enable CTC interrupt
	TCCR1B |= ((1 << CS10) | (1 << CS12)); // Start timer at Fcpu/1024
*/
	motor_off = true;
	motor_forwards = true;
	expected_motor_state = 1;

	sei();			//global enable interrupts
}

int main() {

	initialize();

	motor_off = false;

	//set_flash_green();
	//set_flash_red();
	//set_flash_yellow();
	
	startup_f1();

	REPEAT {
		//TOG_LED_YELLOW();
		//_delay_ms(BLINK_DELAY_MS);


		//ACTUAL REPEATED CODE
		if(sample_gate_temperatures_flag) {
			sample_gate_temperatures();
			sample_gate_temperatures_flag = false;
		}

		if(motor_emergency_stop_flag) {
			//take timestamp
			//compare timestamp with last

			//if 
			//SET_LED_RED();

			//while(hottest_adc_reading < high_adc_reading){
			//	bool placefiller = true;
			//}
			//clear_flash_red();
			//motor_emergency_stop_flag = false;

			//Note that lower value means hotter
			if(hottest_adc_reading >= high_adc_reading){
				clear_flash_red();
				CLR_LED_RED();
				motor_emergency_stop_flag = false;
			}
		}
		
	}

	return 0;
}