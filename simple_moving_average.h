#ifndef SIMPLE_MOVING_AVERAGE_H
#define SIMPLE_MOVING_AVERAGE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
	uint8_t max_size;
	uint8_t size;
	uint16_t sum;
	uint8_t next;
	uint8_t average; 
	uint8_t *data;
} Simple_moving_average;

//returns a pointer to a newly allocated Simple_moving_average struct
Simple_moving_average *new_simple_moving_average(uint8_t max_size_);

//frees to_free
void free_simple_moving_average(Simple_moving_average *to_free);

//returns the current value stored in this->average
uint8_t peek_simple_moving_average(Simple_moving_average *this);

//enter a new data point, then returns the current value stored in this->average
uint8_t get_simple_moving_average(Simple_moving_average *this, uint8_t new_data_point);

#endif