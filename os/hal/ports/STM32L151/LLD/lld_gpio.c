/*******************************************************************************
 В этой версии я не буду пытаться создать универсальную библиотеку
 
 
 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        26 июня 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/
/*
#undef PAL_MODE_RESET
#undef PAL_MODE_UNCONNECTED
#undef PAL_MODE_INPUT
#undef PAL_MODE_INPUT_PULLUP
#undef PAL_MODE_INPUT_PULLDOWN
#undef PAL_MODE_INPUT_ANALOG
#undef PAL_MODE_OUTPUT_PUSHPULL
#undef PAL_MODE_OUTPUT_OPENDRAIN
*/

#include "lld_gpio.h"


void _pal_lld_setgroupmode(ioportid_t port,
                           ioportmask_t mask,
						   iomode_t mode)
{
	GPIO_InitTypeDef gpio_s;

	gpio_s.GPIO_Pin = mask;
	gpio_s.GPIO_Speed = GPIO_Speed_40MHz;
	gpio_s.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio_s.GPIO_Mode = GPIO_Mode_IN;

	if (mode == PAL_MODE_RESET)
	{
		gpio_s.GPIO_Speed = GPIO_Speed_400KHz;
	}
	else if (mode == PAL_MODE_UNCONNECTED)
	{
		gpio_s.GPIO_Speed = GPIO_Speed_400KHz;
	}
	else if (mode == PAL_MODE_INPUT)
	{

	}
	else if (mode == PAL_MODE_INPUT_PULLUP)
	{
		gpio_s.GPIO_PuPd = GPIO_PuPd_UP;		
	}
	else if (mode == PAL_MODE_INPUT_PULLDOWN)
	{
		gpio_s.GPIO_PuPd = GPIO_PuPd_DOWN;
	}
	else if (mode == PAL_MODE_INPUT_ANALOG)
	{
		gpio_s.GPIO_Mode = GPIO_Mode_AN;
	}
	else if (mode == PAL_MODE_OUTPUT_PUSHPULL)
	{
		gpio_s.GPIO_Mode = GPIO_Mode_OUT;
		gpio_s.GPIO_OType = GPIO_OType_PP;
	}
	else if (mode == PAL_MODE_OUTPUT_OPENDRAIN)
	{
		gpio_s.GPIO_Mode = GPIO_Mode_OUT;
		gpio_s.GPIO_OType = GPIO_OType_OD;
	}

	GPIO_Init(port, &gpio_s);
} 


void _pal_lld_init() 
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOH, ENABLE);
}
