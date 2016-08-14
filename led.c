#include "main.h"
#include "led.h"
#include "pins.h"

void all_leds_on()
{
	SET_LED_GREEN();
	SET_LED_RED();
	SET_LED_YELLOW();
}

void all_leds_off()
{
	CLR_LED_GREEN();
	CLR_LED_RED();
	CLR_LED_YELLOW();
}

void delay_and_flash_100ms(uint8_t ms_100)
{
	bool green_status = ISSET_LED_GREEN();
	bool red_status = ISSET_LED_RED();
	bool yellow_status = ISSET_LED_YELLOW();

	while(ms_100--) {
		all_leds_on();
		_delay_ms(50);
		all_leds_off();
		_delay_ms(50);
	}
	
	if(green_status) {
		SET_LED_GREEN();
	} 
	if(red_status) {
		SET_LED_RED();
	}
	if(yellow_status) {
		SET_LED_YELLOW();
	}
}