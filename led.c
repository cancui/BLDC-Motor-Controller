#include "main.h"
#include "led.h"
#include "pins.h"

void led_on(LED_type type)
{
	switch(type) {
		case GREEN:
			pin_set(&LED_GREEN);
		case YELLOW:
			pin_set(&LED_YELLOW);
		case RED:
			pin_set(&LED_RED);
	}
}

void led_off(LED_type type)
{
	switch(type) {
		case GREEN:
			pin_clear(&LED_GREEN);
		case YELLOW:
			pin_clear(&LED_YELLOW);
		case RED:
			pin_clear(&LED_RED);
	}
}

void all_leds_on()
{
	pin_set(&LED_GREEN);
	pin_set(&LED_YELLOW);
	pin_set(&LED_RED);
}

void all_leds_off()
{
	pin_clear(&LED_GREEN);
	pin_clear(&LED_YELLOW);
	pin_clear(&LED_RED);
}

bool led_ison(LED_type type)
{
	switch(type) {
		case GREEN:
			return pin_isset(&LED_GREEN);
		case YELLOW:
			return pin_isset(&LED_YELLOW);
		case RED:
			return pin_isset(&LED_RED);
	}
}