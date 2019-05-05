/*******************************************************************************
 Определение макроса для вывода отладочной информации.
 Макрос учитывает категории отладочной информации, вывод можно подавлять
 частично, в зависимости от того какой модуль отлаживается.

 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        14 марта 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/

#pragma once

#include <stdio.h>

// Определения переменных
#define DEBUG_ENABLE 	1
#define DEBUG_DISABLE 	0

// Категории отладочной информации
#define CORE_LVL		0x01
#define HAL_LVL			0x02

// Управление выводом отладочной информации
#define DEBUG			DEBUG_ENABLE
#define DEBUG_MASK 		(CORE_LVL | HAL_LVL)

#if DEBUG == DEBUG_ENABLE
#define DBG_PRINT(DEBUG_CATEGORY, fmt, ...)								\
		do { if (DEBUG_CATEGORY & DEBUG_MASK) 							\
		fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, 					\
        		__LINE__, __func__, __VA_ARGS__);} 						\
		while (0);										
#endif

#if DEBUG == DEBUG_DISABLE
#define DBG_PRINT(DEBUG_CATEGORY, VALUE)	while (0);
#endif				

/*
#define debug_print(fmt, ...) \
        do { if (DEBUG) fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
                                __LINE__, __func__, __VA_ARGS__); } while (0)
*/