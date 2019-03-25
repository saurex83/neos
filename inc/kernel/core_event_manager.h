#include "kernel/kernel.h"

kcodes core_event_manager_init(void);
kcodes core_post_event(k_event event);
kcodes core_pop_event(k_event *event);