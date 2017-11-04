/*
 * joystick.h
 *
 *  Created on: Nov 4, 2017
 *      Author: luke
 */

#ifndef DRIVERS_HEADERS_JOYSTICK_H_
#define DRIVERS_HEADERS_JOYSTICK_H_
#include <stdint.h>

typedef enum JOYSTICK_ERR_t
{
    JOYSTICK_NO_ERR,
    JOYSTICK_NO_INIT,
    JOYSTICK_NO_DATA,
}JOYSTICK_ERR;

void init_joystick();

JOYSTICK_ERR get_joystick(uint16_t x, uint16_t y);

void ADC14_Handler(void);

#endif /* DRIVERS_HEADERS_JOYSTICK_H_ */
