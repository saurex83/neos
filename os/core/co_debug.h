/*******************************************************************************
 Макросы для вывода отладочной информации
 
 В отладочном режиме вызываем sys_halt которая тормозит выполнение программы.
 В sys_halt поставим точку останова gdb.

 В рабочим режиме перезагрузим МК

 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        7 мая 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/

#pragma once

#include <stddef.h>
#include <stdint.h>

#if !defined(chDbgCheck)
#define chDbgCheck(c) do {} while(false);
#endif

#if !defined(chDbgAssert)
#define chDbgAssert(c, r) do {} while(false);					
#endif
