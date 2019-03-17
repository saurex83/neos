/********************************************************************************/
/*                                                           */
/*       */
/*         */
/*                 */
/*     */
/*     */
/*  */
/*    */
/*                       */
/*     */
/*        */
/*                                                                              */
/* Проект:      Neocore                                                         */
/* Автор:       Макшанов Олег Васильевич                                        */
/* Дата:        15 марта 2019г                                                  */
/* Версия:      0.1                                                             */
/* Компания:    ООО "ДиСиСи"                                                    */
/* mail:        pvp@dcconsult.ru                                                */
/********************************************************************************/

#include "kernel/kernel.h"


// Глобальные переменные модуля
typedef struct 
{
    k_event event;
    task_priority priority;
    task_hndl hndl;
} listener;


static struct 
{
    listener listener_list[LISTENER_QUERY_LENGTH]; // Список обработчиков событий
    uint16_t ptr;
    uint16_t items_num; // Количество обработчиков в очереди 
} hndl_list;


//********************************************************************************
kcodes core_listeners_init(void);
static inline bool is_free_space_list(void);
static inline bool is_hndl_in_list(task_hndl hndl);
static inline void add_hndl(task_hndl hndl, k_event ev, task_priority pri);
kcodes core_subscribe_events(task_hndl hndl, k_event ev, task_priority pri);
kcodes core_retrive_subscriber(task_hndl *hndl, k_event *ev, task_priority *pri);


// Первоначальная инициализация модуля
kcodes core_listeners_init(void)
{
    hndl_list.ptr = 0;
    hndl_list.items_num = 0;
    return k_ok;
}

// Наличие места в в списке
static inline bool is_free_space_list(void)
{
    if (hndl_list.items_num < LISTENER_QUERY_LENGTH )
        return (true);
    return (false);
}

//  Может уже раньше обработчики были зарегестрированы?
static inline bool is_hndl_in_list(task_hndl hndl)
{
    for (uint16_t i=0; i < hndl_list.items_num; i++ )
        if (hndl_list.listener_list[i].hndl == hndl)
            return  (true);
    return (false);
}

// Размещение в очереди
static inline void add_hndl(task_hndl hndl, k_event ev, task_priority pri)
{
    hndl_list.ptr++;
    hndl_list.listener_list[hndl_list.ptr].priority = pri;
    hndl_list.listener_list[hndl_list.ptr].event = ev;
    hndl_list.listener_list[hndl_list.ptr].hndl = hndl;
    hndl_list.items_num ++;
}

// Регистрирует подписчика на событе
// В случаи успешной регистрации возвращает k_ok
// Ранее подписанные обработчики повторно не регистрируются и возвращает
// так же k_ok. Тоесть один и тотже обработчки не может обслуживать 
// разные события и иметь разные приоритеты.
// При переполнение списка kernel panic
kcodes core_subscribe_events(task_hndl hndl, k_event ev, task_priority pri)
{
    if (!(is_free_space_list()))
        return 0;   // TODO kernal panic

    if (is_hndl_in_list(hndl))
        return k_ok;

    add_hndl(hndl, ev, pri); 

    return (k_ok);
}

// Задача извлеч по очереди все обработчики на заданное событие
// first_extr = true означает поиск с начала списка.
// first_extr = false означает продолжение поиска
// *hndl - сюда размещаем найденный обработчик
// *pri - сюда размещаем приоритет обработчика
// Возращает k_ok если было найденно значение 
// Возвращает k_nosubscribe если подписчиков больше нет
kcodes core_retrive_subscriber(
    bool first_extr, k_event ev, task_hndl *hndl, task_priority *pri)
{

    if (first_extr)


}

// начинает поиск события ev начиная с указателя *ptr
// если нашла вернет true
static inline bool find_ptr_handler(uint16_t *ptr, k_event ev)
{
    uint16_t 
}