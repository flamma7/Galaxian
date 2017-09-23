/*
 * blink_test.h
 *
 *  Created on: Sep 15, 2017
 *      Author: luke
 */

#ifndef UNIT_TEST_HEADERS_BLINK_TEST_H_
#define UNIT_TEST_HEADERS_BLINK_TEST_H_

#include <stdint.h>
#include "../../Drivers/Headers/button.h"
#include "../../Drivers/Headers/timerA.h"

void Blink_Tester();

void testBlink();
void testTimerA();
uint8_t fastBlinkCallback();
void testFastBlink();
void singleBlink();
uint8_t singleBlinkCallback();
uint8_t multipleTimersCallback();
void multipleTimers();

void testBlinkLEDs();

/* Toggles LED 1 or 2 at specified rate using timer intrpt*/
void blinkRateLED1(TIMER_A_TIME time);

/* Toggles LED 1 with button depression of inputed button */
void blinkPushLED1(BUTTON but);

#endif /* UNIT_TEST_HEADERS_BLINK_TEST_H_ */
