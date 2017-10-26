/*
 * buzzer.h
 *
 *  Created on: Oct 25, 2017
 *      Author: luke
 */

#ifndef DRIVERS_HEADERS_BUZZER_H_
#define DRIVERS_HEADERS_BUZZER_H_

#include <stdint.h>

#define BUZZER_TIME      30

typedef enum BUZZER_LEVEL_t{
    BUZZER_LOW,
    BUZZER_MED,
    BUZZER_HIGH
}BUZZER_LEVEL;

static uint8_t buzzer_count = 0;
static uint8_t buzzer_level = 0;

void start_buzz();

#endif /* DRIVERS_HEADERS_BUZZER_H_ */
