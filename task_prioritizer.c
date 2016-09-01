#include "task_prioritizer.h"

void init_task_prioritizer()
{
	task_failed_to_enqueue_flag = false;

	tasks_high_priority = queue_new();
	tasks_low_priority = queue_new();
}

bool enqueue_task(Queue *queue, void (* task_function_)())
{
	Task *new_task = (Task *)malloc(sizeof(Task));

	if(!new_task){
		return false;
	}

	new_task->task_function = task_function_;

	if(!queue_push_head(queue, new_task)){
		return false;
	}

	return true;
}

bool do_task(Queue *queue)
{
	if(queue_is_empty(queue)){
		return false;
	}
	
	Task *to_do = queue_pop_tail(queue);
	to_do->task_function();
	to_do->task_function = NULL;
	free(to_do);
	return true;
}