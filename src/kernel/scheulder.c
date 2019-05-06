/*******************************************************************************
 Планировщик задач                                                           
 Главный цикл работы системы                                                 
 Обеспечивает разбор событий, выполнение задач из очереди                    
 Завершившаяся задача возвращает код ошибки, если ошибка критична            
 то планировщик выполнит экстренное отключение аппаратуры путем вызова       
 пользовательского обработчика или заглушки если такой отсутсвует.           
 После этого система перейдет в бесконечный цикл.                            
 При отсутвии задач вызываем обработчик idle или заглушку. 



 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        14 марта 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/

#include "kernel.h"

//******************************************************************************

kcodes kernel_scheulder(void)
{
    k_event event;
    kcodes result;
    uint16_t task_num;
    k_task *tasks = 0;   // Предупр. компилятора на необьявленную переменную

    DBG_PRINT(CORE_LVL,"%s","Scheulder started\n");
    
    while(true)
    {
        while (true)
        {
            // Перебираем все события и ставим в очередь задач
            while (true)
            {
                // Получаем событие
                result = kernel_event_pop(&event);
                
                // Событий нет, переходим к обработке очереди задач
                if (result == k_noevents)
                    break;

                // Извлекаем список обработчиков события
                kernel_get_event_handlers(event, tasks, &task_num);

                // Размещаем обработчики в очереди задач
                for (uint16_t i = 0 ; i < task_num ; i ++)
                    kernel_task_push(&tasks[i]);
            }

            // Извлекаем первую задачу из списка
            result = kernel_task_pop(tasks);

            // Список задач пуст, переходим к циклу сна
            if (result == k_task_list_empty)
                break;

            // Выполняем задачу. У задачи есть коды возврата,
            // но я их не обрабатываю пока что.
            tasks->handler();
        }

        //TODO событие о том что мы проснулись
        // Думаю нужны разные уведомления для разных режимов сна
        kernel_idle();
    }
}