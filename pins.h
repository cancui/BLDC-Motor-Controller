#ifndef PINS_H
#define PINS_H

#include <avr/io.h>
//#include <avr/sfr_defs.h>

#define def #define

#define NL /*
*/

#define ASSIGN_PIN(name, reg, bit) \
	def SET_##name (PORT##reg |= _(bit)) NL \
	def CLR_##name (PORT##reg &= ~_BV(bit)) NL \
	def ISSET_##name (PIN##reg & _BV(bit)) NL \
	def BIT_##name _BV(bit) NL \
	def BITPOS_##name bit

#define ASSIGN_PIN(name, reg, bit)			\
	void SET_##name() {						\
		PORT##reg |= _BV(bit);				\
	}										\
	void CLR_##name() {						\
		PORT##reg &= ~_BV(bit);				\
	}
	bool ISSET_##name() {
		return PORT##reg & _BV(bit);
	}
	uint8_t BITPOS_##name() {
		return bit;
	}
	def BITPOS_##name bit

ASSIGN_PIN(LED_GREEN, B, 5)
ASSIGN_PIN(LED_GREEN, B, 4)
ASSIGN_PIN(LED_GREEN, B, 0)






#endif