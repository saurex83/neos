/********************************************************************************
 Менеджер событий.



 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        14 марта 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ********************************************************************************/

#include "kernel/kernel.h"

#pragma once

kcodes core_event_manager_init(void);
kcodes core_post_event(k_event event);
kcodes core_pop_event(k_event *event);