#include "stdint.h"


#define SYSTICK_FREQ    (uint32_t) 1000 // Частота работы системного таймера. 1 мс





// Менеджер событий
#define EVENT_QUERY_LENGTH  (16)    // Глубина буфера событий. +1 см. в менеджере 
#define LISTENER_QUERY_LENGTH (128)  // Максимальное количестов подписчеков на события