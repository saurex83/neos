
# Дефайны
#-------------------------------------------------------------------------------
DEFINES += USE_STDPERIPH_DRIVER
DEFINES += STM32L1XX_MD
DEFINES += STM32L151xB

TMP_DIR := $(NEOS_DIR)/os/hal/ports/STM32L151

LDSCR_PATH = $(TMP_DIR)/ld-scripts
LDSCRIPT   = stm32_flash.ld

PORT_INC +=$(TMP_DIR)/cmsis
PORT_INC +=$(TMP_DIR)/stdperiph

PORT_SRC += $(TMP_DIR)/startup/startup_stm32l1xx_md.s
PORT_SRC += $(TMP_DIR)/cmsis/system_stm32l1xx.c
PORT_SRC += $(TMP_DIR)/stdperiph/misc.c
PORT_SRC += $(TMP_DIR)/stdperiph/misc.c
PORT_SRC += $(TMP_DIR)/stdperiph/stm32l1xx_adc.c
PORT_SRC += $(TMP_DIR)/stdperiph/stm32l1xx_aes.c
PORT_SRC += $(TMP_DIR)/stdperiph/stm32l1xx_aes_util.c
PORT_SRC += $(TMP_DIR)/stdperiph/stm32l1xx_comp.c
PORT_SRC += $(TMP_DIR)/stdperiph/stm32l1xx_crc.c
PORT_SRC += $(TMP_DIR)/stdperiph/stm32l1xx_dac.c
PORT_SRC += $(TMP_DIR)/stdperiph/stm32l1xx_dbgmcu.c
PORT_SRC += $(TMP_DIR)/stdperiph/stm32l1xx_dma.c
PORT_SRC += $(TMP_DIR)/stdperiph/stm32l1xx_exti.c
PORT_SRC += $(TMP_DIR)/stdperiph/stm32l1xx_flash.c
PORT_SRC += $(TMP_DIR)/stdperiph/stm32l1xx_flash_ramfunc.c
PORT_SRC += $(TMP_DIR)/stdperiph/stm32l1xx_fsmc.c
PORT_SRC += $(TMP_DIR)/stdperiph/stm32l1xx_gpio.c
PORT_SRC += $(TMP_DIR)/stdperiph/stm32l1xx_i2c.c
PORT_SRC += $(TMP_DIR)/stdperiph/stm32l1xx_iwdg.c
PORT_SRC += $(TMP_DIR)/stdperiph/stm32l1xx_lcd.c
PORT_SRC += $(TMP_DIR)/stdperiph/stm32l1xx_opamp.c
PORT_SRC += $(TMP_DIR)/stdperiph/stm32l1xx_pwr.c
PORT_SRC += $(TMP_DIR)/stdperiph/stm32l1xx_rcc.c
PORT_SRC += $(TMP_DIR)/stdperiph/stm32l1xx_rtc.c
PORT_SRC += $(TMP_DIR)/stdperiph/stm32l1xx_sdio.c
PORT_SRC += $(TMP_DIR)/stdperiph/stm32l1xx_spi.c
PORT_SRC += $(TMP_DIR)/stdperiph/stm32l1xx_syscfg.c
PORT_SRC += $(TMP_DIR)/stdperiph/stm32l1xx_tim.c
PORT_SRC += $(TMP_DIR)/stdperiph/stm32l1xx_usart.c
PORT_SRC += $(TMP_DIR)/stdperiph/stm32l1xx_wwdg.c