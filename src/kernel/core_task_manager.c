/********************************************************************************/
/* Менеджер задач.                                                              */
/* Содержит две очереди задач с разным приоритетом исполнения.                  */
/* Первая очередь аппаратных задач типа FIFO                                    */
/* Вторая очередь програмных задач с приоритетами                               */
/* При постановке задачи во вторую очередь производится ее сортировка           */
/* Если задач в первой очереди нет, то менеджер выдает из второй                */
/* При отсутсвии задач, ничего не возвращаем                                    */
/*                                                                              */
/*                                                                              */
/*                                                                              */
/*                                                                              */
/*                                                                              */
/* Проект:      Neocore                                                         */
/* Автор:       Макшанов Олег Васильевич                                        */
/* Дата:        14 марта 2019г                                                  */
/* Версия:      0.1                                                             */
/* Компания:    ООО "ДиСиСи"                                                    */
/* mail:        pvp@dcconsult.ru                                                */
/********************************************************************************/

#include "kernel/kernel.h"

// Глобальные переменные модуля

static bool sorted_flag = false; // Индикатор не сортированной очереди

static struct   // Очередь событий
{
   core_task task_list[TASK_LIST_LENGTH];
   uint16_t size; // Количество задач в очереди
} tasks;

kcodes core_post_task(core_task *task)
{
    if (tasks.size >= TASK_LIST_LENGTH)
        return 0; //TODO Kernel panic

    tasks.task_list[tasks.size] = *task;
    tasks.size ++;
    sorted_flag = false;
    return k_ok;
}

// Задачи с высоким приоритетом должны оказаться в низу 
// списка, так как их можно легко удалять.
static inline void sort_task(void)
{
    sorted_flag = true;
}

kcodes core_pop_task(core_task *task)
{
    if (tasks.size == 0)
        return k_task_list_empty;

    if (!sorted_flag)
        sort_task();

    *task = tasks.task_list[tasks.size - 1];
    tasks.size --;
    return k_ok;
}