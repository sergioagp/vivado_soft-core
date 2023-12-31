# Created by: Sergio Pereira
# Date: 2021/04/18
# Description: Makefile for example soft-core test project

# Cross compiler
CROSS_COMPILE ?= /home/spereira/Projects/tools/arm-gnu-toolchain-12.2.rel1-x86_64-arm-none-eabi/bin/arm-none-eabi-

# Compiler and tools
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OCPY = $(CROSS_COMPILE)objcopy
ODUMP = $(CROSS_COMPILE)objdump
GDB = $(CROSS_COMPILE)gdb
MKDIR = mkdir
QEMU = qemu-system-arm

# Project name and directories
TARGET ?= aes-test
BUILD_DIR ?= build
OBJ_DIR = $(BUILD_DIR)/objs
REPO_ROOT := $(shell pwd)

# Source files and includes
# Source files
SRCS = app/main.c board/system/startup.s board/system/syscalls.c board/system/sysmem.c board/system/system.c board/uart/uart.c lib/aes/aes.c

# Include directories
INCLUDES = lib/aes
LD_FILE = board/linker/m1.ld

# Flags and options
CFLAGS = -mthumb -march=armv6-m -mcpu=cortex-m1 -Wall -std=c11 -specs=nano.specs -O0 -fdebug-prefix-map=$(REPO_ROOT)= -g -ffreestanding -ffunction-sections -fdata-sections $(foreach i,$(INCLUDES),-I$(i))
LDFLAGS = -mthumb -march=armv6-m -mcpu=cortex-m1 -Wl,--print-memory-usage -Wl,-Map=$(BUILD_DIR)/$(TARGET).map -T $(LD_FILE) -Wl,--gc-sections
QEMU_FLAGS = -cpu cortex-m3 -machine lm3s6965evb -nographic -semihosting-config enable=on,target=native -gdb "tcp::50000" -S

# Object files
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))
# Make targets
.PHONY: all
all:
	@echo "Building project..."
	@$(MAKE) --no-print-directory $(BUILD_DIR)/$(TARGET).bin $(BUILD_DIR)/$(TARGET).lst

$(BUILD_DIR):
	@echo "Creating build directory..."
	@$(MKDIR) -p $(BUILD_DIR)

$(OBJ_DIR):
	@echo "Creating object directory..."
	@$(MKDIR) -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c $(OBJ_DIR)
	@echo "Compiling $<..."
	@$(MKDIR) -p $(dir $@)
	@$(CC) -c -o $@ $< $(CFLAGS)

$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	@echo "Creating binary file..."
	@$(OCPY) $< $@ -O binary

$(BUILD_DIR)/$(TARGET).lst: $(BUILD_DIR)/$(TARGET).elf
	@echo "Creating listing file..."
	@$(ODUMP)  -d -M reg-names-raw -S -s $< > $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	@echo "Linking object files..."
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

.PHONY: clean
clean:
	@echo "Deleting build directory..."
	@rm -rf $(BUILD_DIR)

.PHONY: qemu
qemu: $(BUILD_DIR)/$(TARGET).elf
	$(QEMU) $(QEMU_FLAGS) -kernel $<
