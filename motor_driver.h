#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

//#include "main.h"
#include <stdint.h>
#include <stdbool.h>

volatile bool motor_off; //had extern
volatile bool motor_forwards; //had extern
volatile uint8_t expected_motor_state; //had extern
volatile bool motor_emergency_stop_flag;

volatile bool back_emf_zero_crossing_flag;
volatile uint8_t back_emf_PORTC_state;

void init_motor_driver();

void cycle_f(unsigned us100);

void cycle_b(unsigned us100);

void simple1();

bool startup_f1();

void change_motor_state();

#endif
