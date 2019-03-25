/********************************************************************************/
/* Модуль регистрации подписок на события                                       */
/* Модуль содержит список  подписчиков на события с приоритетом задач hndl_list */
/* core_retrive_subscriber - извлекает очередного подписчика из списка          */
/* core_subscribe_events - добавляет в список подписчика                        */
/*                                                                              */
/*                                                                              */
/*                                                                              */
/*                                                                              */
/*                                                                              */
/*                                                                              */
/*                                                                              */
/*                                                                              */
/* Проект:      Neocore                                                         */
/* Автор:       Макшанов Олег Васильевич                                        */
/* Дата:        15 марта 2019г                                                  */
/* Версия:      0.1                                                             */
/* Компания:    ООО "ДиСиСи"                                                    */
/* mail:        pvp@dcconsult.ru                                                */
/********************************************************************************/

#include "kernel/kernel.h"

#define BOOTED_HANDLERS_SIZE  (sizeof(BOOTED_HANDLERS) / sizeof(core_task))

typedef struct 
{
    core_task* task_list;
    uint16_t list_size;
} events_handl_map;


// Список обработчиков события event_booted
core_task BOOTED_HANDLERS[] = {
    {.handler = 0, .prior = middle_priority}
};


// Здесь описываются новые списки обработчиков событий.
events_handl_map EVENTS_HANDLERS_MAP[] = {

// [событие] = {.task_list = указатель на список обработчиков,
//              .list_size = длинна списка}

    [event_booted] = {.task_list = BOOTED_HANDLERS,
                      .list_size = BOOTED_HANDLERS_SIZE},

    // Пустое событие только для того что бы компилятор
    // создал массив нужной длинны. Он заполнен нулями по умолчанию
    [EVENT_LASTEVENT_IN_ENUM] = {.task_list = 0,
                                 .list_size = 0}
};


kcodes core_event_handlers(
    k_event event, core_task *tasks, uint16_t *task_num)
{
    // Такого события нет
    if (event>=EVENT_LASTEVENT_IN_ENUM)
        return 0; // Kernel panic

    *task_num = EVENTS_HANDLERS_MAP[event].list_size;
    tasks = EVENTS_HANDLERS_MAP[event].task_list;
    return k_ok;
}
