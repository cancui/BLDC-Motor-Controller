#include "thermal.h"
#include "led.h"
#include "pins.h"
#include "motor_driver.h"
#include "motor_states.h"
#include "led.h"

#include <avr/interrupt.h>

const uint8_t operational_adc_reading 	= 128; // at ~60C
const uint8_t high_adc_reading 			= 62; // at ~100C
const uint8_t critical_adc_reading 		= 43; // at ~150C

//volatile bool sample_gate_temperatures_flag = false;
//volatile uint8_t hottest_adc_reading = 255;

void init_thermal()
{
	//Allocate buffers for taking a moving average of temperature data
	temperatures_adc0 = new_simple_moving_average(MA_MAX_SIZE);
	temperatures_adc1 = new_simple_moving_average(MA_MAX_SIZE);
	temperatures_adc2 = new_simple_moving_average(MA_MAX_SIZE);

	sample_gate_temperatures_flag = false;
	hottest_adc_reading = 255;

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
}

void sample_gate_temperatures(){

	static uint8_t adc_to_sample = 0;

	uint8_t reading;

	if(adc_to_sample == 0) {
		reading = get_simple_moving_average(temperatures_adc0, ADCH);

		ADMUX = (ADMUX & 0xF0) | (1 << MUX0);
		adc_to_sample = 1;
	} else if(adc_to_sample == 1) {
		reading = get_simple_moving_average(temperatures_adc1, ADCH);

		ADMUX = (ADMUX & 0xF0) | (1 << MUX1);
		adc_to_sample = 2;
	} else {
		reading = get_simple_moving_average(temperatures_adc2, ADCH);

		ADMUX = (ADMUX & 0xF0);
		adc_to_sample = 0;
		hottest_adc_reading = reading;
	}

	if(reading < hottest_adc_reading){
		hottest_adc_reading = reading;
	}

	if(hottest_adc_reading < critical_adc_reading) {
		set_flash_yellow();
	} else if(hottest_adc_reading < high_adc_reading) {
		clear_flash_yellow();
		SET_LED_YELLOW();
	} else {
		clear_flash_yellow();
		CLR_LED_YELLOW();
	}
}

ISR(INT1_vect)
{
	motor_stop();
	motor_off = true;
	motor_emergency_stop_flag = true;
	//set_flash_red();
	SET_LED_RED();
	EIFR |= (1 << INTF1);
	EIMSK &= ~(1 << INT1);
}