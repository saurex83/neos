/*******************************************************************************
 
 
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
#include <stdbool.h>
#include "neosConfig.h"
#include "co_debug.h"
#include "co_events.h"


void core_panic(char *file, int line, char *str);
void coreStartSchedule(void);

// Эта функция вызывается когда событий к обработке больше нет
void co_idle(void);

#define MALFUNCTION(text_note) core_panic(__FILE__, __LINE__ , text_note);	




