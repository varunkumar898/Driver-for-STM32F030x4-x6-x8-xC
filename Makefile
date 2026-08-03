TARGET = firmware

CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

CFLAGS = -mcpu=cortex-m0 -mthumb -Wall -O0 -g -ffreestanding -Iinc
LDFLAGS = -Tlinker.ld -nostdlib -Wl,-Map=$(TARGET).map -Wl,--undefined=SystemInit

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o) startup.o

all: $(TARGET).elf $(TARGET).bin

$(TARGET).elf: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@
	$(SIZE) $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

startup.o: startup.s
	$(CC) $(CFLAGS) -c startup.s -o startup.o

clean:
	rm -f src/*.o *.o firmware.elf firmware.bin firmware.map

flash: firmware.bin
	st-flash write firmware.bin 0x08000000

.PHONY: all clean flash
