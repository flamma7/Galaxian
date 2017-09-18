/*
 * blink.h
 *
 *  Created on: Sep 15, 2017
 *      Author: luke
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
    RED,
    GREEN,
    BLUE
}COLOR;


static uint8_t blinkRateTimerA = 0;

/* Sets the color of LED2 (0-7) (LED1 only has color RED) */
//void setColorLED2(COLOR col);

/* Toggles LED 1 or 2 at specified rate using timer intrpt*/
void blinkRateLED1(TIMER_A_TIME time);

/* Toggles LED 1 with button depression of inputed button
 * LED1 is always COLOR = RED */
void blinkPushLED1(BUTTON but);

/* Cycles through 7 colors of led */
//void blinkCycle(BUTTON but);

/* Configures led pin(s) as output(s) set to low */
static void _configLED(LED led);

/* Toggles LED P1.0 and restarts timerA intrpt */
void toggleRateLED1();

/* Toggles LED P1.0 */
void toggleLED1();

#endif /* DRIVERS_HEADERS_BLINK_H_ */
