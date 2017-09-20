/*
 * blink_test.c
 *
 *  Created on: Sep 15, 2017
 *      Author: luke
 *      General file with a few unit tests related to timerA, buttons and leds
 */
#include "../Drivers/Headers/timerA.h"
#include "../Drivers/Headers/blink.h"
#include "../Drivers/Headers/button.h"
#include <stdint.h>

uint16_t callbackCounter = 0;

uint8_t fastBlinkCallback()
{
    if((++callbackCounter % 100) == 0)
    {
        callbackCounter = 0;
        toggleLED1();
    }
    return 1;
}

void testFastBlink()
{
    configLED(LED1);
//    TIMER_A timerA = setTimerA(ONE_MS, &fastBlinkCallback);
    TIMER_A timerA = setTimerA(TEN_MS, &fastBlinkCallback);
    startTimerA(timerA);
}

void testBlink()
{
    blinkPushLED1(BUTTON_S2);
}

void testTimerA()
{
    blinkRateLED1(HALF_S);
}
