##########################################################################################################################
# File automatically-generated by tool: [projectgenerator] version: [3.5.2] date: [Sun Feb 16 15:18:46 CET 2020]
##########################################################################################################################

# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#	2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------

######################################
# target
######################################
TARGET = FreeRTOS


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# Build path
BUILD_DIR = Output

######################################
# source
######################################
# C sources
C_SOURCES =  \
MX_CubeGenerated/Src/main.c \
MX_CubeGenerated/Src/stm32f4xx_it.c \
MX_CubeGenerated/Src/stm32f4xx_hal_msp.c \
MX_CubeGenerated/Src/stm32f4xx_hal_timebase_tim.c \
MX_CubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c \
MX_CubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c \
MX_CubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c \
MX_CubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
MX_CubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c \
MX_CubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c \
MX_CubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c \
MX_CubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c \
MX_CubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
MX_CubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c \
MX_CubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
MX_CubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c \
MX_CubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c \
MX_CubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
MX_CubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
MX_CubeGenerated/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c \
MX_CubeGenerated/Src/system_stm32f4xx.c \
Framework/FreeRTOSv10.3.0/FreeRTOS/Source/tasks.c \
Framework/FreeRTOSv10.3.0/FreeRTOS/Source/list.c \
Framework/FreeRTOSv10.3.0/FreeRTOS/Source/queue.c \
Framework/FreeRTOSv10.3.0/FreeRTOS/Source/timers.c \
Framework/FreeRTOSv10.3.0/FreeRTOS/Source/event_groups.c \
Framework/FreeRTOSv10.3.0/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c \
Framework/FreeRTOSv10.3.0/FreeRTOS/Source/portable/MemMang/heap_1.c \
Source/OS.c \
Source/BSP/LEDs/LEDs.c \
Source/BSP/BSP.c \
Source/BSP/Communication/Console.c \
Source/BSP/Button/Button.c \
Source/RTOS_Examples/RTOS_Examples.c \
Source/RTOS_Examples/Queues/SimpleQueueExample.c \
Source/RTOS_Examples/Queues/PointerQueueExample.c \
Source/RTOS_Examples/Queues/SetQueueExample.c \
Source/RTOS_Examples/TaskTesting/TaskTesting.c \
Source/RTOS_Examples/SoftwareTimers/SimpleSoftwareTimers.c \
Source/RTOS_Examples/SoftwareTimers/SoftwareTimersWithId.c \
Source/RTOS_Examples/BinarySemaphores/BinarySemaphore.c \
Source/RTOS_Examples/CountingSemaphores/CountingSemaphore.c \
Source/RTOS_Examples/Mutex/SimpleMutexExample.c \
Source/RTOS_Examples/GatekeeperTaskExample/GatekeeperTaskExample.c \
Source/RTOS_Examples/EventGroups/EventGroupTest.c \
Source/RTOS_Examples/TaskNotification/TaskNotification.c \
Source/RTOS_Examples/TaskStatistic/TaskStatistic.c \


# ASM sources
ASM_SOURCES =  \
MX_CubeGenerated/startup_stm32f411xe.s


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DUSE_HAL_DRIVER \
-DSTM32F411xE


# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-IMX_CubeGenerated/Inc \
-IMX_CubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc \
-IMX_CubeGenerated/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy \
-IMX_CubeGenerated/Drivers/CMSIS/Device/ST/STM32F4xx/Include \
-IMX_CubeGenerated/Drivers/CMSIS/Include \
-IMX_CubeGenerated/Drivers/CMSIS/Include \
-IFramework/FreeRTOSv10.3.0/FreeRTOS/Source/include \
-IFramework/FreeRTOSv10.3.0/FreeRTOS/Source/portable/GCC/ARM_CM4F \
-IFramework/FreeRTOSv10.3.0 \

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = MX_CubeGenerated/STM32F411RETx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
ifneq ($(wildcard $(BUILD_DIR)/.*),)
	rmdir $(subst /, \\, $(BUILD_DIR)) /s /q
endif
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***