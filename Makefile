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

info:
	@echo "Available targets:"
	@echo ""
	@echo "build:"
	@echo "  This target builds the project."
	@echo "  It compiles all source files and links them into an executable."
	@echo ""
	@echo "flash:"
	@echo "  This target is for flashing the ELF file to the device."
	@echo ""
	@echo "clean:"
	@echo "  This target removes all object files, the ELF file, and the binary file."
	@echo ""
	@echo "all:"
	@echo "  This target calls all other targets in the following order: clean, build, flash."

all: clean build flash

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