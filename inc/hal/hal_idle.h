/********************************************************************************
 Модуль пониженного энергосбережения.



 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        14 марта 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ********************************************************************************/
#include "hal/hal.h"

#pragma once

hal_retcode hal_idle_init(void);
hal_retcode hal_idle(void);