/*******************************************************************************
 Файл содержит описание платформо-зависимый функций ядра

 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        6 мая 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/

kcodes 	 kernel_sysclock_init(void);
kcodes 	 kernel_systick_init(void);
kcodes 	 kernel_realtime_init(void);
kcodes   kernel_stdio_files_init(void);
kcodes 	 kernel_board_hw_init(void);
kcodes 	 kernel_board_hw_inspection(void);
kcodes 	 kernel_idle(void);
uint64_t kernel_get_systick(void);


