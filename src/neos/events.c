/*******************************************************************************
 События добавляются в простой стек.

 При регистрации событий, обработчик добавляеться в односвязанный список.
 Используется один список для всех обработчкиков. 
 В другом масиве храниться номере события и указатель на первый обработчик
 данного события. Повторное размещение событий не происходит. 

 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        7 мая 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/
#include "neos.h"
#include "events.h"
#include "tasks.h"

#define LAST_ITEM	0xff

// Указатели на индексы в массивах
typedef uint8_t ptr_t;

// Добавим событие в список. Блокировка повторного события
void 	xWriteEvent(event_t event);	

//Прочитаем событие из очереди с его удалением. -1 если пустая очередь
int 	xReadEvent(event_t *event); 

// Использует односвязанный список для быстрого извлечения обработчиков
void 	xRegEventHandler(event_t event, task_t *task);

// Указываем обработчики каких событих собираемся прочитать
void	xExtractEventHandler(event_t event);

// Извлекает и помещает обработчик в *task.
// Возвращает 0 при успешном извлечении или -1 если нет обработчиков
int 	xExtractHandler(task_t *task);

static struct 
{
	event_t 	event[EVENT_STACK_SIZE];
	ptr_t 		ptr;
} eventStack;

typedef struct 
{
	task_t  	task;
	ptr_t		next;
} itemHandler_t;


typedef struct 
{
	event_t 	event;
	ptr_t 		first;
} itemEvent_t;

static struct 
{
	itemEvent_t item[EVENT_COUNT_REG];
	ptr_t		ptr;
} eventHandlersList;

static struct
{
	itemHandler_t 	item[EVENT_HNDL_MAX];
	ptr_t			ptr;
} relatedSeqHandlers;

static ptr_t iterator;

 /*****************************************************************************/

void xWriteEvent(event_t event)
{
	ptr_t ptr = eventStack.ptr ;
	
	if (ptr < EVENT_STACK_SIZE)
	{
		eventStack.event[ptr] = event;
		eventStack.ptr ++;
		return ;
	}
	 kernel_panic( __FILE__, __LINE__, "Event stack full");
}	

//Прочитаем событие из очереди с его удалением. -1 если пустая очередь
int xReadEvent(event_t *event)
{	
	if (eventStack.ptr == 0)
		return -1;

	eventStack.ptr --;
	*event = eventStack.event[eventStack.ptr];
	return 0;
}

 /*****************************************************************************/
static inline int checkEventReg(event_t event)
{
	for (ptr_t i = 0; i < eventHandlersList.ptr; i++)
		if (eventHandlersList.item[i].event == event)
			return 0;
	return -1;
}


static inline void eventReg(event_t event, ptr_t index)
{
	if (eventHandlersList.ptr < EVENT_COUNT_REG)
	{
		eventHandlersList.item[eventHandlersList.ptr].event = event;
		eventHandlersList.item[eventHandlersList.ptr].first = index;
		eventHandlersList.ptr++;
	}
	kernel_panic( __FILE__, __LINE__, "Max number events registrated");
} 

static inline ptr_t addHandler(task_t *task)
{
	ptr_t ptr = relatedSeqHandlers.ptr;
	if (relatedSeqHandlers.ptr < EVENT_HNDL_MAX)
	{
		relatedSeqHandlers.item[ptr].task = *task;
		relatedSeqHandlers.item[ptr].next = LAST_ITEM;
		relatedSeqHandlers.ptr++;
		return ptr;
	}
	kernel_panic( __FILE__, __LINE__, "Max number handlers registrated");
	return ptr;
}

static inline ptr_t findLastHandler(event_t event)
{
	ptr_t first_ptr = 0;
	ptr_t next_ptr;

	for (ptr_t i = 0; i < eventHandlersList.ptr; i++)
		if (eventHandlersList.item[i].event == event)
		{
			first_ptr = eventHandlersList.item[i].first;
			break;
		}
	
	while(1)
	{
		next_ptr = relatedSeqHandlers.item[first_ptr].next;
		
		if (next_ptr == LAST_ITEM)
			break;

		first_ptr = next_ptr;
	};			
	
	return first_ptr;
}

static inline void connectNextHandler(ptr_t last_item, ptr_t next_item)
{
	relatedSeqHandlers.item[last_item].next = next_item;
}

void xRegEventHandler(event_t event, task_t *task)
{
	ptr_t hndIndex = addHandler(task);
	
	// Было ли событие ранее зарегестрированно в eventHandlersList
	if (checkEventReg(event) == -1)
	{
		eventReg(event, hndIndex);
		return;
	}

	ptr_t last_ptr = findLastHandler(event);
	connectNextHandler(last_ptr, hndIndex);
}

// Указываем обработчики какого событя собираемся прочитать
void xExtractEventHandler(event_t event)
{
	for (ptr_t i = 0; i < eventHandlersList.ptr; i++)
		if (eventHandlersList.item[i].event == event)
		{
			iterator = eventHandlersList.item[i].first;
			return;
		}

	iterator = LAST_ITEM;
}

// Извлекает и помещает обработчик в *task.
// Возвращает 0 при успешном извлечении или -1 если нет обработчиков
int xExtractHandler(task_t *task)
{
	if (iterator == LAST_ITEM)
		return -1;

	*task = relatedSeqHandlers.item[iterator].task;

	ptr_t next = relatedSeqHandlers.item[iterator].next;
	iterator = next;
	return 0;
}

