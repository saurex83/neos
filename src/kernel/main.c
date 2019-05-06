/*******************************************************************************
 



 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        14 марта 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/

#include "kernel.h"
#include "platform/kernel_hw.h"

int main(void)
{
    int result;
    
    result = kernel_sysclock_init();  
    result = kernel_systick_init();  
    result = kernel_realtime_init();
    result = kernel_stdio_files_init();
    
    DBG_PRINT(CORE_LVL,"%s","Kernel hardware started\n");

    result = kernel_board_hw_init();

    DBG_PRINT(CORE_LVL,"%s","Board hardware started\n");
    
    result = kernel_board_hw_inspection();

    result = kernel_event_manager_init();

    result = kernel_event_push(event_booted);

    result = kernel_scheulder();

    return result;
}