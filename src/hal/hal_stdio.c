/*******************************************************************************
 Определение стандартных потоков вводв/вывода                                
 Модуль переопределяет стандартные потоки на интерфейс uart.
 
 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        14 марта 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/

#include "hal/hal.h"
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/unistd.h>

hal_retcode hal_stdio_init(void)
{
		setvbuf(stderr, NULL, _IONBF, 0);
		setvbuf(stdout, NULL, _IONBF, 0);
		setvbuf(stdin, NULL, _IONBF, 0);
		return hal_ok;
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