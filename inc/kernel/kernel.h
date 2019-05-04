/********************************************************************************
 Общий заголовочный файл ядра системы.

 TODO все остальные функции ядра из других заголовочных файлов перенести сюда

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

kcodes core_event_handlers(
    k_event event, core_task *tasks, uint16_t *task_num);

kcodes core_event_manager_init(void);
kcodes core_post_event(k_event event);
kcodes core_pop_event(k_event *event);

kcodes core_pop_task(core_task *task);
kcodes core_post_task(core_task *task);

kcodes execute_unit_tests(void);

void core_kernel_panic(char *file, int line, char *str);


// пример
// #include "kernel/kernel_panic.h"
// core_kernel_panic( __FILE__, __LINE__, "Event is not registrated");