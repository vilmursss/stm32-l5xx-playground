TARGET = main

CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CFLAGS = -mcpu=cortex-m33 -mthumb -g -O0 -Wall
LDFLAGS = -T startup/linker.ld -Wl,--gc-sections -nostartfiles

STFLASH = st-flash

# Find all .c and .s files in the project directories
SRCS = $(shell find . -name '*.c') $(shell find . -name '*.s')

# Object files
OBJS = $(SRCS:.c=.o)
OBJS := $(OBJS:.s=.o)

build: $(TARGET).elf
	$(OBJCOPY) -O binary $(TARGET).elf $(TARGET).bin

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET).elf $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(CC) $(CFLAGS) -c $< -o $@

flash: $(TARGET).bin
	$(STFLASH) erase
	$(STFLASH) write $< 0x08000000

clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).bin