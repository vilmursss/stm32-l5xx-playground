#include "system_clock.h"

#define RCC_BASE            0x40021000
#define FLASH_BASE          0x40022000
#define PWR_BASE            0x40007000

#define RCC_CR              (*(volatile unsigned int *)(RCC_BASE + 0x00))
#define RCC_CFGR            (*(volatile unsigned int *)(RCC_BASE + 0x08))
#define RCC_PLLCFGR         (*(volatile unsigned int *)(RCC_BASE + 0x0C))

#define FLASH_ACR           (*(volatile unsigned int *)(FLASH_BASE + 0x00))

#define PWR_CR1             (*(volatile unsigned int *)(PWR_BASE + 0x00))
#define PWR_SR2             (*(volatile unsigned int *)(PWR_BASE + 0x18))

#define RCC_CR_HSION        (1 << 8)
#define RCC_CR_HSIRDY       (1 << 10)
#define RCC_CR_PLLON        (1 << 24)
#define RCC_CR_PLLRDY       (1 << 25)

#define RCC_CFGR_HSI6_SYSTEM_CLOCK (1 << 2)
#define RCC_CFGR_SW_PLL     (0x3 << 0)
#define RCC_CFGR_SWS_PLL    (0x3 << 2)

// Local variables
static const int TIMEOUT = 1000000;

// Local functions
static void system_clock_clear_pll();
static void system_clock_configure_pll();
static void system_clock_clear_cfgr();
static void system_clock_configure_cfgr();
static void system_clock_configure_flash_latency();

void system_clock_init()
{
    // Configure voltage scaling to Range 0 (high performance)
    PWR_CR1 &= ~(0x3 << 9); // Clear VOS bits
    PWR_CR1 |= (0x0 << 9);

    // Wait until voltage scaling is ready
    int timeout = TIMEOUT;
    while ((PWR_SR2 & (0x1 << 10)) && timeout--)
    {
        // TODO: Error message
        if (timeout == 0)
        {
            while (1);
        } 
    }
    
    //  Enable HSI oscillator
    RCC_CR |= RCC_CR_HSION;
    timeout = TIMEOUT;
    while (!(RCC_CR & RCC_CR_HSIRDY) && timeout--)
    {
        // TODO: Error message
        if (timeout == 0)
        {
            while (2);
        }
    }

    // Set HSI16 as the system clock source just in case
    timeout = TIMEOUT;
    RCC_CFGR |= (0x1 << 0);
    while (!(RCC_CFGR & RCC_CFGR_HSI6_SYSTEM_CLOCK) && timeout--) // Wait until HSI16 is used as system clock
    {
        // TODO: Error message
        if (timeout == 0)
        {
            while (3);
        } 
    }

    // Disable the PLL before clearing the PLLCFGR register
    timeout = TIMEOUT;
    RCC_CR &= ~RCC_CR_PLLON;
    while ((RCC_CR & RCC_CR_PLLRDY) && timeout--)
    {
        // TODO: Error message
        if (timeout == 0)
        {
            while (4);
        }
    }

    // Configure PLL latency
    system_clock_clear_pll();
    system_clock_configure_pll();

    // Re-enable the PLL
    timeout = TIMEOUT;
    RCC_CR |= RCC_CR_PLLON;
    while (!(RCC_CR & RCC_CR_PLLRDY) && timeout--)
    {
        // TODO: Error message
        if (timeout == 0)
        {
            while (5);
        }
    }

    // Configure CFGR latency
    system_clock_clear_cfgr();
    system_clock_configure_cfgr();

    // Configure flash latency
    system_clock_configure_flash_latency();

    // Switch system clock to PLL
    timeout = TIMEOUT;
    RCC_CFGR |= RCC_CFGR_SW_PLL;
    while (!(RCC_CFGR & RCC_CFGR_SWS_PLL) && --timeout)
    {
        // TODO: Error message
        if (timeout == 0)
        {
            while (6);
        }
    }
}

static void system_clock_clear_pll()
{
    // Clear the PLLSRC bits
    RCC_PLLCFGR &= ~(0x3 << 0);

    // Clear the PLLM bits
    RCC_PLLCFGR &= ~(0xF << 4);

    // Clear the PLLN bits
    RCC_PLLCFGR &= ~(0x7F << 8);

    // Clear the PLLP bit
    RCC_PLLCFGR &= ~(1 << 17);
}

static void system_clock_configure_pll()
{
    // Configure the PLL source to HSI16
    RCC_PLLCFGR |= (0x2 << 0);

    // Configure the PLLM 
    RCC_PLLCFGR |= (0x3 << 4);

    // Configure the PLLN
    RCC_PLLCFGR |= (50 << 8);

    // Configure the PLLP
    RCC_PLLCFGR |= (0 << 17);
}

static void system_clock_clear_cfgr()
{
    // Clear SW bits
    RCC_CFGR &= ~(0x3 << 0);

    // Clear HPRE bits
    RCC_CFGR &= ~(0xF << 4);

    // Clear PPRE1 bits 
    RCC_CFGR &= ~(0x7 << 8);

    // Clear PPRE2
    RCC_CFGR &= ~(0x7 << 11);
}

static void system_clock_configure_cfgr()
{
    // Configure the AHB prescaler (HPRE)
    RCC_CFGR |= (0x0 << 4);
 
    // Configure the APB1 prescaler (PPRE1) to divide by 2
    RCC_CFGR |= (0x4 << 8);
 
    // Configure the APB2 prescaler (PPRE2) to divide by 4
    RCC_CFGR |= (0x5 << 11);
}

static void system_clock_configure_flash_latency()
{
    // Set flash latency to 4 wait states
    FLASH_ACR &= ~(0xF << 0); // Clear latency bits
    FLASH_ACR |= (0x4 << 0);
}