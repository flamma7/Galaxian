/*
 * blink_test.c
 *
 *  Created on: Sep 15, 2017
 *      Author: luke
 *      General file with a few unit tests related to timerA, buttons and leds
 */
#include "Headers/blink_test.h"
#include "../Drivers/Headers/timerA.h"
#include "../Drivers/Headers/blink.h"
#include "../Drivers/Headers/button.h"
#include <stdint.h>

uint16_t callbackCounter = 0;

void Unit_Tester()
{
//  testTimerA();
//  testBlink();
//  testFastBlink();
    singleBlink();
//    multipleTimers();

}

uint8_t multipleTimersCallback()
{
    TIMER_A timer = setTimerA(ONE_MS, &multipleTimersCallback);
    if(timer != TIMERA_ERROR)
    {
        toggleLED1();
        startTimerA(timer);
    }
    return 0;
}

uint8_t fastBlinkCallback()
{
    if((++callbackCounter % 100) == 0)
    {
        callbackCounter = 0;
        toggleLED1();
    }
    return 1;
}

uint8_t singleBlinkCallback()
{
    toggleLED1();
    return ++callbackCounter % 2;
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

void singleBlink()
{
    configLED(LED1);
    TIMER_A timerA = setTimerA(ONE_S, &singleBlinkCallback);
    startTimerA(timerA);
}

void multipleTimers()
{
    TIMER_A timer = setTimerA(ONE_S, &multipleTimersCallback);
    startTimerA(timer);
}
