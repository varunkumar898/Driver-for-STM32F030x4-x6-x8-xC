TARGET = main
BUILD = build

CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

CPU = -mcpu=cortex-m0 -mthumb
CFLAGS = $(CPU) -std=c11 -Wall -Wextra -Werror \
         -ffreestanding -fno-builtin -fdata-sections -ffunction-sections \
         -Iinc -Os
LDFLAGS = $(CPU) -nostartfiles -Wl,--gc-sections -Wl,-Map=$(BUILD)/$(TARGET).map \
          -Tlinker.ld

C_SRCS := $(wildcard src/*.c)
C_OBJS := $(patsubst src/%.c,$(BUILD)/%.o,$(C_SRCS))
ASM_OBJ := $(BUILD)/startup.o

.PHONY: all clean flash size

all: $(BUILD)/$(TARGET).elf $(BUILD)/$(TARGET).bin size

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/%.o: src/%.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/startup.o: startup.s | $(BUILD)
	$(CC) $(CPU) -c $< -o $@

$(BUILD)/$(TARGET).elf: $(C_OBJS) $(ASM_OBJ) linker.ld
	$(CC) $(LDFLAGS) $(C_OBJS) $(ASM_OBJ) -o $@

$(BUILD)/$(TARGET).bin: $(BUILD)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

size: $(BUILD)/$(TARGET).elf
	$(SIZE) $<

flash: $(BUILD)/$(TARGET).elf
	openocd -f interface/stlink.cfg -f target/stm32f0x.cfg \
		-c "program $(BUILD)/$(TARGET).elf verify reset exit"

clean:
	rm -rf $(BUILD)
