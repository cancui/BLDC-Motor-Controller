#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include "main.h"

void cycle_f(unsigned us100);
void cycle_b(unsigned us100);

void simple1();

volatile bool motor_off; //had extern
volatile bool motor_forwards; //had extern
volatile uint8_t expected_motor_state; //had extern

#endif
