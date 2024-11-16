TARGET = main

CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CFLAGS = -mcpu=cortex-m33 -mthumb -g -O0 -Wall
LDFLAGS = -T linker.ld -Wl,--gc-sections -nostartfiles

STFLASH = st-flash

# Source files
SRCS = startup.s main.c gpiof.c delay.c system_clock.c

# Object files
OBJS = $(SRCS:.c=.o)

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
	rm -f *.o $(TARGET).elf $(TARGET).bin