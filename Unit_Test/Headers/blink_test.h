/*
 * blink_test.h
 *
 *  Created on: Sep 15, 2017
 *      Author: luke
 */

#ifndef UNIT_TEST_HEADERS_BLINK_TEST_H_
#define UNIT_TEST_HEADERS_BLINK_TEST_H_

#include <stdint.h>

void Unit_Tester();

void testBlink();
void testTimerA();
uint8_t fastBlinkCallback();
void testFastBlink();
void singleBlink();
uint8_t singleBlinkCallback();
uint8_t multipleTimersCallback();
void multipleTimers();

#endif /* UNIT_TEST_HEADERS_BLINK_TEST_H_ */
