#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Enables the clock for GPIO port F.
 *
 * This function sets the appropriate bit in the RCC AHB2 peripheral clock enable register
 * to enable the clock for GPIO port F.
 */
void gpiof_enable_clock(void);

/**
 * @brief Configures a specified pin on GPIO port F as an output.
 *
 * This function clears the mode bits for the specified pin and sets it to output mode.
 *
 * @param pin The pin number to configure as output (0-15).
 * @return True on success, False otherwise.
 */
bool gpiof_configure_pin_as_output(uint8_t pin);

/**
 * @brief Sets a specified pin on GPIO port F to high.
 *
 * This function sets the output data register bit corresponding to the specified pin,
 * driving the pin to a high level.
 *
 * @param pin The pin number to set high (0-15).
 * @return True on success, False otherwise.
 */
bool gpiof_set_pin_high(uint8_t pin);

/**
 * @brief Sets a specified pin on GPIO port F to low.
 *
 * This function clears the output data register bit corresponding to the specified pin,
 * driving the pin to a low level.
 *
 * @param pin The pin number to set low (0-15).
 * @return True on success, False otherwise.
 */
bool gpiof_set_pin_low(uint8_t pin);

#endif // GPIO_H