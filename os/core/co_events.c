/*******************************************************************************
 События добавляются в простой стек.


 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        7 мая 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/
#include "neos.h"

// Пользователь сам должен заботится о создании этого массива
extern subscriber_t *event_chain_list[];

typedef uint16_t ptr_t;

// очередь событий
static struct 
{
	event_t firedEvents[MAX_CORE_EVENTS];
	ptr_t ptr;
} events_query;

// Возвращает 0 если нет активных событий или 1
// Номер события размещает в event
int coreGetEvent(event_t *event)
{
	if 	(!events_query.ptr)
		return 0;

	events_query.ptr--;
	*event = events_query.firedEvents[events_query.ptr];
	return 1;
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
		MALFUNCTION("Event query exceeded");
	}
	events_query.firedEvents[ptr] = event;
	events_query.ptr ++;
}