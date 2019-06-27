.DEFAULT_GOAL := all

# Имя проекта
#-------------------------------------------------------------------------------
TARGET  = neos_node

# Корневой путь проекта
NEOS_DIR :=../..

# Исходный код для сборки приложений 
#-------------------------------------------------------------------------------
APP_SRC += main.c 
APP_INC += 

include config/config.mk
include drivers/drivers.mk


GDB := gdb-multiarch  -ex "target remote localhost:4242" -tui

programm:
	st-flash write  $(NEOS_DIR)/bin/$(TARGET).hex  0x08000000

connect: 
	st-util -2

debug:
	@$(GDB)  $(NEOS_DIR)/bin/$(TARGET).elf



# Включение файлов сборки проекта 
#-------------------------------------------------------------------------------
include $(NEOS_DIR)/os/common/buildrules.mk
