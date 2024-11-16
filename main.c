#include "utils/delay.h"
#include "gpio/gpio_f.h"
#include "clock/system_clock.h"

int main(void)
{

    system_clock_init();

    // Set to 16 MHz
    delay_set_clock_frequency(16000000);

    // Enable the GPIOF clock
    gpiof_enable_clock();

    static const uint8_t pin_f = 11;

    // Configure PF11 as output
    if (!gpiof_configure_pin_output(pin_f))
    {
        // TODO: Handle error
        while (2);
    }

    while (1)
    {
        // Set PF11 high
        if (!gpiof_set_pin_high(pin_f))
        {
            // TODO: Handle error
            while (3);
        }

        delay_ms(500);

        // Set PF11 low
        if (!gpiof_set_pin_low(pin_f))
        {
            // TODO: Handle error
            while (4);
        }

        delay_ms(500);
    }
}