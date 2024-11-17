#ifndef GPIO_GPIO_C_H
#define GPIO_GPIO_C_H

/**
 * @brief Enables the clock for GPIOC and configures PC10 for USART3_TX.
 *
 * This function enables the clock for the GPIOC peripheral and configures
 * pin PC10 to operate in alternate function mode for USART3 transmission (TX).
 * It sets the appropriate alternate function type (AF7) for PC10 to ensure
 * proper communication with the USART3 peripheral.
 */ 
void gpioc_enable_clock();

#endif // GPIO_GPIO_C_H