/********************************************************************************
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



 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        14 марта 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ********************************************************************************/

// TODO Подумать о блокировке прерываний при постановке событий в очередь
#include "kernel/core_event_manager.h"
#include "kernel/kernel_panic.h"

// Глобальные переменные модуля
static struct   // Очередь событий
{
   k_event query[EVENT_QUERY_LENGTH];
   uint16_t size; // Количество событий в очереди 
} event_query;

//********************************************************************************

// Первоначальная инициализация модуля
kcodes core_event_manager_init(void)
{
    event_query.size = 0 ;
    return k_ok;
}

// Наличие места в очереди
static inline bool is_free_space_query(void)
{
    if (event_query.size < EVENT_QUERY_LENGTH )
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
kcodes core_post_event(k_event event)
{
    if (!(is_free_space_query()))
        core_kernel_panic( __FILE__, __LINE__, "Event query overloaded");

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
    if (event_query.size == 0)
        return (k_noevents);

    *event = event_query.query[event_query.size - 1];
    event_query.size--;
    return k_ok;    
}




/********************************************************************************/
// Юнит тесты
/********************************************************************************/

int TUNIT_event_manager_test_1(char *msg)
{
    return 0;   
}