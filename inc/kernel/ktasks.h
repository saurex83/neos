
#pragma once

#include "kcodes.h"

typedef kcodes (*task_hndl)(void); // Обработчик задачи

typedef enum task_priority // Перечень приоритетов задач
{
    hw_priority = 255,
    high_priority = 200,
    middle_priority = 50,
    low_prioritty = 0,
} task_priority;

typedef struct // Задача
{
    task_priority prior;
    task_hndl handler;
} k_task;