/********************************************************************************
 Файл определений событий в системе.

 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        14 марта 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ********************************************************************************/

#pragma once


typedef uint8_t k_event; // Событие ядра


// Перечень событий в системе. Все возможные события должны
// быть перечисленныу в перечислении. Компиляция событий статическая
// для ускорения работы
typedef enum event_id
{
    event_booted,
    EVENT_LASTEVENT_IN_ENUM // ВСЕГДА ПОСЛЕДНЕЕ В ENUM! 
} event_id;