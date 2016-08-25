#include "thermal.h"
#include "led.h"
#include "pins.h"
#include "motor_driver.h"
#include "motor_states.h"
#include "led.h"

#include <avr/interrupt.h>

//TODO: recalculate 8-bit versions of these
const uint8_t operational_adc_reading 	= 128; // at ~60C
const uint8_t high_adc_reading 			= 52; // at ~110C
const uint8_t critical_adc_reading 		= 43; // at ~150C

ISR(TIMER2_COMPA_vect)
{
	static uint8_t thermal_count = 1;

	if(thermal_count >= 5) {
		static uint8_t hottest_reading = 255;
		static uint8_t adc_to_sample = 0;

		if(adc_to_sample == 0) {
			ADMUX = (ADMUX & 0xF0) | (1 << MUX0);
			adc_to_sample = 1;
		} else if(adc_to_sample == 1) {
			ADMUX = (ADMUX & 0xF0) | (1 << MUX1);
			adc_to_sample = 2;
		} else {
			ADMUX = (ADMUX & 0xF0);
			adc_to_sample = 0;
			hottest_reading = 255;
		}

		uint8_t reading = ADCH;
		
		if(reading < hottest_reading){
			hottest_reading = reading;
		}

		if(hottest_reading < critical_adc_reading) {
			set_flash_yellow();
			//CLR_LED_YELLOW();
		} else if(hottest_reading < high_adc_reading) {
			clear_flash_yellow();
			SET_LED_YELLOW();
			//CLR_LED_YELLOW();
		} else {
			clear_flash_yellow();
			//CLR_LED_RED();
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
	//SET_LED_RED();
	set_flash_red();
	//set_flash_yellow();

	EIFR |= (1 << INTF1);
}