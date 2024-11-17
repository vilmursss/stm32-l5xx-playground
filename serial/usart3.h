#ifndef SERIAL_USART3_H
#define SERIAL_USART3_H

/**
 * @brief Initializes the USART3 peripheral with a baud rate of 9600.
 *
 * This function enables the clock for the USART3 peripheral and configures
 * it for transmission with a baud rate of 9600. It calculates the baud rate
 * register (BRR) value based on an 8 MHz peripheral clock (PCLK1) and sets
 * the necessary control registers to enable the USART3 transmitter.
 */
void usart3_init();

/**
 * @brief Sends a single character via USART3.
 *
 * This function transmits a single character through the USART3 peripheral.
 * It waits until the transmit data register (TDR) is empty before writing
 * the character to the TDR, ensuring that the character is sent correctly.
 *
 * @param c The character to be sent.
 *
 * @note Ensure that USART3 is properly initialized using usart3_init()
 *       before calling this function.
 */
void usart3_send_char(char c);

#endif // SERIAL_USART3_H