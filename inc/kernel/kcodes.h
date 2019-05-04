/********************************************************************************
 Файл определений кодов возврата операционной системы.

 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        14 марта 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ********************************************************************************/

#pragma once

typedef enum kcodes // Коды возврата функций ядра
{
    k_ok = 0x00,
    k_noevents = 0x01,
    k_nosubscribe = 0x02,
    k_task_list_empty = 0x03,
    k_unit_test_not_passed = 0x04
} kcodes;