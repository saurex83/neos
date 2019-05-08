/*******************************************************************************
 
 
 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        7 мая 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/

#pragma once

#include "neos.h" 
#include "tasks.h"

typedef uint8_t event_t;

void xWriteEvent(event_t event);
int xReadEvent(event_t *event); 
void xRegEventHandler(event_t event, task_t *task);
void xExtractEventHandler(event_t event);
int xExtractHandler(task_t *task);