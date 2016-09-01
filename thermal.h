#ifndef THERMAL_H
#define THERMAL_H

#include "simple_moving_average.h"
//#include "main.h"

#include <stdint.h>
#include <stdbool.h>

#define MA_MAX_SIZE 4

const uint8_t operational_adc_reading;
const uint8_t high_adc_reading;
const uint8_t critical_adc_reading;

volatile Simple_moving_average *temperatures_adc0;
volatile Simple_moving_average *temperatures_adc1;
volatile Simple_moving_average *temperatures_adc2;

volatile bool sample_gate_temperatures_flag;
volatile uint8_t hottest_adc_reading;

void init_thermal();
void sample_gate_temperatures();

#endif