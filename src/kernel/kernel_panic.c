/*******************************************************************************
  Модуль ошибки ядра.                                                             

 При вызове функции core_kernel_panic производится регистрация
 ошибки. 
 

 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        26 марта 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/

// *file указатель на имя файла в текстовом представлении
// *line указатель на номер строки в текстовом представлении
// *str указатель на текст ошибки
void core_kernel_panic(char *file, int line, char *str)
{
    while (0);
}