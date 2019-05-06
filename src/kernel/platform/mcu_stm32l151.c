/*******************************************************************************
 Файл содержит описание платформо-зависимый функций ядра

 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        6 мая 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/

#include "kernel/kernel.h"
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/unistd.h>

#include <stm32l1xx_rcc.h>

// Частота работы системного таймера. 1 мс
#define SYSTICK_FREQ    (uint32_t) 1000 

// Глобальные переменные модуля
// TODO точно volatile?
volatile uint64_t sys_ticks;

kcodes 	 kernel_sysclock_init(void);
kcodes 	 kernel_systick_init(void);
kcodes 	 kernel_realtime_init(void);
kcodes   kernel_idle(void);
kcodes   kernel_board_hw_init(void);
uint64_t kernel_get_systick(void);


// Установка системных часов, делителей шин переферии
kcodes kernel_sysclock_init(void)
{
    RCC_DeInit();
    RCC_HSICmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
    RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    RCC_PCLK1Config(RCC_HCLK_Div1);
    RCC_PCLK2Config(RCC_HCLK_Div1);
    SystemCoreClockUpdate();
    return k_ok;
}

// Настройка системного таймера
kcodes kernel_systick_init(void)
{
    uint32_t clk_freq;
    
    RCC_ClocksTypeDef RCC_Clocks;
    RCC_GetClocksFreq (&RCC_Clocks);
    clk_freq = RCC_Clocks.HCLK_Frequency;

    uint32_t ticks =  clk_freq/ SYSTICK_FREQ;
    SysTick_Config (ticks);
    return k_ok;
}

uint64_t kernel_get_systick(void)
{
    return sys_ticks;
}

// Настройка часов реального времени
kcodes kernel_realtime_init(void)
{
    return k_ok;
}

// Обработчик прерываний системного таймера
// 64 битная переменная истекает через 58 млн. лет
void SysTick_Handler (void)
 {
   sys_ticks++;
 }

// Настраиваем потоки ввода вывода fprintf
kcodes kernel_stdio_files_init(void)
{
		setvbuf(stderr, NULL, _IONBF, 0);
		setvbuf(stdout, NULL, _IONBF, 0);
		setvbuf(stdin,  NULL, _IONBF, 0);
		return k_ok;
}

// Проверка работоспособности аппаратуры
kcodes kernel_board_hw_inspection(void)
{
	return k_ok;
}

int _read(int file, char *data, int len)
{
    int bytes_read;

    if (file != STDIN_FILENO)
    {
        errno = EBADF;
        return -1;
    }

    for (bytes_read = 0; bytes_read < len; bytes_read++)
    {
        //*data = (char) UART_RxBlocking();
        data++;
    }

    return bytes_read;
}

int _write(int file, char *data, int len)
{
    int bytes_written;

    if ((file != STDOUT_FILENO) && (file != STDERR_FILENO))
    {
        errno = EBADF;
        return -1;
    }

    for (bytes_written = 0; bytes_written < len; bytes_written++)
    {
       // UART_TxBlocking(*data);
        data++;
    }

    return bytes_written;
}

int _close(int file)
{
    return -1;
}

int _lseek(int file, int ptr, int dir)
{
    return 0;
}

int _fstat(int file, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

int _isatty(int file)
{
    if ((file == STDOUT_FILENO) ||
        (file == STDIN_FILENO) ||
        (file == STDERR_FILENO))
    {
        return 1;
    }

    errno = EBADF;
    return 0;
}


kcodes kernel_idle(void)
{
    return k_ok;
}

kcodes   kernel_board_hw_init(void)
{
    return k_ok;
}