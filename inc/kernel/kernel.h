
#include "kernel/kernel_configuration.h"
#include "stdint.h"
#include "stdbool.h"

#pragma once
//********************************
// Определения типов
//********************************

typedef enum kcodes // Коды возврата функций ядра
{
    k_ok = 0x00,
    k_noevents = 0x01,
    k_nosubscribe = 0x02,
    k_task_list_empty = 0x03
} kcodes;


typedef uint8_t k_event; // Событие ядра
typedef kcodes (*task_hndl)(void); // Обработчик задачи

// Перечень событий в системе. Все возможные события должны
// быть перечисленныу в перечислении. Компиляция событий статическая
// для ускорения работы
typedef enum event_id
{
    event_booted,
    EVENT_LASTEVENT_IN_ENUM // ВСЕГДА ПОСЛЕДНЕЕ В ENUM! 
} event_id;


typedef enum task_priority // Перечень приоритетов задач
{
    high_priority = 0,
    middle_priority = 50,
    low_prioritty = 100,
} task_priority;


typedef struct // Задача
{
    task_priority prior;
    task_hndl handler;
} core_task;

