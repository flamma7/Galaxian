/*
 * fifo.c
 *
 *  Created on: Nov 3, 2017
 *      Author: luke
 */

#include "Headers/fifo.h"
#include "Headers/uart.h"
#include <stdlib.h>


fifo_buffer* init_fifo(uint8_t size)
{
    fifo_buffer* buf = (fifo_buffer *)malloc(sizeof(fifo_buffer));
    buf->size = size;
    buf->buffer = (FIFO_DATA_TYPE *) malloc(sizeof(FIFO_DATA_TYPE) * buf->size);
    buf->next_index = 0;
    buf->oldest_index = 0;
    buf->count = 0;
    return buf;
}

void add_fifo(fifo_buffer* buf, FIFO_DATA_TYPE data)
{
    buf->buffer[buf->next_index] = data;

    // only add to the count if the buffer is not full
    if(buf->count != buf->size)
        buf->count++;

    if(buf->next_index == buf->oldest_index && buf->count == buf->size)
    {
        buf->oldest_index = next_fifo(buf->size, buf->oldest_index);
    }
    buf->next_index = next_fifo(buf->size, buf->next_index);
}

FIFO_DATA_TYPE get_fifo(fifo_buffer* buf)
{
    // no warnings thrown here if user gets from empty buffer
    if(buf->count == 0)
        return 0;

    FIFO_DATA_TYPE data = buf->buffer[buf->oldest_index];
    buf->oldest_index = next_fifo(buf->size, buf->oldest_index);
    buf->count--;
    return data;
}

void dump_fifo_uart(fifo_buffer* buf)
{
    // loop for as many counts
    uint8_t i = 0;
    uint8_t old_index = buf->oldest_index;
    while(i < buf->count)
    {
        transmit_char((char) buf->buffer[old_index]);
        i++;
        old_index = next_fifo(buf->size, old_index);
    }
    buf->count = 0;
    buf->next_index = 0;
    buf->oldest_index = 0;
}


uint8_t next_fifo(uint8_t size, uint8_t cur_index)
{
    return (cur_index + 1) % size;
}

uint8_t prev_fifo(uint8_t size, uint8_t cur_index)
{
    if(cur_index == 0)
        return size - 1;
    else
        return cur_index - 1;
}
