/*******************************************************************************
 В этой версии я не буду пытаться создать универсальную библиотеку
 
 
 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        26 июня 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/
#pragma once

#include "stm32l1xx_gpio.h"
#include "hld_gpio.h"

#define IOPORTA		GPIOA
#define IOPORTB		GPIOB
#define IOPORTH		GPIOH

typedef uint32_t 		ioportmask_t;
typedef uint32_t 		iomode_t;
typedef GPIO_TypeDef 	*ioportid_t;
typedef uint16_t 		iopadid_t;


/*******************************************************************************
Декларация функций
*******************************************************************************/
void _pal_lld_init();
void _pal_lld_setgroupmode(ioportid_t port,
                           ioportmask_t mask,
						   iomode_t mode);

/*******************************************************************************
Макросы-обертки для функций
*******************************************************************************/
#define pal_lld_setgroupmode(port, mask, mode)                      \
		_pal_lld_setgroupmode(port, mask, mode)

/*******************************************************************************
Макросы прямого доступа к портам ввода-вывода.
Такой подход существенно ускорит работу с выводами
*******************************************************************************/
#define pal_lld_readport(port) ((ioportmask_t)((port)->IDR))
#define pal_lld_writeport(port, bits) ((port)->ODR = (uint32_t)(bits))
#define pal_lld_setport(port, bits) ((port)->BSRR.H.set = (uint16_t)(bits))
#define pal_lld_clearport(port, bits) ((port)->BSRR.H.clear = (uint16_t)(bits))
#define pal_lld_readlatch(port) ((ioportmask_t)((port)->ODR))
#define pal_lld_init() _pal_lld_init()




