#include "gpiof.h"

// Base addresses for GPIO and RCC
#define RCC_BASE_ADDR       0x40021000
#define GPIOF_BASE_ADDR     0x42021400

// Register offsets
#define RCC_AHB2ENR_OFFSET  0x4C
#define GPIO_MODER_OFFSET   0x00
#define GPIO_ODR_OFFSET     0x14

// Register addresses
#define RCC_AHB2ENR   (*(volatile unsigned int*)(RCC_BASE_ADDR + RCC_AHB2ENR_OFFSET))
#define GPIOF_MODER   (*(volatile unsigned int*)(GPIOF_BASE_ADDR + GPIO_MODER_OFFSET))
#define GPIOF_ODR     (*(volatile unsigned int*)(GPIOF_BASE_ADDR + GPIO_ODR_OFFSET))

// Macros to calculate mode register mask and position
#define GPIO_MODER_MODE_Pos(pin) ((pin) * 2) // Each pin has 2 bits in use
#define GPIO_MODER_MODE_Msk(pin) (0x3 << GPIO_MODER_MODE_Pos(pin))

// Local variables
static const uint8_t MAX_PIN_LENGTH = 15;

// Local functions
static bool valid_pin(const uint8_t pin);

void gpiof_enable_clock()
{
    RCC_AHB2ENR |= (1 << 5);  // Enable clock for GPIOF
}

bool gpiof_configure_pin_output(const uint8_t pin)
{
    if (!valid_pin(pin))
    {
        return false; // Invalid pin number
    }

    // Clear mode bits for the specified pin
    GPIOF_MODER &= ~GPIO_MODER_MODE_Msk(pin);
    // Set mode to output (01) for the specified pin
    GPIOF_MODER |= (0x1 << GPIO_MODER_MODE_Pos(pin));

    return true;
}

bool gpiof_set_pin_high(const uint8_t pin)
{
    if (!valid_pin(pin))
    {
        return false; // Invalid pin number
    }

    GPIOF_ODR |= (1 << pin); // Set the specified pin high

    return true;
}

bool gpiof_set_pin_low(const uint8_t pin)
{
    if (!valid_pin(pin)) {
        return false; // Invalid pin number
    }

    GPIOF_ODR &= ~(1 << pin); // Set the specified pin low

    return true;
}

bool valid_pin(const uint8_t pin)
{
    return pin <= MAX_PIN_LENGTH;
}