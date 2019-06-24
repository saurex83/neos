/*******************************************************************************
 
 
 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        7 мая 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/

// Режимы энергосбережиения. LP1 самый низкий
typedef enum 
{
	LP1, LP2, LP3
} idleState;

typedef void (*sys_hnl)(void);

void xSystemIdle(idleState state);
void xSystemWDT_SetHandler(sys_hnl handler);	// Установить обр. WDT
void xSystemEXP_SetHandler(sys_hnl handler);	// Установить обр. исключений
void xSystemSysClock(void);
void xSystemSysTick(void);
int xSystemDBG_write(int fd, char *str, int len); // Для kernel_printf