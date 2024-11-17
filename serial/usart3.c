#include "usart3.h"

#include <stdint.h>

// Base addresses
#define RCC_BASE        0x40021000
#define USART3_BASE     0x40004800

// RCC registers
#define RCC_APB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x58))

// USART3 registers
#define USART3_ISR      (*(volatile uint32_t *)(USART3_BASE + 0x1C))
#define USART3_TDR      (*(volatile uint32_t *)(USART3_BASE + 0x28))
#define USART3_BRR      (*(volatile uint32_t *)(USART3_BASE + 0x0C))
#define USART3_CR1      (*(volatile uint32_t *)(USART3_BASE + 0x00))

// Bit definitions
#define RCC_APB1ENR_USART3EN (1 << 18)

void usart3_init()
{
    // Enable the clock for USART3
    RCC_APB1ENR |= RCC_APB1ENR_USART3EN;

    // Calculate baud (9600) for 8MHz clock (PCLK1, see system_clock.c)
    const uint32_t baud = ((8000000 + (9600 / 2U)) / 9600) / 4;
    USART3_BRR = baud;

    // Enable USART3 and configure it for transmission
    USART3_CR1 |= (1 << 29);
    USART3_CR1 |= (1 << 3);  // Enable transmitter (TE bit)
    USART3_CR1 |= (1 << 0); // Enable USART (UE bit)
}

void usart3_send_char(const char c)
{
    // Wait until the transmit data register is empty
    while (!(USART3_ISR & (1 << 7)));

    // Write the character to the data register
    USART3_TDR = c;
}