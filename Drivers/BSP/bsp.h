/*
 * bsp.h
 *
 * Public interface for board support functions.
 */
#ifndef BSP_H_
#define BSP_H_

#include "gpio.h"

#define LED_PIN          PA5
#define PUSH_BUTTON_PIN  PA6

void bsp_init(void);

#endif
