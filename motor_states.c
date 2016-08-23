#include "motor_states.h"
#include "pins.h"
#include "main.h"

#include <util/delay.h>

extern volatile bool motor_state_change_flag = false;

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

void flash_motor_gates()
{
	test_gates_on();
	_delay_ms(100);
	motor_stop();
	_delay_ms(100);
	test_gates_on();
	_delay_ms(100);
	motor_stop();
	_delay_ms(100);
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