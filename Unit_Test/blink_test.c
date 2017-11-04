/*
 * blink_test.c
 *
 *  Created on: Sep 15, 2017
 *      Author: luke
 *      General file with a few unit tests related to timerA, buttons and leds
 */
#include "msp.h"
#include "Headers/blink_test.h"
#include "../Drivers/Headers/timerA.h"
#include "../Drivers/Headers/blink.h"
#include "../Drivers/Headers/button.h"
#include <stdint.h>

uint16_t callbackCounter = 0;




void Blink_Tester()
{
//  testTimerA();
//  testBlink();
//  testFastBlink();
//    singleBlink();
//    multipleTimers();
//  testBlinkLEDs();
//    setColorLED2(PINK);
    test_booster_buttons();
}

uint8_t multipleTimersCallback()
{
    callbackCounter++;
    toggleLED1();
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
    blinkPushLED1(MSP_S2);
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

void blinkRateLED1(TIMER_A_TIME time)
{
    configLED(LED1);
    P1OUT |= BIT0;              // led on
    blinkRateTimerA = setTimerA(time, &toggleRateLED1);
    startTimerA( (TIMER_A) blinkRateTimerA);
}

void blinkPushLED1(BUTTON but)
{
    configLED(LED1);
    P1OUT |= BIT0;              // led on
    configButton(but, &toggleLED1);
}

void multipleTimers()
{
    configLED(LED1);

    TIMER_A timer = setTimerA(ONE_S, &multipleTimersCallback);
    startTimerA(timer);
    while(timer != 0b1);
    while(callbackCounter != 1);

    timer = setTimerA(ONE_S, &multipleTimersCallback);
    startTimerA(timer);
    while(timer != 0b10);
    while(callbackCounter != 2);

    timer = setTimerA(ONE_S, &multipleTimersCallback);
    startTimerA(timer);
    while(timer != 0b100);
    while(callbackCounter != 3);

    timer = setTimerA(ONE_S, &multipleTimersCallback);
    startTimerA(timer);
    while(timer != 0b1000);
    while(callbackCounter != 4);
}

void testBlinkLEDs()
{
    configLED(LED1_LED2);
    TIMER_A timer = setTimerA(HALF_S, &toggleColorsLED2);
    startTimerA(timer);
}

void test_booster_buttons()
{
    configLED(LED1);
    configButton(BOOSTER_S1, &toggleLED1);
}
