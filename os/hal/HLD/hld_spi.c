/*******************************************************************************
 В этой версии я не буду пытаться создать универсальную библиотеку
 
 
 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        26 июня 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/

/*******************************************************************************
Экспортируемые функции
*******************************************************************************/
#include <stdint.h>

extern void lld_spi1_read(uint8_t *buf, uint8_t len);
extern void lld_spi1_write(uint8_t *buf, uint8_t len);
extern void spi_lld_init();

void spiInit()
{
	spi_lld_init();	
} 

void spi1Receive_sync(uint8_t *buf, uint8_t len)
{
	lld_spi1_read(buf, len); 
}

void spi1Send_sync(uint8_t *buf, uint8_t len)
{
	lld_spi1_write(buf, len);
}

/*
void spiInit(void);
void spiObjectInit(SPIDriver *spip);

void spiStart(SPIDriver *spip, const SPIConfig *config);
void spiStop(SPIDriver *spip);


void spiSelect(SPIDriver *spip);
void spiUnselect(SPIDriver *spip);


void spiStartSend(SPIDriver *spip, size_t n, const void *txbuf);
void spiStartReceive(SPIDriver *spip, size_t n, void *rxbuf);


void spiSend(SPIDriver *spip, size_t n, const void *txbuf);
void spiReceive(SPIDriver *spip, size_t n, void *rxbuf);
*/