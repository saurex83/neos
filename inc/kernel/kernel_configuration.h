#include "stdint.h"








// Менеджер событий
#define EVENT_QUERY_LENGTH  (16)    // Глубина буфера событий. +1 см. в менеджере 
#define LISTENER_QUERY_LENGTH (128)  // Максимальное количестов подписчеков на события
#define TASK_LIST_LENGTH (128) // Длина очереди задач 