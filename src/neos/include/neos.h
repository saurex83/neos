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
#include "neosConfig.h"
#include "portable.h"

#include "debug.h"

void kernel_panic(char *file, int line, char *str);
