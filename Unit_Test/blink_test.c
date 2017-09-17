/*
 * blink_test.c
 *
 *  Created on: Sep 15, 2017
 *      Author: luke
 */
#include "../Drivers/Headers/timerA.h"
#include "../Drivers/Headers/blink.h"
#include "../Drivers/Headers/button.h"

void testTimerA()
{
    blinkRateLED1(ONE_S);
}

void testBlink()
{
    blinkPushLED1(BUTTON_S1);
}
