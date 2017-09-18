/*
 * timerA.h
 *
 *  Created on: Sep 15, 2017
 *      Author: luke
 *  INSTRUCTIONS:
 *      1) Call setTimerA() with time and callback to receive an open timerA number (TIMERA_x 0-3)
 *      2) Call startTimerA() passing the TIMERA_x number to start timing
 */

#ifndef DRIVERS_HEADERS_TIMERA_H_
#define DRIVERS_HEADERS_TIMERA_H_

#include <stdint.h>

/* global function ptr's for intrpts */
static void (*_timerA0_handler)(void);
static void (*_timerA1_handler)(void);
static void (*_timerA2_handler)(void);
static void (*_timerA3_handler)(void);

/* global timerA counts */
static uint16_t _timerA0_counter = 0;
static uint16_t _timerA1_counter = 0;
static uint16_t _timerA2_counter = 0;
static uint16_t _timerA3_counter = 0;

static uint8_t _timerAs_in_use = 0;

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


/* Returns an open timerA, given a time and a callback */
TIMER_A setTimerA(const TIMER_A_TIME time, void(*handler)(void));
/* Start selected timerA */
TIMER_A_START startTimerA(const TIMER_A timerA);

/* TimerA interrupt handler */
void TimerA0Handler(void);
void TimerA1Handler(void);
void TimerA2Handler(void);
void TimerA3Handler(void);

/* Non-user functions, configure the selected timer for the time */
static void _configTimerA0(const TIMER_A_TIME time);
static void _configTimerA1(const TIMER_A_TIME time);
static void _configTimerA2(const TIMER_A_TIME time);
static void _configTimerA3(const TIMER_A_TIME time);


#endif /* DRIVERS_HEADERS_TIMERA_H_ */
