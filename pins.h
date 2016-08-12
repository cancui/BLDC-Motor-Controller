#ifndef PINS_H
#define PINS_H

#include <stdbool.h>

#include <avr/io.h>
//#include <avr/sfr_defs.h>

/* METHOD 1
#define def #define
#define NL
#define ASSIGN_PIN(name, reg, bit) \
	def SET_##name (PORT##reg |= _(bit)) NL \
	def CLR_##name (PORT##reg &= ~_BV(bit)) NL \
	def ISSET_##name (PIN##reg & _BV(bit)) NL \
	def BIT_##name _BV(bit) NL \
	def BITPOS_##name bit
*/

/* METHOD 2
#define ASSIGN_PIN(name, reg, bit)		\
	void SET_##name() {					\
		PORT##reg |= _BV(bit);			\
	}									\
	void CLR_##name() {					\
		PORT##reg &= ~_BV(bit);			\
	}									\
	bool ISSET_##name() {				\
		return PORT##reg & _BV(bit);	\
	}									\
	uint8_t BITPOS_##name() {			\
		return bit;						\
	}									
	//def BITPOS_##name bit 				

ASSIGN_PIN(LED_GREEN, B, 5)
ASSIGN_PIN(LED_GREEN, B, 4)
ASSIGN_PIN(LED_GREEN, B, 0)
*/

typedef enum {
	//PORT_A,
	PORT_B,
	PORT_C,
	PORT_D
} Port;

typedef struct {
	Port port;
	uint8_t bit;
} Pin;

//define like this:
//const Pin LED_GREEN = { .port = B, .bit = 5 };

void pin_set(const Pin *pin);

void pin_clear(const Pin *pin);

bool pin_isset(const Pin *pin);

uint8_t pin_bitpos(const Pin *pin);

Port pin_port(const Pin *pin);

extern const Pin LED_GREEN;
extern const Pin LED_RED;
extern const Pin LED_YELLOW;

extern const Pin MOTOR_GATE_1;
extern const Pin MOTOR_GATE_2;
extern const Pin MOTOR_GATE_3;
extern const Pin MOTOR_GATE_4;
extern const Pin MOTOR_GATE_5;
extern const Pin MOTOR_GATE_6;

//called like this:
//set_pin(&LED_GREEN);

#endif