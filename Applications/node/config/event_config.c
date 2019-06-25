/*******************************************************************************
 В этом модуле устанавливаются подписчики на события


 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        25 июня 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/

#include "co_events.h"
#include "events_defs.h"

void stub()
{
}

EVENT_SUBSCRIBERS_CHAIN_BEGIN(Oleg)
	SUBSCRIBER(stub),
	SUBSCRIBER(stub),
	SUBSCRIBER(stub)
EVENT_SUBSCRIBERS_CHAIN_END


EVENT_TO_SUBSCRIBERS_CHAIN_MAP_BEGIN
	REG_SUB_CHAIN(start_ev,Oleg),
	REG_SUB_CHAIN(start_ev,Oleg),
	REG_SUB_CHAIN(start_ev,Oleg),
EVENT_TO_SUBSCRIBERS_CHAIN_MAP_END
