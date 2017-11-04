/*
 * fifo.h
 *
 *  Created on: Nov 3, 2017
 *      Author: luke
 *
 *      FIFO buffer library, fifo_buffer structure contains
 *          all important aspects of the buffer
 *
 *      For operation:
 *      1) call init_fifo() and get a buffer
 *      2) add_fifo(data)
 *      3) get_fifo(data)
 *
 */

#ifndef DRIVERS_HEADERS_FIFO_H_
#define DRIVERS_HEADERS_FIFO_H_

#include <stdint.h>

// Limitation of 1 universal data type for all fifo's
#define FIFO_DATA_TYPE   uint8_t

typedef struct fifo_buffer_t
{
    uint8_t size;
    FIFO_DATA_TYPE * buffer;
    uint8_t next_index;
    uint8_t oldest_index;
    uint8_t count;
}fifo_buffer;

/* Initializes and returns a fifo buffer with FIFO_SIZE*/
fifo_buffer* init_fifo(uint8_t size);

/* Adds a new value into the buffer */
void add_fifo(fifo_buffer* buf, FIFO_DATA_TYPE data);

/* Returns the oldest value in the buffer */
FIFO_DATA_TYPE get_fifo(fifo_buffer* buf);

/* Dumps the fifo outputs oldest -> newest through UART */
void dump_fifo_uart(fifo_buffer* buf);

/* Returns the next index */
static uint8_t next_fifo(uint8_t size, uint8_t cur_index);
/* Returns the previous index*/
static uint8_t prev_fifo(uint8_t size, uint8_t cur_index);


#endif /* DRIVERS_HEADERS_FIFO_H_ */
