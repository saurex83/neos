/*******************************************************************************
 Менеджер задач.                                                             




 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        14 марта 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/
#include <stdlib.h>
#include "kernel.h"

// Глобальные переменные модуля

static bool sorted_flag = false; // Индикатор не сортированной очереди

static struct   // Очередь событий
{
   k_task task_list[TASK_LIST_LENGTH];
   uint16_t size; // Количество задач в очереди
} tasks;

kcodes kernel_task_push(k_task *task)
{
    if (tasks.size >= TASK_LIST_LENGTH)
        kernel_panic( __FILE__, __LINE__, "Tasks list overloaded");

    tasks.task_list[tasks.size] = *task;
    tasks.size ++;
    sorted_flag = false;
    return k_ok;
}

// Функция сравнения для алгоритма сортировки
// Если x1 < x2 возвращаем отрицательное значение
// Если x1 = x2 возвращаем ноль
// Если x1 > x2 возвращаем положительное значение
static int compare(const void * x1, const void * x2)
{
    int x1_val = (*(k_task*)x1).prior;
    int x2_val = (*(k_task*)x2).prior;

    // Высокоприоритетные задачи должны оказаться внизу списка
    // Начало списка - индекс масива [0]
    int result = x1_val - x2_val ;
    return result;
} 

static inline void sort_task(void)
{
    qsort(tasks.task_list, tasks.size, sizeof(k_task), compare);
    sorted_flag = true;
}

kcodes kernel_task_pop(k_task *task)
{
    if (tasks.size == 0)
        return k_task_list_empty;

    if (!sorted_flag)
        sort_task();

    *task = tasks.task_list[tasks.size - 1];
    tasks.size --;
    return k_ok;
}

/******************************************************************************/
// Юнит тесты
/******************************************************************************/

int TUNIT_task_manager_test_1(char *msg)
{
    return 0;   
}