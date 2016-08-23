#ifndef LED_H
#define LED_H

#include "main.h"

void all_leds_on();
void all_leds_off();

void set_flash_green();
void set_flash_red();
void set_flash_yellow();

void clear_flash_green();
void clear_flash_red();
void clear_flash_yellow();

void delay_and_flash_100ms(uint8_t ms_100);

#endif