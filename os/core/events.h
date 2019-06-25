/*******************************************************************************
 Обработчик событий в системе.
 Пользователь самостоятельно создает списки подписчиков на события с помощью
 макросов EVENT_SUBSCRIBERS_CHAIN_BEGIN, EVENT_SUBSCRIBERS_CHAIN_END и 
 SUBSCRIBER. 
 Списки подписчиков регистрируются в глобальный список event_chain_list.
 Индексом масива является номер события, значением массива указатель на 
 цепочку обработчиков. Такой подход позволяет сделать максимально быстрый
 код с минимальными затратами памяти, но это переносит некоторые проблемы на 
 пользователя.
 При определении EVENT_TO_SUBSCRIBERS_CHAIN_MAP_BEGIN порядок событий должен
 нумероваться от 0 и по порядку для создания массива минимальной длинны при
 статической компиляции. Если пользователь сделает одно событие с номером 1000 
 то будет создан массив длинной 1000 с пустыми записями заполнеными нулями.
 При выборе цепочки подписчиков по номеру события код не проверяет факт 
 регистрации события и программа может зависнуть, так как указатели не верны.

 
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

typedef uint16_t event_t;
typedef void (*subscriber_t)(void);

// Активируем событие. Возможно несколько одинаковых событий
void coreFireEvent(event_t event);

// Возвращает указатель на список подписчиков
subscriber_t* coreGetSubscribers(event_t event);

// Возвращает 0 если нет активных событий или 1
// Номер события размещает в event
int coreGetEvent(event_t *event);

// Конец цепочки подписчиков
#define SUB_CHAIN_END  NULL

// Макросы для удобства статической линковки
#define SUBSCRIBER(func)  func

#define EVENT_SUBSCRIBERS_CHAIN_BEGIN(name)		\
	subscriber_t name[]	= {					

// обозначить конец списка
#define EVENT_SUBSCRIBERS_CHAIN_END				\
		,SUB_CHAIN_END							\
	};

#define REG_SUB_CHAIN(event, chain) [event] = chain 

// Список указателей на цепочки подписчиков
// Список может существовать только один
#define EVENT_TO_SUBSCRIBERS_CHAIN_MAP_BEGIN	\
subscriber_t *event_chain_list[] ={	 

#define EVENT_TO_SUBSCRIBERS_CHAIN_MAP_END		\
	};


/* ПРИМЕР */

//EVENT_SUBSCRIBERS_CHAIN_BEGIN(chain1)
//	SUBSCRIBER(test1),
//	SUBSCRIBER(test2)
//EVENT_SUBSCRIBERS_CHAIN_END	

//EVENT_SUBSCRIBERS_CHAIN_BEGIN(chain2)
//	SUBSCRIBER(test1),
//	SUBSCRIBER(test2)
//EVENT_SUBSCRIBERS_CHAIN_END

//EVENT_CHAIN_LIST_BEGIN	
//   REG_SUB_CHAIN(event1, chain1),
//   REG_SUB_CHAIN(event2, chain2)
//EVENT_CHAIN_LIST_END	

