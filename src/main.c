

#include "events.h"
#include "tasks.h"

int main(void)
{
	task_t task;
	event_t event =1;
	task.taskP = MIN_PRIORITY;

 	xRegEventHandler(1, &task);

	xWriteEvent(event);
	xReadEvent(&event); 
	xExtractEventHandler(1);
	xExtractHandler(&task);
	//DBG_PRINT_LVL1("%s","aaa");
}