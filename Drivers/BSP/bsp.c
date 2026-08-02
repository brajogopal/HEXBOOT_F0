/*
 * bsp.c
 *
 * Board Support Package.
 */

#include "bsp.h"
#include "stm32f030x8.h"

void bsp_init(void)
{
    pinMode(LED_PIN, OUTPUT);
    pinMode(PUSH_BUTTON_PIN, INPUT);
}
