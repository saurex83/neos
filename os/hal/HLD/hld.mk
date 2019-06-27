TMP_DIR := $(NEOS_DIR)/os/hal/HLD

HAL_INC += $(TMP_DIR)

HAL_SRC += $(TMP_DIR)/hld_spi.c
HAL_SRC += $(TMP_DIR)/hld_gpio.c