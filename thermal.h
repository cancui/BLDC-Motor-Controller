#ifndef THERMAL_H
#define THERMAL_H

//#include "main.h"
#include <stdint.h>

const uint8_t operational_adc_reading;
const uint8_t high_adc_reading;
const uint8_t critical_adc_reading;

volatile uint8_t hottest_adc_reading;

#endif