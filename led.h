#ifndef LED_H
#define LED_H

#include "main.h"

void led_on(LED_type type); 
void led_off(LED_type type);

void all_leds_on();
void all_leds_off();

LED_status get_led_status(LED_type type);

#endif