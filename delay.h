#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>

/**
 * @brief Sets the clock frequency for delay calculations.
 * 
 * @param frequency_hz The clock frequency in Hz.
 */
void delay_set_clock_frequency(uint32_t frequency_hz);

/**
 * @brief Delays execution for a specified number of milliseconds.
 * 
 * @param ms The number of milliseconds to delay.
 */
void delay_ms(uint32_t ms);

#endif // DELAY_H