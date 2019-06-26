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
void spiInit(void);
void spiObjectInit(SPIDriver *spip);

void spiStart(SPIDriver *spip, const SPIConfig *config);
void spiStop(SPIDriver *spip);

// выбор чипселекта
void spiSelect(SPIDriver *spip);
void spiUnselect(SPIDriver *spip);

// асинхронные функции. в конце передачи вызывается callback
void spiStartSend(SPIDriver *spip, size_t n, const void *txbuf);
void spiStartReceive(SPIDriver *spip, size_t n, void *rxbuf);

// Синхронные функции
void spiSend(SPIDriver *spip, size_t n, const void *txbuf);
void spiReceive(SPIDriver *spip, size_t n, void *rxbuf);