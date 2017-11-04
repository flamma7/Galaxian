/*
 * fifo.h
 *
 *  Created on: Nov 3, 2017
 *      Author: luke
 *
 *      fifo library that supports only a single fifo on the driver side
 *
 */

#ifndef DRIVERS_HEADERS_FIFO_H_
#define DRIVERS_HEADERS_FIFO_H_

#include <stdint.h>

#define FIFO_SIZE   32

static uint8_t * fifo = 0;
static uint8_t next_index = 0;
static uint8_t oldest_index = 0;
static uint8_t count = 0;

/* Initializes the fifo buffer with FIFO_SIZE*/
void init_fifo();

/* Adds a new value into the buffer */
void add_fifo(uint8_t data);

/* Returns the oldest value in the buffer */
uint8_t get_fifo(void);

/* Dumps the fifo outputs oldest -> newest through UART */
void dump_fifo_uart(void);


#endif /* DRIVERS_HEADERS_FIFO_H_ */
