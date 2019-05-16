/*******************************************************************************
 
 
 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        7 мая 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/

#include "neos.h"
#include "tasks.h"

void xTaskWrite(task_t *task);

// Извлекает задачу из очереди с удалением
int xTaskRead(task_t *task);

// Указатели на индексы в массивах
typedef uint8_t ptr_t;

typedef struct queryMinPriority
{
	task_t task[TASK_Q_SIZE_MinP];
	ptr_t ptr;
} queryMinPriority;

typedef struct 
{
	task_t task[TASK_Q_SIZE_MaxP];
	ptr_t ptr;
} queryMaxPriority;

static struct 
{
	queryMinPriority queryMinPriority;
	queryMaxPriority queryMaxPriority;
} taskQuery;


static inline void pushMin(task_t *task)
{
	queryMinPriority *qptr;
	qptr = &taskQuery.queryMinPriority;

	if (qptr->ptr < TASK_Q_SIZE_MinP)
	{
		qptr->task[qptr->ptr] = *task;
		qptr->ptr++;
	}
	kernel_panic( __FILE__, __LINE__, "Query min priority full");
}

static inline void pushMax(task_t *task)
{
	queryMaxPriority *qptr;
	qptr = &taskQuery.queryMaxPriority;

	if (qptr->ptr < TASK_Q_SIZE_MaxP)
	{
		qptr->task[qptr->ptr] = *task;
		qptr->ptr++;
	}
	kernel_panic( __FILE__, __LINE__, "Query max priority full");
}

static inline int popMin(task_t *task)
{
	queryMinPriority *qptr;
	qptr = &taskQuery.queryMinPriority;

	if (qptr->ptr == 0)
		return -1;

	qptr->ptr--;
	*task = qptr->task[qptr->ptr];
	return 0;
}

static inline int popMax(task_t *task)
{
	queryMaxPriority *qptr;
	qptr = &taskQuery.queryMaxPriority;

	if (qptr->ptr == 0)
		return -1;

	qptr->ptr--;
	*task = qptr->task[qptr->ptr];
	return 0;
}

void xTaskWrite(task_t *task)
{
	if (task->taskP == MIN_PRIORITY)
		pushMin(task);
	else if (task->taskP == MAX_PRIORITY)
		pushMax(task);
	else
		kernel_panic( __FILE__, __LINE__, "Wrong priority task");
}

// Извлекает задачу из очереди с удалением
int xTaskRead(task_t *task)
{
	if (popMax(task) == 0)
		return 0;
	else if (popMin(task) == 0)
		return 0;
	else
		return -1;
}	