#include "motor_states.h"
#include "pins.h"

void motor_stop()
{
	pin_clear(&MOTOR_GATE_1);
	pin_clear(&MOTOR_GATE_2);
	pin_clear(&MOTOR_GATE_3);
	pin_clear(&MOTOR_GATE_4);
	pin_clear(&MOTOR_GATE_5);
	pin_clear(&MOTOR_GATE_6);
}

void f1()
{
	pin_set(&MOTOR_GATE_1);
	pin_clear(&MOTOR_GATE_2);
	pin_clear(&MOTOR_GATE_3);
	pin_clear(&MOTOR_GATE_4);
	pin_set(&MOTOR_GATE_5);
	pin_clear(&MOTOR_GATE_6);
}

void f2()
{
	pin_clear(&MOTOR_GATE_1);
	pin_set(&MOTOR_GATE_2);
	pin_clear(&MOTOR_GATE_3);
	pin_clear(&MOTOR_GATE_4);
	pin_clear(&MOTOR_GATE_5);
	pin_set(&MOTOR_GATE_6);
}

void f3()
{
	pin_clear(&MOTOR_GATE_1);
	pin_clear(&MOTOR_GATE_2);
	pin_set(&MOTOR_GATE_3);
	pin_set(&MOTOR_GATE_4);
	pin_clear(&MOTOR_GATE_5);
	pin_clear(&MOTOR_GATE_6);
}

void b1()
{
	pin_clear(&MOTOR_GATE_1);
	pin_set(&MOTOR_GATE_2);
	pin_clear(&MOTOR_GATE_3);
	pin_set(&MOTOR_GATE_4);
	pin_clear(&MOTOR_GATE_5);
	pin_clear(&MOTOR_GATE_6);
}

void b2()
{
	pin_set(&MOTOR_GATE_1);
	pin_clear(&MOTOR_GATE_2);
	pin_clear(&MOTOR_GATE_3);
	pin_clear(&MOTOR_GATE_4);
	pin_clear(&MOTOR_GATE_5);
	pin_set(&MOTOR_GATE_6);
}

void b3()
{
	pin_clear(&MOTOR_GATE_1);
	pin_clear(&MOTOR_GATE_2);
	pin_set(&MOTOR_GATE_3);
	pin_clear(&MOTOR_GATE_4);
	pin_set(&MOTOR_GATE_5);
	pin_clear(&MOTOR_GATE_6);
}