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

#define MIN_PRIORITY	0x00
#define MAX_PRIORITY	0xFF

typedef void (*taskF)(void);
typedef uint8_t taskP;

typedef struct
{
    taskP taskP;
    taskF taskF;
} task_t;

void xTaskWrite(task_t *task);
int xTaskRead(task_t *task);