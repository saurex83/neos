#include "kernel/kernel.h"
#include <stm32l1xx_rcc.h>


// Глобальные переменные модуля
volatile uint64_t sys_ticks;    // Счетчик системных тиков 

//********************************************************************************
kcodes core_set_systick(void);
uint64_t core_get_ms(void);
void SysTick_Handler (void);


// Настройка системного таймера
kcodes core_set_systick(void)
{
    uint32_t clk_freq;
    
    //Получаем значение системной частоты в герцах.
    RCC_ClocksTypeDef RCC_Clocks;
    RCC_GetClocksFreq (&RCC_Clocks);
    clk_freq = RCC_Clocks.HCLK_Frequency;

    // Количество тиков после которого сработает прерывание
    uint32_t ticks =  clk_freq/ SYSTICK_FREQ;
    SysTick_Config (ticks);

    return k_ok;
}


uint64_t core_get_ms(void)
{
    return sys_ticks;
}


// Обработчик прерываний системного таймера
// 64 битная переменная истекает через 58 млн. лет
void SysTick_Handler (void)
 {
   sys_ticks++;
 }