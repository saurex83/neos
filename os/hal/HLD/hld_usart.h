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


/*******************************************************************************
Экспортируемые функции
*******************************************************************************/

void uartInit(void);
void uartObjectInit(UARTDriver *uartp);

void uartStart(UARTDriver *uartp, const UARTConfig *config);
void uartStop(UARTDriver *uartp);

void uartStartSend(UARTDriver *uartp, size_t n, const void *txbuf);
void uartStartReceive(UARTDriver *uartp, size_t n, void *rxbuf);
