#include "simple_moving_average.h"

#include <stdlib.h>

Simple_moving_average *new_simple_moving_average(uint8_t max_size_)
{
	Simple_moving_average *to_return;

	to_return = (Simple_moving_average *)malloc(sizeof(Simple_moving_average));

	if(!to_return) {
		return NULL;
	}

	to_return->data = (uint8_t *)malloc(sizeof(uint8_t) * max_size_);

	if(!to_return->data){
		free(to_return);
		return NULL;
	}

	to_return->max_size = max_size_;
	to_return->size = 0;
	to_return->sum = 0;
	to_return->next = 0;
	to_return->average = 0; 

	return to_return;
}

void free_simple_moving_average(Simple_moving_average *to_free)
{
	free(to_free->data);
	free(to_free);
}

uint8_t peek_simple_moving_average(Simple_moving_average *this)
{
	return this->average;
}

uint8_t get_simple_moving_average(Simple_moving_average *this, uint8_t new_data_point)
{
	this->sum += new_data_point;

	if(this->size >= this->max_size){
		this->sum -= this->data[this->next];
	} else {
		this->size++;
	}

	this->data[this->next] = new_data_point;

	this->next = (++(this->next))%(this->max_size);

	this->average = this->sum / this->size;

	return this->average;
}