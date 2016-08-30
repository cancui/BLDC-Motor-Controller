#include "motor_states.h"
#include "pins.h"
//#include "main.h"

#include <util/delay.h>

volatile bool motor_state_change_flag = false; //had extern

/*
void motor_stop()
{
	CLR_MOTOR_GATE_1();
	CLR_MOTOR_GATE_2();
	CLR_MOTOR_GATE_3();
	CLR_MOTOR_GATE_4();
	CLR_MOTOR_GATE_5();
	CLR_MOTOR_GATE_6();
}

void test_gates_on()
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

void f1()
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

void f2()
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

void f3()
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

void b1()
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

void b2()
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

void b3()
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
*/

//new implementation

extern inline void motor_stop(); 
extern inline void test_gates_on();

extern inline void f1();
extern inline void f2();
extern inline void f3();

extern inline void b1();
extern inline void b2();
extern inline void b3();