/*******************************************************************************
 Менеджер событий.                                                            
 Обеспечивате разбор списка событий и постановку заданий менеджере задач      
 Список разбирается на основе сортировонаго списка слушателей событий         
 После разбора списка и постановки задачи событие уничтожается                
 Список слушателей содержит информацию о приоритете задачи и типе очереди     
 Для ускорения работы с аппаратными событиями из прерывания или выполнении    
 задач сетевого протокола можно поставить задачу самостоятельно в очередь без 
 использования менеджера событий, но в этом случаи другие модули не будут     
 знать о возникновении события и отреагировать на него.                       
 Возможно поставить приоритетную задачу самостоятельно, но создать событие    
 с низким приоритетом для целей подсчета статистики или еще для чего          
 core_event_manager_init - инициализация модуля                               
 core_post_event - размещение события                                         
 core_pop_event - извлечение события   

 ВНИМАНИЕ
 Реализация динамического добавления обработчико событий.
 В список listeners_list добавляются обработчики (event,task)
 Далее список сортируем чтобы event шли попорядку.
 Потом формируем на основе сортированного списка цепочек обработчкив.
 Элемент списка содержит информацию о event, указатель на начало task в 
 listeners_list и их количестве. Таким образом можно по запросу быстро выдавать
 информацию об всех обработчиках какого нибудь события пользуясь списком 
 цепочек обработчиков.

 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        14 марта 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/

// TODO Подумать о блокировке прерываний при постановке событий в очередь
#include "kernel.h"
#include <stdlib.h>

// Глобальные переменные модуля
static struct   // Очередь событий
{
   k_event query[MAX_EVENTS];
   uint16_t size; // Количество событий в очереди 
} event_query;

typedef struct   
{
   k_event event;
   k_task  task;
} handler_record;

// Запись о цепочке обработчиков. 
typedef struct 
{
    k_event event;
    k_task *ptr;
    uint16_t tasks_count;
} handlers_chain;

// Массив указателей на сортированные цепочки обработчиков событий
static struct 
{
    handlers_chain chain[MAX_EVENTS];
    uint16_t size;
} handlers_chain_list;

// Список подписчиков
static struct 
{
    handler_record hndl[LISTENER_QUERY_LENGTH];
    uint16_t size; // Количество записей
} listeners_list;


//******************************************************************************

kcodes kernel_event_manager_init(void);
kcodes kernel_event_push(k_event event);
kcodes kernel_event_pop(k_event *event);
kcodes kernel_event_hndl_add(k_event event, k_task *task);
static int compare(const void * x1, const void * x2);
static void build_handlers_chain_list(void);

// Первоначальная инициализация модуля
kcodes kernel_event_manager_init(void)
{
    event_query.size = 0;
    listeners_list.size = 0;
    handlers_chain_list.size = 0;
    return k_ok;
}

// Наличие места в очереди
static inline bool is_free_space_query(void)
{
    if (event_query.size < MAX_EVENTS )
        return (true);
    return (false);
}

// Было ли ранее событие размещено в очереди
static inline bool is_event_in_query(k_event event)
{
    for (uint16_t i=0; i < event_query.size; i++ )
        if (event_query.query[i] == event)
            return  (true);
    return (false);
}

// Размещение в очереди
static inline void push_event(k_event event)
{
    event_query.query[event_query.size] = event;
    event_query.size ++;
}
    
// Установка события в очередь
// Возвращает k_ok в случаи успешного завершения
kcodes kernel_event_push(k_event event)
{
    if (!(is_free_space_query()))
        kernel_panic( __FILE__, __LINE__, "Event query overloaded");

    if (is_event_in_query(event))
        return k_ok;   // Добавлять не нужно, уже в очереди

    push_event(event);

    return k_ok;
}

// Извлекает событие из очереди
// в случаи успешного завершения возвращает k_ok
// в противном k_noevents
kcodes kernel_event_pop(k_event *event)
{
    if (event_query.size == 0)
        return (k_noevents);

    *event = event_query.query[event_query.size - 1];
    event_query.size--;
    return k_ok;    
}


// Функция сравнения для алгоритма сортировки
// Если x1 < x2 возвращаем отрицательное значение
// Если x1 = x2 возвращаем ноль
// Если x1 > x2 возвращаем положительное значение
static int compare(const void * x1, const void * x2)
{
    int x1_val = (*(handler_record*)x1).event;
    int x2_val = (*(handler_record*)x2).event;

    // Высокоприоритетные задачи должны оказаться внизу списка
    // Начало списка - индекс масива [0]
    int result = x1_val - x2_val ;
    return result;
} 

// Добавляет обработчик события.
kcodes kernel_event_hndl_add(k_event event, k_task *task)
{
    if (listeners_list.size >= LISTENER_QUERY_LENGTH)
        kernel_panic( __FILE__, __LINE__, "Event listeners list overloaded");

    uint16_t ptr = listeners_list.size;
    listeners_list.hndl[ptr].task = *task;
    listeners_list.hndl[ptr].event = event;
    listeners_list.size++ ;

    qsort(listeners_list.hndl, listeners_list.size, sizeof(handler_record),
        compare);

    build_handlers_chain_list();

    return k_ok;
}

// Обрабатывает отсортированный список подписчиков событий и заполняет
// список цепочек обработчиков. 
static void build_handlers_chain_list(void)
{
    k_event curr_event;
    handlers_chain *chain;
    uint16_t curr_ptr;
    uint16_t item = 0;
    uint16_t chain_len;

    handlers_chain_list.size = 0;
    
    while (item < listeners_list.size)
    {
        chain_len = 0;
        curr_event =  listeners_list.hndl[item].event;
        curr_ptr = item;
        do
        {
            item++;
            chain_len++;
        } while 
            ((listeners_list.hndl[item].event == curr_event) &&
            ( item < listeners_list.size));

        chain = &handlers_chain_list.chain[handlers_chain_list.size];
        chain->event = curr_event;
        chain->tasks_count  = chain_len;
        chain->ptr = &listeners_list.hndl[curr_ptr].task;
        handlers_chain_list.size ++;

        if (handlers_chain_list.size >= MAX_EVENTS)
            kernel_panic( __FILE__, __LINE__, "Handlers chain list overloaded");
    }
}


kcodes kernel_get_event_handlers(
    k_event event, k_task *tasks, uint16_t *task_num)
{
    return k_ok;
}

/******************************************************************************/
// Юнит тесты
/******************************************************************************/

int TUNIT_event_manager_test_1(char *msg)
{
    return 0;   
}