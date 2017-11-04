/*
 * button.h
 *
 *  Created on: Sep 15, 2017
 *      Author: luke
 */

#ifndef DRIVERS_HEADERS_BUTTON_H_
#define DRIVERS_HEADERS_BUTTON_H_

static uint8_t buttons_in_use = 0;     // determine if a timerA is already in use

/* global function ptr's for intrpts */
static void (*button_s1_handler)(void);
static void (*button_s2_handler)(void);
static void (*booster_s1_handler)(void);
static void (*booster_s2_handler)(void);
static void (*joystick_s1_handler)(void);

static void (*debouncer)(void);

static uint8_t buttonTimerInUse = 0;

typedef enum BUTTON_t{
    MSP_S1     =   0b00001,
    MSP_S2     =   0b00010,
    BOOSTER_S1  =   0b00100,
    BOOSTER_S2  =   0b01000,
    JOYSTICK_S1 =   0b10000,
}BUTTON;

typedef enum BUTTON_CONFIG_t{
    BUTTON_CONFIG_NO_ERROR,
    BUTTON_CONFIG_ERR_IN_USE,
    BUTTON_CONFIG_ERR_BAD_INPUT
}BUTTON_CONFIG;

/* Configures button to trigger an interrupt and call inputed function */
BUTTON_CONFIG configButton(BUTTON but, void(*handler)(void));

/* Debounce using timerA */
uint8_t _debounceHandler(void);

/* Port ISR's */
void Port1Handler(void);
void Port3Handler(void);
void Port4Handler(void);
void Port5Handler(void);

#endif /* DRIVERS_HEADERS_BUTTON_H_ */
