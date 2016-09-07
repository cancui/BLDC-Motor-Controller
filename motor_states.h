#ifndef MOTOR_STATES_H
#define MOTOR_STATES_H

#include "pins.h"

#include <stdbool.h>
#include <avr/interrupt.h>

volatile bool motor_state_change_flag;

inline void motor_stop()
{
	//cli();
	CLR_MOTOR_GATE_1();
	CLR_MOTOR_GATE_2();
	CLR_MOTOR_GATE_3();
	CLR_MOTOR_GATE_4();
	CLR_MOTOR_GATE_5();
	CLR_MOTOR_GATE_6();
	//sei();
}

inline void test_gates_on()
{
	//cli();
	SET_MOTOR_GATE_1();
	SET_MOTOR_GATE_2();
	SET_MOTOR_GATE_3();
	SET_MOTOR_GATE_4();
	SET_MOTOR_GATE_5();
	SET_MOTOR_GATE_6();
	TCNT1 = 0;
	motor_state_change_flag = true;
	//sei();
}

inline void f1()
{
	//cli();
	SET_MOTOR_GATE_1();
	CLR_MOTOR_GATE_2();
	CLR_MOTOR_GATE_3();
	CLR_MOTOR_GATE_4();
	SET_MOTOR_GATE_5();
	CLR_MOTOR_GATE_6();
	TCNT1 = 0;
	motor_state_change_flag = true;
	//sei();
}

inline void f2()
{
	//cli();
	CLR_MOTOR_GATE_1();
	SET_MOTOR_GATE_2();
	CLR_MOTOR_GATE_3();
	CLR_MOTOR_GATE_4();
	CLR_MOTOR_GATE_5();
	SET_MOTOR_GATE_6();
	TCNT1 = 0;
	motor_state_change_flag = true;
	//sei();
}

inline void f3()
{
	//cli();
	CLR_MOTOR_GATE_1();
	CLR_MOTOR_GATE_2();
	SET_MOTOR_GATE_3();
	SET_MOTOR_GATE_4();
	CLR_MOTOR_GATE_5();
	CLR_MOTOR_GATE_6();
	TCNT1 = 0;
	motor_state_change_flag = true;
	//sei();
}

inline void b1()
{
	//cli();
	CLR_MOTOR_GATE_1();
	SET_MOTOR_GATE_2();
	CLR_MOTOR_GATE_3();
	SET_MOTOR_GATE_4();
	CLR_MOTOR_GATE_5();
	CLR_MOTOR_GATE_6();
	TCNT1 = 0;
	motor_state_change_flag = true;
	//sei();
}

inline void b2()
{
	//cli();
	SET_MOTOR_GATE_1();
	CLR_MOTOR_GATE_2();
	CLR_MOTOR_GATE_3();
	CLR_MOTOR_GATE_4();
	CLR_MOTOR_GATE_5();
	SET_MOTOR_GATE_6();
	TCNT1 = 0;
	motor_state_change_flag = true;
	//sei();
}

inline void b3()
{
	//cli();
	CLR_MOTOR_GATE_1();
	CLR_MOTOR_GATE_2();
	SET_MOTOR_GATE_3();
	CLR_MOTOR_GATE_4();
	SET_MOTOR_GATE_5();
	CLR_MOTOR_GATE_6();
	TCNT1 = 0;
	motor_state_change_flag = true;
	//sei();
}

#endif