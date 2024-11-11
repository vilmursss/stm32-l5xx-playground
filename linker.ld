MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K
    SRAM1 (rwx) : ORIGIN = 0x20000000, LENGTH = 192K
}

_estack = ORIGIN(SRAM1) + LENGTH(SRAM1);

SECTIONS
{
    .isr_vector :
    {
        KEEP(*(.isr_vector)) /* Vector table */
    } > FLASH

    .text :
    {
        *(.text*)
        *(.rodata*)
        _etext = .;
    } > FLASH

    .data : AT(_etext)
    {
        __data_start__ = .;
        *(.data*)
        __data_end__ = .;
    } > SRAM1

    .bss :
    {
        __bss_start__ = .;
        *(.bss*)
        __bss_end__ = .;
    } > SRAM1

    . = ALIGN(4);
    _end = .;
}