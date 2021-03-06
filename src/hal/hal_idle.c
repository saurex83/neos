/*******************************************************************************
 Модуль пониженного энергосбережения.
                                                            
 Модуль определяет требуемый тип режима снижения энергопоребления  в          
 зависимости от активных модулей (uart, spi, adc) и переводит МК в режим      
 пониженного энергопотребления. Если все модули выключены, то переходим       
 в режим глубокого сна, выход их которого возможен только по таймеру LSE      
 По умолчанию таймер LSE будет установлен на стандартное значение             
 определенное в файле kernel_conguration.h                                    

 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        14 марта 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/

#include "hal/hal.h"
#include <stm32l1xx_rcc.h>

hal_retcode hal_idle_init(void)
{

    return 0;
}



// Настройка системного таймера
hal_retcode hal_idle(void)
{
    return hal_ok;
}