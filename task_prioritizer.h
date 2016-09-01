#ifndef TASK_PRIORITIZER
#define TASK_PRIORITIZER

#include "queue.h"

#include <stdlib.h>
#include <stdbool.h>

typedef struct{
	void (* task_function)();
} Task;

volatile bool task_failed_to_enqueue_flag;

volatile Queue *tasks_high_priority;
volatile Queue *tasks_low_priority;

void init_task_prioritizer();
bool enqueue_task(Queue *queue, void (* task_function_)());
bool do_task(Queue *queue);

#endif