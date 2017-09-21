/*
 * blink.h
 *
 *  Created on: Sep 15, 2017
 *      Author: luke
 *
 */

#ifndef DRIVERS_HEADERS_BLINK_H_
#define DRIVERS_HEADERS_BLINK_H_

#include "button.h"
#include "timerA.h"
#include <stdint.h>

typedef enum LED_t{
    LED1,
    LED2,
    LED1_LED2
}LED;

typedef enum COLOR_t{
    OFF,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    PINK,
    LIGHT_BLUE,
    WHITE
}COLOR;


static uint8_t blinkRateTimerA = 0;

/* Sets the color of LED2 (0-7) (LED1 only has color RED) */
void setColorLED2(COLOR col);

/* Configures led pin(s) as output(s) set to low */
void configLED(LED led);

/* Toggles LED P1.0 and restarts timerA intrpt */
uint8_t toggleRateLED1();

/* Toggles LED P1.0 */
void toggleLED1();

/* Cycles through LED2's 8 color states */
uint8_t toggleColorsLED2();

#endif /* DRIVERS_HEADERS_BLINK_H_ */
