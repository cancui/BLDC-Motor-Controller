#include "motor_driver.h"
#include "motor_states.h"

#include <util/delay.h>

void delay_100us(unsigned us) 
{
	while(us--) {
		_delay_ms(0.1);
	}
}

void cycle_f(unsigned us100) 
{
	f1();
	delay_100us(us100);
	f2();
	delay_100us(us100);
	f3();
	delay_100us(us100);
}

void cycle_b(unsigned us100) 
{
	b1();
	delay_100us(us100);
	b2();
	delay_100us(us100);
	b3();
	delay_100us(us100);
}

void simple1()
{
	for(unsigned i = 0; i < 100; i++) {
		cycle_f(30);
	}
}