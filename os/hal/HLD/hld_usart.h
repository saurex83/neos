/*******************************************************************************
 В этой версии я не буду пытаться создать универсальную библиотеку
 Согласно идеологии ОС у нас нет постоянно работающих задач.
 Поэтому функция приема данных usart должна быть ассинхронной и вызывать 
 обработчик по завершению прием, в противном случаии приложение заблокирует
 выполнение остальных событий в ОС.
 
 Мне нужен такой результат:
 При приеме символа конца строки, вызывается пользовательский обработчки.
 Обработчик будет устанавливать событие о приеме строки и завершаться.
 Я предполагаю, что последовательным портом будет пользоватся только одна
 программа, поэтому блокировок не ввожу. 
 Передача данных будет происходиться синхронно.
 В итоге-асинхронный прием, синхронная передача.

 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        26 июня 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/
#pragma once

#include <stdint.h>


/*******************************************************************************
Экспортируемые функции
*******************************************************************************/

void uartInit(void);

void uartStart(void);
void uartStop(void);


void uartSend_sync(uint8_t *buf, uint8_t len);
void uartReceive_sync(uint8_t *buf, uint8_t len);

void uartSend_async(uint8_t *buf, uint8_t len, void (*callback)(void));
void uartReceive_async(uint8_t *buf, uint8_t len , void (*callback)(void));

/*
void uartObjectInit(UARTDriver *uartp);

void uartStart(UARTDriver *uartp, const UARTConfig *config);
void uartStop(UARTDriver *uartp);

void uartStartSend(UARTDriver *uartp, size_t n, const void *txbuf);
void uartStartReceive(UARTDriver *uartp, size_t n, void *rxbuf);
*/