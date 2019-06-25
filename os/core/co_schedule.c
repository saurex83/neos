/*******************************************************************************
 
 
 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        7 мая 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/
#include "neos.h"
#include "co_events.h"

void co_idle(void) __attribute__ ((weak));

// Запускаем планировщик задач
void coreStartSchedule(void)
{
	event_t event;
	subscriber_t *sub_list;

	while (true)
	{
		if (!coreGetEvent(&event))
			{
				co_idle();
				continue;
			}
		
		sub_list = coreGetSubscribers(event);

		while (*sub_list != SUB_CHAIN_END)
		{
			(*sub_list)();
			sub_list++;
		}
	}
}

void co_idle(void) 
{

}