/*******************************************************************************
 Модуль управления тактовой подсистемой микроконтроллера.

 TODO подумать как можно получать еще мкс. Возможно при прерывании мс запускать 
  другой таймер который считает мкс. ввести функцию hal_get_systick_us которая 
  возращала бы число мкс прошедшее с последней мс. Программно считать мкс н
  икакой производительности не хватит. Может как то таймеры можно связать, чтоб 
  при счете 1 мс автоматически сбрасывался таймер мкс. hal_get_systick_us
  возращала бы sys_ticks и sys_ticks_us (показания мкс таймера). Если сделать
   на аппаратном уровне будет очень быстро

 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        14 марта 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/

#include "hal/hal.h"
#include <stm32l1xx_rcc.h>

// Глобальные переменные модуля
volatile uint64_t sys_ticks;    // Счетчик системных тиков 


// Установка системных часов, делителей шин переферии
hal_retcode hal_start_sysclock(void)
{
    RCC_DeInit();

    // Включаем встроеный высокочастотный генератор
    RCC_HSICmd(ENABLE);

    // Дожидаемся готовности
    while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

    // SYSCLK = HSI
    RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI );

    // AHB = HSI
    RCC_HCLKConfig(RCC_SYSCLK_Div1);

    // APB1 = HSI
    RCC_PCLK1Config(RCC_HCLK_Div1);

    // APB2 = HSI
    RCC_PCLK2Config(RCC_HCLK_Div1);

    SystemCoreClockUpdate();

    return hal_ok;
}

// Настройка системного таймера
hal_retcode hal_start_systick(void)
{
    uint32_t clk_freq;
    
    //Получаем значение системной частоты в герцах.
    RCC_ClocksTypeDef RCC_Clocks;
    RCC_GetClocksFreq (&RCC_Clocks);
    clk_freq = RCC_Clocks.HCLK_Frequency;

    // Количество тиков после которого сработает прерывание
    uint32_t ticks =  clk_freq/ SYSTICK_FREQ;
    SysTick_Config (ticks);

    return hal_ok;
}

uint64_t hal_get_systick(void)
{
    return sys_ticks;
}

// Обработчик прерываний системного таймера
// 64 битная переменная истекает через 58 млн. лет
void SysTick_Handler (void)
 {
   sys_ticks++;
 }