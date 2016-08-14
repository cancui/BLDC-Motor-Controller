#ifndef PINS_H
#define PINS_H

#include <stdbool.h>
#include <avr/io.h>

#define ASSIGN_PIN_H(name, reg, bit)	\
	void SET_##name();					\
	void CLR_##name();					\
	bool ISSET_##name();				\
	uint8_t BITPOS_##name();

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

ASSIGN_PIN_H(LED_GREEN, B, 5)
ASSIGN_PIN_H(LED_RED, B, 4)
ASSIGN_PIN_H(LED_YELLOW, B, 0)

ASSIGN_PIN_H(MOTOR_GATE_1, D, 7)
ASSIGN_PIN_H(MOTOR_GATE_2, D, 6)
ASSIGN_PIN_H(MOTOR_GATE_3, D, 5)
ASSIGN_PIN_H(MOTOR_GATE_4, D, 4)
ASSIGN_PIN_H(MOTOR_GATE_5, D, 3)
ASSIGN_PIN_H(MOTOR_GATE_6, D, 2)

#endif