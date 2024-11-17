#include "gpio_c.h"

#include <stdint.h>

// Base addresses
#define RCC_BASE        0x40021000
#define GPIOC_BASE      0x42020800

// RCC registers
#define RCC_AHB2ENR     (*(volatile uint32_t *)(RCC_BASE + 0x4C))

// GPIOC registers
#define GPIOC_MODER     (*(volatile uint32_t *)(GPIOC_BASE + 0x00))
#define GPIOC_AFRH      (*(volatile uint32_t *)(GPIOC_BASE + 0x24))

// Bit definitions
#define RCC_AHB2ENR_GPIOCEN  (1 << 2)

#define GPIO_MODER_MODER10   (3 << (10 * 2))
#define GPIO_MODER_MODER10_1 (2 << (10 * 2))

#define GPIO_AFRH_AF7_PC10   (0x7 << ((10 - 8) * 4))  // PC10 is in AFRH

void gpioc_enable_clock()
{
    // Enable the clock for GPIOC
    RCC_AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

    // Set PC10 to alternate function mode
    GPIOC_MODER &= ~GPIO_MODER_MODER10;
    GPIOC_MODER |= GPIO_MODER_MODER10_1;

    // Set the alternate function type to USART3_TX (AF7)
    GPIOC_AFRH &= ~(0xF << ((10 - 8) * 4));  // Clear the existing bits
    GPIOC_AFRH |= GPIO_AFRH_AF7_PC10;        // Set AF7 for PC10
}