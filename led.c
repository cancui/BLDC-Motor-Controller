//#include "main.h"
#include "led.h"
#include "pins.h"

#include <avr/interrupt.h>
#include <util/delay.h>

void all_leds_on()
{
	cli();
	SET_LED_GREEN();
	SET_LED_RED();
	SET_LED_YELLOW();
	sei();
}

void all_leds_off()
{
	cli();
	CLR_LED_GREEN();
	CLR_LED_RED();
	CLR_LED_YELLOW();
	sei();
}

static bool flash_green = false; 
static bool flash_red = false;
static bool flash_yellow = false;

void set_flash_green()
{
	flash_green = true;
}

void set_flash_red()
{
	flash_red = true;
}

void set_flash_yellow()
{
	flash_yellow = true;
}

void clear_flash_green()
{
	flash_green = false;
}

void clear_flash_red()
{
	flash_red = false;
}

void clear_flash_yellow()
{
	flash_yellow = false;
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

//volatile bool flash_leds_flag = false;

void flash_leds(){
	cli();
	if(flash_green) {
		TOG_LED_GREEN();
	}
	if(flash_red) {
		TOG_LED_RED();
	}
	if(flash_yellow) {
		TOG_LED_YELLOW();
	}
	sei();
}