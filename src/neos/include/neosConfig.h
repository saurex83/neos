/*******************************************************************************
 
 
 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        7 мая 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/


// Уровни отладки ядра. Для отключения отладки закоментируйте необходимую строку
#define DBGLVL1
#define DBGLVL2
#define DBGLVL3

#define EVENT_STACK_SIZE	16	// Размер буфера для хранения возникших событий
#define EVENT_COUNT_REG		16  // Количество событий доступных для регистрации 
#define EVENT_HNDL_MAX		32  // Количество обработчиков событий

#define TASK_Q_SIZE_MinP	16	//Размер очереди задач с низким приоритетом
#define TASK_Q_SIZE_MidP	16	//Размер очереди задач с средним приоритетом
#define TASK_Q_SIZE_MaxP	16	//Размер очереди задач с высоким приоритетом