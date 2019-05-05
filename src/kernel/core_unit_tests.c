/*******************************************************************************
 Модульное тестирование



 Проект:      Neocore                                                         
 Автор:       Макшанов Олег Васильевич                                     
 Дата:        14 марта 2019г                                               
 Версия:      0.1                                                          
 Компания:    ООО "ДиСиСи"                                                 
 mail:        pvp@dcconsult.ru 
 ******************************************************************************/

#define UNIT_TEST_FUNC_LIST_SIZE (sizeof(UNIT_TEST_FUNC_LIST) / sizeof(test_item))

#include "kernel/kernel.h"

static bool no_problems;

typedef int (*proto_utest_fun)(char *msg);

/******************************************************************************/
// Декларация внешних функция тестирования
static int stub_f(char *msg); // Заглушка
int TUNIT_task_manager_test_1(char *msg);
int TUNIT_event_handlers_test_1(char *msg);
int TUNIT_event_manager_test_1(char *msg);

typedef struct 
{
    proto_utest_fun test_func;
    bool result;
} test_item;

test_item UNIT_TEST_FUNC_LIST[] = {
// Для добавления функции сначало поместите ее в раздел декларация
// а потом по шаблону добавте в список
//  {.test_func = FNAME}
   {.test_func = stub_f },   // Заглушка нужно чтобы компилятор не ругался
   {.test_func = TUNIT_task_manager_test_1},
   {.test_func = TUNIT_event_handlers_test_1},
   {.test_func = TUNIT_event_manager_test_1}
};


kcodes execute_unit_tests(void)
{
    no_problems = true;
    int result;
    char *msg = 0;

    for (uint16_t i =0; i< UNIT_TEST_FUNC_LIST_SIZE ; i++)
    {
        result = UNIT_TEST_FUNC_LIST[i].test_func(msg);
        UNIT_TEST_FUNC_LIST[i].result = result;
        
        if (result != 0) 
            no_problems = false;
    }

    if (!no_problems)
        return k_unit_test_not_passed;

    // TODO помигать светодиодами если тесты не прошли
    
    return k_ok;
}

static int stub_f(char *msg)
{
    return 0;
}