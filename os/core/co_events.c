/*******************************************************************************
 События добавляются в простой стек.


 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        7 мая 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/
#include "co_events.h"

// Максимальное число событий в системе
#define MAX_CORE_EVENTS 16

// Пользователь сам должен заботится о создании этого массива
extern subscriber_t *event_chain_list[];

typedef uint16_t ptr_t;

// очередь событий
static struct 
{
	event_t firedEvents[MAX_CORE_EVENTS];
	ptr_t ptr;
} events_query;



void coreFireEvent(event_t event);
subscriber_t* coreGetSubscribers(event_t event);
int coreGetEvent(event_t *event);


// Возвращает 0 если нет активных событий или 1
// Номер события размещает в event
int coreGetEvent(event_t *event)
{
	
}

// Возвращает указатель на список подписчиков
subscriber_t* coreGetSubscribers(event_t event)
{
	return event_chain_list[event];
}

// Активируем событие. Возможно несколько одинаковых событий
void coreFireEvent(event_t event)
{
	ptr_t ptr = events_query.ptr;

	if (ptr >= MAX_CORE_EVENTS)
	{
		// TODO Системный пиздец
	}
	events_query.firedEvents[ptr] = event;
	events_query.ptr ++;
}