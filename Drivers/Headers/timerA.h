/*
 * timerA.h
 *
 *  Created on: Sep 15, 2017
 *      Author: luke
 *  INSTRUCTIONS:
 *      1) Call setTimerA() with parameters to configure and receive a timerA number (0-3)
 *      2) Call startTimerA() passing the timerA number to start timing
 */

#ifndef DRIVERS_HEADERS_TIMERA_H_
#define DRIVERS_HEADERS_TIMERA_H_

#include <stdint.h>

/* global function ptr's for intrpts */
void (*_timerA0_handler)(void);
void (*_timerA1_handler)(void);
void (*_timerA2_handler)(void);

/* global timerA counts */
uint16_t _timerA0_counter;
uint16_t _timerA1_counter;
uint16_t _timerA2_counter;

uint8_t _timerAs_in_use;

typedef enum TIMER_A_t{
    TIMERA_0 = 0b1,
    TIMERA_1 = 0b10,
    TIMERA_2 = 0b100,
    TIMERA_3 = 0b1000,
    TIMERA_ERROR = 0
}TIMER_A;

typedef enum TIMER_A_START_t{
    TIMER_A_START_NO_ERROR,
    TIMER_A_START_ERR_NOT_CONFIGURED
}TIMER_A_START;

typedef enum TIMER_A_TIME_t{
    ONE_MS,
    TEN_MS,
    HALF_S,
    ONE_S,
}TIMER_A_TIME;


/* Returns an open timerA */
TIMER_A setTimerA(TIMER_A_TIME time, void(*handler)(void));
/* Start selected timerA */
TIMER_A_START startTimerA(TIMER_A timerA);

#endif /* DRIVERS_HEADERS_TIMERA_H_ */
