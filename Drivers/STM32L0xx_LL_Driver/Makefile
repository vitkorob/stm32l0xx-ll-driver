# Tools and options
PREFIX  = arm-none-eabi
CC      = $(PREFIX)-gcc
AR      = $(PREFIX)-ar
LD      = $(PREFIX)-ld
OBJCOPY = $(PREFIX)-objcopy
MKDIR   = mkdir -p

# Paths
INC_PATHS   = -IInclude \
        -I../CMSIS/Include \
        -I../Device/ST/STM32L0xx/Include
LIB_PATHS   =
SRC_PATHS   = Source
OUT_PATH    = gcc

# The flags passed to the compiler
CFLAGS  = -mthumb \
        -mcpu=cortex-m0plus \
        -std=c99 \
        -Wall \
        -ffunction-sections \
        -fdata-sections

# Libs
LIBS    = -ldriver

# The flags passed to the preprocessor
CPPFLAGS    = $(INC_PATHS) \
        -DUSE_FULL_LL_DRIVER=1 \
        -DSTM32L053xx

SRCS    = $(foreach DIR,$(SRC_PATHS),$(wildcard $(DIR)/*.c))
OBJS    = $(SRCS:%.c=%.o)

LIB = $(OUT_PATH)/libdriver.a

# The main Release target
Release: CFLAGS += -O2
Release: CPPFLAGS += -DNDEBUG
Release: $(LIB)
.PHONY: Release

# The main Debug target
Debug: CFLAGS += -Og -g
Debug: CPPFLAGS += -DUSE_FULL_ASSERT=1 \
        -DDEBUG
Debug: $(LIB)
.PHONY: Debug

# Clean target
clean:
	$(RM) $(LIB) $(OBJS)
.PHONY: clean

# The library depends
$(LIB): $(OBJS) $(OUT_PATH) Makefile
	$(AR) -crs $(@) $(filter %.o, $(^))

# Objects depend
$(OBJS): Makefile

# Output directory
$(OUT_PATH): Makefile
	$(MKDIR) $(@)
