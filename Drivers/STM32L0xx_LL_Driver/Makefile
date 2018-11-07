# Tools and options
PREFIX  = arm-none-eabi
CC      = $(PREFIX)-gcc
AR      = $(PREFIX)-ar

# The flags passed to the compiler
CFLAGS  = -mthumb \
        -mcpu=cortex-m0plus \
        -std=c99 \
        -Wall \
        -ffunction-sections \
        -fdata-sections

# Paths
INC_PATHS   = -IInclude \
        -I../CMSIS/Include \
        -I../Device/ST/STM32L0xx/Include
LIB_PATHS   =
SRC_PATH    = Source/
OUT_PATH    = gcc/

# Libs
LIBS    = -lc

# Definitions
DEFS    = -DUSE_FULL_LL_DRIVER=1 \
        -DSTM32L053xx

OBJS    = $(OUT_PATH)stm32l0xx_ll_adc.o \
        $(OUT_PATH)stm32l0xx_ll_comp.o \
        $(OUT_PATH)stm32l0xx_ll_crc.o \
        $(OUT_PATH)stm32l0xx_ll_crs.o \
        $(OUT_PATH)stm32l0xx_ll_dac.o \
        $(OUT_PATH)stm32l0xx_ll_dma.o \
        $(OUT_PATH)stm32l0xx_ll_exti.o \
        $(OUT_PATH)stm32l0xx_ll_gpio.o \
        $(OUT_PATH)stm32l0xx_ll_i2c.o \
        $(OUT_PATH)stm32l0xx_ll_irq.o \
        $(OUT_PATH)stm32l0xx_ll_lptim.o \
        $(OUT_PATH)stm32l0xx_ll_lpuart.o \
        $(OUT_PATH)stm32l0xx_ll_pwr.o \
        $(OUT_PATH)stm32l0xx_ll_rcc.o \
        $(OUT_PATH)stm32l0xx_ll_rng.o \
        $(OUT_PATH)stm32l0xx_ll_rtc.o \
        $(OUT_PATH)stm32l0xx_ll_spi.o \
        $(OUT_PATH)stm32l0xx_ll_tim.o \
        $(OUT_PATH)stm32l0xx_ll_usart.o \
        $(OUT_PATH)stm32l0xx_ll_utils.o \
        $(OUT_PATH)system_stm32l0xx.o

LIB = $(OUT_PATH)libdriver.a

# The main Release target
Release: CFLAGS += -O2
Release: DEFS += -DNDEBUG
Release: $(LIB)
.PHONY: Release

# The main Debug target
Debug: CFLAGS += -g
Debug: DEFS += -DUSE_FULL_ASSERT=1
Debug: DEFS += -DDEBUG
Debug: $(LIB)
.PHONY: Debug

# Clean target
clean:
	$(RM) $(LIB) $(OBJS)
.PHONY: clean

# The library depends
$(LIB): $(OBJS) Makefile

# Objects depend
$(OBJS): Makefile

# Implicit rule
$(OUT_PATH)%.o: $(SRC_PATH)%.c
	$(CC) -c $(CFLAGS) $(INC_PATHS) $(DEFS) $(<) -o $(@)

# Implicit rule
$(OUT_PATH)%.a:
	$(AR) -crs $(@) $(filter %.o, $(^))
