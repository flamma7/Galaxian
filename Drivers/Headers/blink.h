/*
 * blink.h
 *
 *  Created on: Sep 15, 2017
 *      Author: luke
 */

#ifndef DRIVERS_HEADERS_BLINK_H_
#define DRIVERS_HEADERS_BLINK_H_

#include "button.h"
#include <stdint.h>

typedef enum LED_t{
    LED1,
    LED2,
    LED1_LED2
}LED;

typedef enum COLOR_t{
    RED,
    GREEN,
    BLUE
}COLOR;

/* Sets the color of LED2 (0-7) */
void setColorLED2(COLOR col);

/* Toggles LED 1 or 2 at specified rate using timer intrpt*/
void blinkRate(LED led, COLOR col, uint8_t milli_period);

/* Toggles LED 1 with button depression of inputted button
 * LED1 is always COLOR = RED */
void blinkPushLED1(BUTTON but);

/* Cycles through 7 colors of led */
void blinkCycle(BUTTON but);

/* Configures led pin(s) as output(s) set to low */
void _configLED(LED led);

/* Toggles the LED */
void toggleLED1();

#endif /* DRIVERS_HEADERS_BLINK_H_ */
