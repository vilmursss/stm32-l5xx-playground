#include "delay.h"

// Local variables
static uint32_t clock_frequency_hz = 0;

void delay_set_clock_frequency(const uint32_t frequency_hz)
{
    clock_frequency_hz = frequency_hz;
}

void delay_ms(const uint32_t ms)
{
    // Calculate the number of cycles needed for the specified delay in milliseconds
    uint32_t cycles = (clock_frequency_hz / 1000) * ms / 50;

    while (cycles--)
    {
        __asm__ volatile ("nop");
    }
}