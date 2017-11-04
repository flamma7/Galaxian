/*
 * joystick.h
 *
 *  Created on: Nov 4, 2017
 *      Author: luke
 */

#ifndef DRIVERS_HEADERS_JOYSTICK_H_
#define DRIVERS_HEADERS_JOYSTICK_H_


typedef enum JOYSTICK_ERR_t
{
    JOYSTICK_NO_ERR,
    JOYSTICK_NO_INIT,
    JOYSTICK_NO_DATA,
}JOYSTICK_ERR;

void init_joystick();



#endif /* DRIVERS_HEADERS_JOYSTICK_H_ */
