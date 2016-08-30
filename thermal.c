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

volatile bool sample_gate_temperatures_flag = false;
volatile uint8_t hottest_adc_reading = 255;

ISR(TIMER2_COMPA_vect)
{
	sample_gate_temperatures_flag = true;
}

void sample_gate_temperatures(){
	static uint8_t thermal_count = 1;

	if(thermal_count >= 5) {
/*
		static uint8_t next_adc0 = 0;
		static uint8_t size_adc0 = 0;
		static uint8_t sum_adc0 = 0;
		static uint8_t ma_values_adc0[MA_MAX_SIZE];
*/
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



/*
		if(adc_to_sample == 0) {
			ADMUX = (ADMUX & 0xF0) | (1 << MUX0);
			adc_to_sample = 1;
		} else if(adc_to_sample == 1) {
			ADMUX = (ADMUX & 0xF0) | (1 << MUX1);
			adc_to_sample = 2;
		} else {
			ADMUX = (ADMUX & 0xF0);
			adc_to_sample = 0;
			hottest_adc_reading = ADCH;
		}
*/
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
	
		thermal_count = 0;
	}
	thermal_count++;
}

ISR(INT1_vect)
{
	motor_stop();
	motor_off = true;
	motor_emergency_stop_flag = true;
	//set_flash_red();
	SET_LED_RED();
	EIFR |= (1 << INTF1);
}