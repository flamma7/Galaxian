/*
 * timerA.h
 *
 *  Created on: Sep 15, 2017
 *      Author: luke
 */

#ifndef DRIVERS_HEADERS_TIMERA_H_
#define DRIVERS_HEADERS_TIMERA_H_

#include <stdint.h>

//#define CALC_TIMER_CONFIG_FAST            // calculateTimerConfig() or calculateTimerConfigFast()
#define CALC_TIMER_CONFIG_ONE_S             1

uint8_t timerAs_in_use;     // determine if a timerA is already in use

/* global function ptr's for intrpts */
void (*timerA0_handler)(void);
void (*timerA1_handler)(void);
void (*timerA2_handler)(void);

/* global timerA counts */
uint16_t timerA0_counter;
uint16_t timerA1_counter;
uint16_t timerA2_counter;


typedef enum TIMER_A_t{
    TIMERA_0 = 0b1,
    TIMERA_1 = 0b10,
    TIMERA_2 = 0b100
}TIMER_A;

typedef enum TIMER_A_START_t{
    TIMER_A_START_NO_ERROR,
    TIMER_A_START_ERR_NO_CONFIG,
    TIMER_A_START_ERR_BAD_INPUT
}TIMER_A_START;

typedef enum TIMER_A_CONFIG_t{
    TIMER_A_CONFIG_NO_ERROR,
    TIMER_A_CONFIG_ERR_IN_USE,
    TIMER_A_CONFIG_ERR_NO_INIT,
    TIMER_A_CONFIG_ERR_BAD_INPUT
}TIMER_A_CONFIG;

typedef enum TIMER_A_CALC_t{
    TIMER_A_CALC_EXACT_TIME,
    TIMER_A_CALC_ALMOST_TIME
}TIMER_A_CALC;

typedef enum TIMER_A_CLK_t{
    TIMER_A_CLK_SMCLK = 3000000,
    TIMER_A_CLK_ACLK = 32768,
}TIMER_A_CLK;

/* Initializes timerA module for use. Must be called before all other timerA functions */
void initTimerA(void);

/* Configure a timerA 0-2, inputs: timerA select, time (ms) and callback */
TIMER_A_CONFIG configTimerA(TIMER_A timerA, uint16_t milli_time, void(*handler)(void));

/* Reconfigure a timerA 0-2 inputs: timerA select, new time (ms) and new callback
 * Call to change a timer's callback */
TIMER_A_CONFIG reconfigTimerA(TIMER_A timerA, uint16_t milli_time, void(*handler)(void));

/* Start timerA count */
TIMER_A_START startTimerA(TIMER_A timerA);

/* Returns the clock source, prescalar1, prescalar2 and the count given the time (ms) */
TIMER_A_CALC _calculateTimerConfig(TIMER_A_CLK * clk, uint8_t * prescl_1, uint8_t * prescl_2, uint16_t * count, uint16_t milli_time);

/* Returns the clock source, prescalar1, prescalar2 and the count given the time (ms)
 * Uses hardcoded values */
#ifdef CALC_TIMER_CONFIG_FAST
TIMER_A_CALC _calculateTimerConfigFast(TIMER_A_CLK * clk, uint8_t * prescl_1, uint8_t * prescl_2, uint16_t * count, uint16_t milli_time);
#endif

/* Helper functions for dynamic clock configuration */
void _configTimerA_Clk(TIMER_A timerA, TIMER_A_CLK clk);
void _configTimerA_ID(TIMER_A timerA, uint8_t id);
void _configTimerA_TAIDEX(TIMER_A timerA, uint8_t taidex);


/* TODO add timerA3 capability */

#endif /* DRIVERS_HEADERS_TIMERA_H_ */
