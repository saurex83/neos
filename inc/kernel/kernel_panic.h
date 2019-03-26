/********************************************************************************
 Модуль ошибки ядра.                                                             




 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        26 марта 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ********************************************************************************/

void core_kernel_panic(char *file, int line, char *str);


// пример
// #include "kernel/kernel_panic.h"
// core_kernel_panic( __FILE__, __LINE__, "Event is not registrated");