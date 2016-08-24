#ifndef MOTOR_STATES_H
#define MOTOR_STATES_H

#include <stdbool.h>

volatile bool motor_state_change_flag; //had extern

void motor_stop();
void test_gates_on();

void flash_motor_gates();

void f1();
void f2();
void f3();

void b1();
void b2();
void b3();



#endif