/*******************************************************************************
 Макросы для вывода отладочной информации
 
 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        7 мая 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/

#pragma once

#include "kernel_fprintf.h"

#define DPRNT(fmt, ...)									
		kernel_fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__,	\		
        		__LINE__, __func__, __VA_ARGS__);				\

#define NOPRNT 	while (0);	

#ifdef DBGLVL1 													
#define	DBG_PRINT_LVL1 DPRNT							
#else
#define DBG_PRINT_LVL1 NOPRNT
#endif

#ifdef DBGLVL2												
#define	DBG_PRINT_LVL2 DPRNT							
#else
#define DBG_PRINT_LVL2 NOPRNT
#endif

#ifdef DBGLVL3													
#define	DBG_PRINT_LVL3 DPRNT							
#else
#define DBG_PRINT_LVL3 NOPRNT
#endif