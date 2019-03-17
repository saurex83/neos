/********************************************************************************/
/* Менеджер событий.                                                            */
/* Обеспечивате разбор списка событий и постановку заданий менеджере задач      */
/* Список разбирается на основе сортировонаго списка слушателей событий         */
/* После разбора списка и постановки задачи событие уничтожается                */
/* Список слушателей содержит информацию о приоритете задачи и типе очереди     */
/* Для ускорения работы с аппаратными событиями из прерывания или выполнении    */
/* задач сетевого протокола можно поставить задачу самостоятельно в очередь без */
/* использования менеджера событий, но в этом случаи другие модули не будут     */
/* знать о возникновении события и отреагировать на него.                       */
/* Возможно поставить приоритетную задачу самостоятельно, но создать событие    */
/* с низким приоритетом для целей подсчета статистики или еще для чего          */
/*                                                                              */
/* Проект:      Neocore                                                         */
/* Автор:       Макшанов Олег Васильевич                                        */
/* Дата:        14 марта 2019г                                                  */
/* Версия:      0.1                                                             */
/* Компания:    ООО "ДиСиСи"                                                    */
/* mail:        pvp@dcconsult.ru                                                */
/********************************************************************************/


// TODO Подумать о блокировке прерываний при постановке событий в очередь
#include "kernel/kernel.h"

// Глобальные переменные модуля
static struct   // Очередь событий
{
   k_event query[EVENT_QUERY_LENGTH];
   uint16_t ptr;  
   uint16_t items_num; // Количество обработчиков в очереди 
} event_query;

//********************************************************************************
kcodes core_event_manager_init(void);
kcodes core_post_event(k_event event);
kcodes core_pop_event(k_event *event);
static inline bool is_free_space_query(void);
static inline bool is_event_in_query(k_event event);
static inline void push_event(k_event event);

// Первоначальная инициализация модуля
kcodes core_event_manager_init(void)
{
    event_query.ptr = 0 ;
    event_query.items_num = 0;
    return k_ok;
}

// Наличие места в очереди
static inline bool is_free_space_query(void)
{
    if (event_query.items_num < EVENT_QUERY_LENGTH )
        return (true);
    return (false);
}

// Было ли ранее событие размещено в очереди
static inline bool is_event_in_query(k_event event)
{
    for (uint16_t i=0; i < event_query.items_num; i++ )
        if (event_query.query[i] == event)
            return  (true);
    return (false);
}

// Размещение в очереди
static inline void push_event(k_event event)
{
    event_query.ptr++;
    event_query.query[event_query.ptr] = event;
    event_query.items_num ++;
}
    
// Установка события в очередь
// Возвращает k_ok в случаи успешного завершения
kcodes core_post_event(k_event event)
{
    if (!(is_free_space_query()))
        return 0;   // TODO Тут очередь переполнена. Нужен Kernel panic?

    if (is_event_in_query(event))
        return k_ok;   // Добавлять не нужно, уже в очереди

    push_event(event);

    return k_ok;
}

// Извлекает событие из очереди
// в случаи успешного завершения возвращает k_ok
// в противном k_noevents
kcodes core_pop_event(k_event *event)
{
    if (event_query.items_num == 0)
        return (k_noevents);

    *event = event_query.query[event_query.ptr];
    event_query.ptr--;
    event_query.items_num--;
    return (k_ok);    
}