/*
 * rcc.c
 * Get APB1 clock frequency (USART2 clock)
 */
#include "rcc.h"

#include "stm32f030x8.h"


uint32_t rcc_get_pclk1_freq(void)
{
    uint32_t sysclk;
    uint32_t clk_src = (RCC->CFGR >> 2) & 0x3;
    uint32_t hpre    = (RCC->CFGR >> 4) & 0xF;
    uint32_t ppre    = (RCC->CFGR >> 8) & 0x7;
    /* Determine system clock source */
    switch (clk_src)
    {
        case 0x0:  // HSI
            sysclk = 8000000U;
            break;

        case 0x1:  // HSE
            sysclk = 8000000U;   // adjust if crystal differs
            break;

        case 0x2:  // PLL
            sysclk = 48000000U;
            break;

        default:   // reserved / unexpected
            sysclk = 8000000U;   // safe fallback
            break;
    }
    /* Apply AHB prescaler */
    if (hpre >= 8) {			// HPRE: 0xxx=/1, 1000=/2, 1001=/4, 1010=/8 ...
        sysclk >>= (hpre - 7);	// divide SYSCLK by AHB prescaler (2^(hpre-7))
    }
    /* Apply APB1 prescaler */
    if (ppre >= 4) {
        sysclk >>= (ppre - 3); // divide SYSCLK by APB1 prescaler (2^(ppre-3))
    }
    return sysclk;
}
/*Instead of this
 * sysclk = sysclk / 2^1;
 * sysclk = sysclk / 2^2;
 * I used this
 * sysclk >>= 1;
 * sysclk >>= 2;
 * */
