#include "stm32l1xx.h"

#define PIN_SPI1_MISO	GPIO_Pin_6
#define PIN_SPI1_MOSI	GPIO_Pin_7
#define PIN_SPI_SCK		GPIO_Pin_5

inline static void spi1_gpio_init()
{
	GPIO_InitTypeDef gpio_s;	

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	gpio_s.GPIO_Pin = PIN_SPI1_MISO;
	gpio_s.GPIO_Mode = GPIO_Mode_AF;
	gpio_s.GPIO_Speed = GPIO_Speed_40MHz;
	gpio_s.GPIO_OType = GPIO_OType_PP;
	gpio_s.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &gpio_s);

	gpio_s.GPIO_Pin = PIN_SPI1_MOSI | PIN_SPI_SCK;
	gpio_s.GPIO_Mode = GPIO_Mode_AF;
	gpio_s.GPIO_Speed = GPIO_Speed_40MHz;
	gpio_s.GPIO_OType = GPIO_OType_PP;
	gpio_s.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &gpio_s);

	GPIO_PinAFConfig( GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig( GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
	GPIO_PinAFConfig( GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
}

inline static void spi1_init()
{
	SPI_InitTypeDef spi_s;
	SPI_I2S_DeInit(SPI1);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

	SPI_StructInit(&spi_s);
	spi_s.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	spi_s.SPI_Mode = SPI_Mode_Master;
	spi_s.SPI_DataSize = SPI_DataSize_8b;
	spi_s.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	spi_s.SPI_NSS = SPI_NSS_Soft;
	spi_s.SPI_CPOL = SPI_CPOL_Low;
	spi_s.SPI_CPHA = SPI_CPHA_1Edge;
	spi_s.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_Init(SPI1, &spi_s);
	SPI_Cmd(SPI1, ENABLE);
	SPI_NSSInternalSoftwareConfig(SPI1, SPI_NSSInternalSoft_Set);
}

inline static void spi1_dma_init()
{
	DMA_InitTypeDef dma;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	dma.DMA_PeripheralBaseAddr = (uint32_t) (&(SPI1->DR));
	dma.DMA_DIR = DMA_DIR_PeripheralDST;
	dma.DMA_M2M = DMA_M2M_Disable;
	dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dma.DMA_Mode = DMA_Mode_Normal;
	dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dma.DMA_Priority = DMA_Priority_Medium;
	DMA_Init(DMA1_Channel3, &dma);
	SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
	dma.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_Init(DMA1_Channel2, &dma);
	SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Rx, ENABLE);
}

void spi_lld_init()
{ 
	spi1_gpio_init();
	spi1_init();
	spi1_dma_init();
}

void lld_spi1_write(uint8_t *buf, uint8_t len) 
{
	DMA1_Channel3->CNDTR = len;
	DMA1_Channel3->CMAR = (uint32_t) buf;
	DMA_Cmd(DMA1_Channel3, ENABLE);
	while (DMA_GetFlagStatus(DMA1_FLAG_TC3) == RESET)
		;
	DMA_Cmd(DMA1_Channel3, DISABLE);
	DMA_ClearFlag(DMA1_FLAG_GL3);
}

void lld_spi1_read(uint8_t *buf, uint8_t len) 
{
	DMA1_Channel3->CNDTR = len;
	DMA1_Channel3->CMAR = (uint32_t) buf;
	DMA1_Channel2->CNDTR = len;
	DMA1_Channel2->CMAR = (uint32_t) buf;
	DMA_Cmd(DMA1_Channel2, ENABLE);
	DMA_Cmd(DMA1_Channel3, ENABLE);
	while (DMA_GetFlagStatus(DMA1_FLAG_TC3) == RESET)
		;
	while (DMA_GetFlagStatus(DMA1_FLAG_TC2) == RESET)
		;
	DMA_Cmd(DMA1_Channel3, DISABLE);
	DMA_Cmd(DMA1_Channel2, DISABLE);
	DMA_ClearFlag(DMA1_FLAG_GL3);
	DMA_ClearFlag(DMA1_FLAG_GL2);
}