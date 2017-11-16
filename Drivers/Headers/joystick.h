/*
 * joystick.h
 *
 *  Created on: Nov 4, 2017
 *      Author: luke
 *      Joystick driver for the boostxl-edumkii boosterpack
 *      For use:
 *      1) call init_joystick()
 *      -Makes a circular buffer to store data
 *      2) call get_joystick(&x) and receive x data through an x pointer
 *      Pulls data from the circular buffer
 */

#ifndef DRIVERS_HEADERS_JOYSTICK_H_
#define DRIVERS_HEADERS_JOYSTICK_H_
#include <stdint.h>
#include "fifo.h"

#define JOYSTICK_DATA_TYPE        uint8_t
#define JOYSTICK_BUFFER_SIZE      20
#define JOYSTICK_LEFT_THRESH      6000
#define JOYSTICK_RIGHT_THRESH     10000

static fifo_buffer* x_buffer;     // we'll only need horizontal movement
static uint8_t joystick_timer;

typedef enum JOYSTICK_ERR_t
{
    JOYSTICK_NO_ERR,
    JOYSTICK_NO_DATA
}JOYSTICK_ERR;

typedef enum JOYSTICK_DIR_t
{
  DIR_LEFT,
  DIR_RIGHT,
  DIR_NO_MOVEMENT
}JOYSTICK_DIR;

/* Initializes the joystick module */
void init_joystick();

/* Reads the buffer and returns the oldest movement of the buffer */
JOYSTICK_ERR get_joy_dir(JOYSTICK_DIR* dir);

/* Reads the buffer and returns the oldest value in the buffer */
JOYSTICK_ERR get_joystick(JOYSTICK_DATA_TYPE* x);

/* Ends adc conversions on the joystick */
void stop_joystick();
/* Called after stop_joystick() reenables adc conversions */
void restart_joystick();

/* Reads the adc and stores the value in the circular buffer 
 *    Not a user function */
void _store_adc_buffer();

//void ADC14_Handler(void);

#endif /* DRIVERS_HEADERS_JOYSTICK_H_ */
