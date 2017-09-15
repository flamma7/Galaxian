/*
 * button.h
 *
 *  Created on: Sep 15, 2017
 *      Author: luke
 */

#ifndef DRIVERS_HEADERS_BUTTON_H_
#define DRIVERS_HEADERS_BUTTON_H_

uint8_t buttons_in_use;     // determine if a timerA is already in use

/* global function ptr's for intrpts */
void (*button_s1_handler)(void);
void (*button_s2_handler)(void);

typedef enum BUTTON_t{
    BUTTON_S1,
    BUTTON_S2
}BUTTON;

typedef enum BUTTON_CONFIG_t{
    BUTTON_CONFIG_NO_ERROR,
    BUTTON_CONFIG_ERR_IN_USE,
    BUTTON_CONFIG_ERR_NO_INIT,
    BUTTON_CONFIG_ERR_BAD_INPUT
}BUTTON_CONFIG;

/* Initializes button module for use. Must be called before all other button functions */
void initButtons(void);

/* Configures button to trigger an interrupt and call inputed function */
BUTTON_CONFIG configButton(BUTTON but, void(*handler)(void));

/* Port 1 ISR */
void Port1Handler(void);

#endif /* DRIVERS_HEADERS_BUTTON_H_ */
