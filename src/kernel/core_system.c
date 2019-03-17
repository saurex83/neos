/********************************************************************************/
/*                                                                              */
/*                                                                              */
/*                                                                              */
/*                                                                              */
/*                                                                              */
/*                                                                 */
/*               */
/*      */
/*                                                                              */
/*                                                                              */
/*                                                                              */
/*                                                                              */
/* Проект:      Neocore                                                         */
/* Автор:       Макшанов Олег Васильевич                                        */
/* Дата:        14 марта 2019г                                                  */
/* Версия:      0.1                                                             */
/* Компания:    ООО "ДиСиСи"                                                    */
/* mail:        pvp@dcconsult.ru                                                */
/********************************************************************************/
#include "kernel/kernel.h"
#include <stm32l1xx_rcc.h>

//********************************************************************************
kcodes core_init(void);
kcodes core_set_sysclock(void);
kcodes core_set_lse(void);


// Декларация внешних функций
kcodes core_event_manager_init(void);


// Первоначальная инициализация модулей ядра
kcodes core_init(void)
{
    core_event_manager_init();
    return 0;
}

// Установка системных часов, делителей шин переферии
kcodes core_set_sysclock(void)
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

    return k_ok;
}


// Установка внешнего кварца 32.768 кГц.
// Установку достаточно провести один раз при инициализации системы.
kcodes core_set_lse(void)
{

    return 0;
}