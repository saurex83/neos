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

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "kconf.h"
#include "kdebug.h"
#include "kcodes.h"
#include "kevents.h"
#include "ktasks.h"

kcodes kernal_get_event_handlers(
    k_event event, k_task *tasks, uint16_t *task_num);

kcodes kernel_scheulder(void);

kcodes kernel_event_manager_init(void);
kcodes kernel_event_push(k_event event);
kcodes kernel_event_pop(k_event *event);

kcodes kernel_task_pop(k_task *task);
kcodes kernel_task_push(k_task *task);

kcodes execute_unit_tests(void);

void kernel_panic(char *file, int line, char *str);
kcodes kernel_idle(void);

// пример
// #include "kernel/kernel_panic.h"
// core_kernel_panic( __FILE__, __LINE__, "Event is not registrated");