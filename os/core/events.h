/*******************************************************************************
 
 
 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        7 мая 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/

#pragma once

#include "neos.h" 
#include "tasks.h"

typedef uint8_t event_t;
typedef void (*subscriber_t)();


void xWriteEvent(event_t event);
int xReadEvent(event_t *event); 
void xRegEventHandler(event_t event, task_t *task);
void xExtractEventHandler(event_t event);
int xExtractHandler(task_t *task);

// Макросы для удобства статической линковки
#define SUBSCRIBER(func)  (subscriber_t*)func

#define SUBSCRIBERS_CHAIN_BEGIN(name)		\
	subscriber_t name[]	= {					

// обозначить конец списка
#define SUBSCRIBERS_CHAIN_END				\
	};


#define REG_SUB_CHAIN(event, chain) [event] = chain 

// Список указателей на цепочки подписчиков
// Список может существовать только один
#define EVENT_CHAIN_LIST_BEGIN				\
subscriber_t event_chain_list[] ={	 

#define EVENT_CHAIN_LIST_END				\
	};


//EVENT_CHAIN_LIST_BEGIN	

//EVENT_CHAIN_LIST_END	