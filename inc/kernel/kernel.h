
#include "kernel/kernel_configuration.h"
#include "stdint.h"
#include "stdbool.h"

//********************************
// Определения типов
//********************************

typedef enum kcodes // Коды возврата функций ядра
{
    k_ok = 0x00,
    k_noevents =0x01
} kcodes;


typedef uint8_t k_event; // Событие ядра
typedef kcodes (*task_hndl)(void); // Обработчик задачи

// Перечень событий в системе. Все возможные события должны
// быть перечисленныу в перечислении. Компиляция событий статическая
// для ускорения работы
typedef enum event_id
{
    event_booted
} event_id;


typedef enum task_priority // Перечень приоритетов задач
{
    high_priority = 0,
    middle_priority = 50,
    low_prioritty = 100,
} task_priority;

// Определяем задачу, параметры вызова

//********************************
// Системные часы
//********************************

kcodes      core_set_sysclock(void); 
uint64_t    core_get_ms(void);

//********************************
// Менеджер событий
//********************************

kcodes core_pop_event(uint8_t *event);
kcodes core_post_event(uint8_t event);

//********************************
// Регистратор подписчиков
//********************************

kcodes core_subscribe_events(task_hndl hndl, k_event ev, task_priority pri);