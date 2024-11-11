#include "delay.h"
#include "gpiof.h"

int main(void) {

    // Set to 16 MHz
    delay_set_clock_frequency(16000000);

    // Enable the GPIOF clock
    gpiof_enable_clock();

    static const uint8_t pin_f = 11;

    // Configure PF11 as output
    if (!gpiof_configure_pin_output(pin_f))
    {
        // TODO: Handle error
        while (1);
    }

    while (1)
    {
        // Set PF11 high
        if (!gpiof_set_pin_high(pin_f))
        {
            // TODO: Handle error
            while (1);
        }

        delay_ms(500);

        // Set PF11 low
        if (!gpiof_set_pin_low(pin_f))
        {
            // TODO: Handle error
            while (1);
        }
    }
}