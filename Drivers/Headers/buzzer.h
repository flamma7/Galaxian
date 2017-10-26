/*
 * buzzer.h
 *
 *  Created on: Oct 25, 2017
 *      Author: luke
 *      Buzzer interface pin = p2.7
 *      Instructions:
 *      1) Configure a buzzer with a beep or alarm
 *      2) call buzz() to activate the buzzer
 */

#ifndef DRIVERS_HEADERS_BUZZER_H_
#define DRIVERS_HEADERS_BUZZER_H_

#include <stdint.h>

#define BEEP_TIME_COUNT      50
#define ALARM_TIME_COUNT     100

typedef enum BUZZER_SEL_t{
    BUZZER_BEEP,        // short beep on the buzzer
    BUZZER_ALARM         // extended buzz at a lower frequency
}BUZZER_SEL;

static uint8_t buzzer_count = 0;
static uint8_t buzzer_timer = 0;

void config_buzzer(BUZZER_SEL sel);
void buzz();
uint8_t buzzer_callback();

// TODO create interface to make different pitches for different lengths
// --> create simple tunes

#endif /* DRIVERS_HEADERS_BUZZER_H_ */
