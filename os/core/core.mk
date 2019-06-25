TMP_DIR  := $(NEOS_DIR)/os/core

CORE_INC += $(TMP_DIR)

CORE_SRC += $(TMP_DIR)/co_events.c
CORE_SRC += $(TMP_DIR)/co_panic.c
CORE_SRC += $(TMP_DIR)/co_schedule.c