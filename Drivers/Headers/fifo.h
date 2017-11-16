/*
 * fifo.h
 *
 *  Created on: Nov 3, 2017
 *      Author: luke
 *
 *      FIFO buffer library, fifo_buffer structure contains
 *          all important aspects of the buffer
 *          Can handle any number of fifo's
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
#define FIFO_DATA_TYPE   uint16_t

typedef struct fifo_buffer_t
{
    uint8_t size;
    FIFO_DATA_TYPE * buffer;
    uint8_t next_index;
    uint8_t oldest_index;
    uint8_t count;
}fifo_buffer;

/* Initializes and returns a fifo buffer with the given size */
fifo_buffer* init_fifo(uint8_t size);
/* Adds a new value into the buffer */
void add_fifo(fifo_buffer* buf, FIFO_DATA_TYPE data);
/* Returns the oldest value in the buffer, empty is 1 for empty buffer and 0 for non-empty */
FIFO_DATA_TYPE get_fifo(fifo_buffer* buf, uint8_t* empty);
/* Dumps the fifo outputs oldest -> newest through UART
 * Empties the buffer */
void dump_fifo_uart(fifo_buffer* buf);



/* Returns the next index of the given ptr */
static uint8_t next_fifo(uint8_t size, uint8_t cur_index);


// Unused function
//#define PREV_FIFO
#ifdef  PREV_FIFO
/* Returns the previous index*/
static uint8_t prev_fifo(uint8_t size, uint8_t cur_index);
#endif

#endif /* DRIVERS_HEADERS_FIFO_H_ */
