/*******************************************************************************
 В этой версии я не буду пытаться создать универсальную библиотеку
 
 
 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        26 июня 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/

#include "hld_gpio.h"
#include "hld_spi.h"
#include "hld_usart.h"

// эта функция иницилизирует все модули которые используются
// в оригинали какой модуль активен определют условной компиляцией
void halInit(void) ;