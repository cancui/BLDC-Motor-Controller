#include "pins.h"
#include "stdbool.h"

void pin_set(const Pin *pin)
{
	switch (pin->port) {
		//case PORT_A:
		//	PORTA |= _BV(pin->bit);
		case PORT_B:
			PORTB |= _BV(pin->bit);
		case PORT_C:
			PORTC |= _BV(pin->bit);
		case PORT_D:
			PORTD |= _BV(pin->bit);
	}
}

void pin_clear(const Pin *pin)
{
	switch (pin->port) {
		//case PORT_A:
		//	PORTA &= ~_BV(pin->bit);
		case PORT_B:
			PORTB &= ~_BV(pin->bit);
		case PORT_C:
			PORTC &= ~_BV(pin->bit);
		case PORT_D:
			PORTD &= ~_BV(pin->bit);
	}
}

bool pin_isset(const Pin *pin)
{
	switch (pin->port) {
		//case PORT_A:
		//	return PORTA & _BV(pin->bit);
		case PORT_B:
			return PORTB & _BV(pin->bit);
		case PORT_C:
			return PORTC & _BV(pin->bit);
		case PORT_D:
			return PORTD & _BV(pin->bit);
		default:
			return false;
	}
}

uint8_t pin_bitpos(const Pin *pin)
{
	return pin->bit;
}

Port pin_port(const Pin *pin)
{
	return pin->port;
}

extern const Pin LED_GREEN = { .port = PORT_B, .bit = 5 };
extern const Pin LED_RED = { .port = PORT_B, .bit = 4 };
extern const Pin LED_YELLOW = { .port = PORT_B, .bit = 0 };

extern const Pin MOTOR_GATE_1 = { .port = PORT_D, .bit = 7 };
extern const Pin MOTOR_GATE_2 = { .port = PORT_D, .bit = 6 };
extern const Pin MOTOR_GATE_3 = { .port = PORT_D, .bit = 5 };
extern const Pin MOTOR_GATE_4 = { .port = PORT_D, .bit = 4 };
extern const Pin MOTOR_GATE_5 = { .port = PORT_D, .bit = 3 };
extern const Pin MOTOR_GATE_6 = { .port = PORT_D, .bit = 2 };
