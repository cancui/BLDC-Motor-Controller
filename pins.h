#ifndef PINS_H
#define PINS_H

#include <stdbool.h>
#include <avr/io.h>

#define ASSIGN_PIN_H(name, reg, bit)	\
	void SET_##name();					\
	void CLR_##name();					\
	void TOG_##name();					\
	bool ISSET_##name();				\
	uint8_t BITPOS_##name();

#define ASSIGN_PIN(name, reg, bit)		\
	void SET_##name() {					\
		PORT##reg |= _BV(bit);			\
	}									\
	void CLR_##name() {					\
		PORT##reg &= ~_BV(bit);			\
	}									\
	void TOG_##name() {					\
		PORT##reg ^= _BV(bit);			\
	}									\
	bool ISSET_##name() {				\
		return PIN##reg & _BV(bit);		\
	}									\
	uint8_t BITPOS_##name() {			\
		return bit;						\
	}													

#define ASSIGN_PIN_IN(name, reg, bit)	\


ASSIGN_PIN_H(LED_GREEN, B, 5)
ASSIGN_PIN_H(LED_RED, B, 4)
ASSIGN_PIN_H(LED_YELLOW, B, 0)

ASSIGN_PIN_H(MOTOR_GATE_1, D, 7)
ASSIGN_PIN_H(MOTOR_GATE_2, D, 6)
ASSIGN_PIN_H(MOTOR_GATE_3, D, 5)
ASSIGN_PIN_H(MOTOR_GATE_4, D, 4)
ASSIGN_PIN_H(MOTOR_GATE_5, B, 3) // This is on PORTB, not PORTD like the others
ASSIGN_PIN_H(MOTOR_GATE_6, B, 2) // This is on PORTB, not PORTD like the others

#endif