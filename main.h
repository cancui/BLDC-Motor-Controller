#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>

#include <util/delay.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

typedef enum {
	STATUS_OK = 0,

} Status;

typedef enum {
	GREEN,
	YELLOW,
	RED
} LED_type;

/*
typedef enum {
	LED_OFF = 0,
	LED_ON = 1
} LED_status;
*/

#endif