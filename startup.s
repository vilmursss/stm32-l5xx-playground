.equ NUMBER_OF_INTERRUPTS, 121

.section .isr_vector, "a", %progbits
.global _start
_start:
    .word  _estack           // Initial stack pointer
    .word  Reset_Handler
    .rept NUMBER_OF_INTERRUPTS - 1
        .word  Default_Handler   // Default handler for all other interrupts
    .endr

.section .text
.global Default_Handler
Default_Handler:
    bx lr

.global Reset_Handler
Reset_Handler:
    // Initialize the stack pointer
    ldr r0, =_estack
    mov sp, r0

    // Call the main function
    bl main

    b .
