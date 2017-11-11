/*
 * joystick.h
 *
 *  Created on: Nov 4, 2017
 *      Author: luke
 *      Joystick driver for the boostxl-edumkii boosterpack
 *      For use:
 *      1) call init_joystick()
 *      Make a circular buffer and store data
 *      2) call get_joystick(&x,&y) and receive data through x,y pointers
 *      Pulls data from the circular buffer
 */

#ifndef DRIVERS_HEADERS_JOYSTICK_H_
#define DRIVERS_HEADERS_JOYSTICK_H_
#include <stdint.h>
#include "fifo.h"

#define JOYSTICK_DATA_TYPE        uint8_t
#define JOYSTICK_BUFFER_SIZE      40

static fifo_buffer* y_buffer;

typedef enum JOYSTICK_ERR_t
{
    JOYSTICK_NO_ERR,
    JOYSTICK_NO_INIT,
    JOYSTICK_NO_DATA,
}JOYSTICK_ERR;

/* Initializes the joystick module */
void init_joystick();

JOYSTICK_ERR get_joystick(JOYSTICK_DATA_TYPE* x, JOYSTICK_DATA_TYPE* y);

/* Ends adc conversions on the joystick */
void stop_joystick();
/* Called after stop_joystick() reenables adc conversions */
void restart_joystick();

void ADC14_Handler(void);

#endif /* DRIVERS_HEADERS_JOYSTICK_H_ */
