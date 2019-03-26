/********************************************************************************
 Общий заголовочный файл ядра системы.



 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        14 марта 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ********************************************************************************/

#include "kernel/kernel_configuration.h"
#include "kernel/kcodes.h"
#include "kernel/kevents.h"
#include "stdint.h"
#include "stdbool.h"

#pragma once
//********************************
// Определения типов
//********************************

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
} core_task;

