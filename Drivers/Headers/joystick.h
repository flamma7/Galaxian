/*
 * joystick.h
 *
 *  Created on: Nov 4, 2017
 *      Author: luke
 *      Joystick driver for the boostxl-edumkii boosterpack
 *      For use:
 *      1) call init_joystick()
 *      2) call get_joystick(&x,&y) and receive data through x,y pointers
 */

#ifndef DRIVERS_HEADERS_JOYSTICK_H_
#define DRIVERS_HEADERS_JOYSTICK_H_
#include <stdint.h>

#define JOYSTICK_DATA_TYPE  uint8_t

typedef enum JOYSTICK_ERR_t
{
    JOYSTICK_NO_ERR,
    JOYSTICK_NO_INIT,
    JOYSTICK_NO_DATA,
}JOYSTICK_ERR;

/* Initializes the joystick module */
void init_joystick();

JOYSTICK_ERR get_joystick(JOYSTICK_DATA_TYPE* x, JOYSTICK_DATA_TYPE* y);

void stop_joystick();

void ADC14_Handler(void);

#endif /* DRIVERS_HEADERS_JOYSTICK_H_ */
