#ifndef MOTOR_STATES_H
#define MOTOR_STATES_H

#include "pins.h"

#include <stdbool.h>

volatile bool motor_state_change_flag; //had extern

/*
void motor_stop(); 
void test_gates_on();

void f1();
void f2();
void f3();

void b1();
void b2();
void b3();
*/

//new implementation
inline void motor_stop()
{
	CLR_MOTOR_GATE_1();
	CLR_MOTOR_GATE_2();
	CLR_MOTOR_GATE_3();
	CLR_MOTOR_GATE_4();
	CLR_MOTOR_GATE_5();
	CLR_MOTOR_GATE_6();
}

inline void test_gates_on()
{
	SET_MOTOR_GATE_1();
	SET_MOTOR_GATE_2();
	SET_MOTOR_GATE_3();
	SET_MOTOR_GATE_4();
	SET_MOTOR_GATE_5();
	SET_MOTOR_GATE_6();
	TCNT1 = 0;
	motor_state_change_flag = true;
}

inline void f1()
{
	SET_MOTOR_GATE_1();
	CLR_MOTOR_GATE_2();
	CLR_MOTOR_GATE_3();
	CLR_MOTOR_GATE_4();
	SET_MOTOR_GATE_5();
	CLR_MOTOR_GATE_6();
	TCNT1 = 0;
	motor_state_change_flag = true;
}

inline void f2()
{
	CLR_MOTOR_GATE_1();
	SET_MOTOR_GATE_2();
	CLR_MOTOR_GATE_3();
	CLR_MOTOR_GATE_4();
	CLR_MOTOR_GATE_5();
	SET_MOTOR_GATE_6();
	TCNT1 = 0;
	motor_state_change_flag = true;
}

inline void f3()
{
	CLR_MOTOR_GATE_1();
	CLR_MOTOR_GATE_2();
	SET_MOTOR_GATE_3();
	SET_MOTOR_GATE_4();
	CLR_MOTOR_GATE_5();
	CLR_MOTOR_GATE_6();
	TCNT1 = 0;
	motor_state_change_flag = true;
}

inline void b1()
{
	CLR_MOTOR_GATE_1();
	SET_MOTOR_GATE_2();
	CLR_MOTOR_GATE_3();
	SET_MOTOR_GATE_4();
	CLR_MOTOR_GATE_5();
	CLR_MOTOR_GATE_6();
	TCNT1 = 0;
	motor_state_change_flag = true;
}

inline void b2()
{
	SET_MOTOR_GATE_1();
	CLR_MOTOR_GATE_2();
	CLR_MOTOR_GATE_3();
	CLR_MOTOR_GATE_4();
	CLR_MOTOR_GATE_5();
	SET_MOTOR_GATE_6();
	TCNT1 = 0;
	motor_state_change_flag = true;
}

inline void b3()
{
	CLR_MOTOR_GATE_1();
	CLR_MOTOR_GATE_2();
	SET_MOTOR_GATE_3();
	CLR_MOTOR_GATE_4();
	SET_MOTOR_GATE_5();
	CLR_MOTOR_GATE_6();
	TCNT1 = 0;
	motor_state_change_flag = true;
}

#endif