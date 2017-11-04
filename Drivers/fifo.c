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
    buf->buffer = (FIFO_DATA_TYPE *) malloc(sizeof(FIFO_DATA_TYPE) * size);
    buf->next_index = 0;
    buf->oldest_index = 0;
    buf->empty = 1;
    return buf;
}

void add_fifo(fifo_buffer* buf, FIFO_DATA_TYPE data)
{
    buf->buffer[buf->next_index] = data;
    buf->empty = 0;

    if(buf->next_index == buf->oldest_index && buf->empty != 0)
    {
        buf->oldest_index = next_fifo(buf->size, buf->oldest_index);
    }
    buf->next_index = next_fifo(buf->size, buf->next_index);
}

FIFO_DATA_TYPE get_fifo(fifo_buffer* buf)
{
    FIFO_DATA_TYPE data = buf->buffer[buf->oldest_index];
    buf->oldest_index = prev_fifo(buf->size, buf->oldest_index);
    return data;
}


static uint8_t next_fifo(uint8_t size, uint8_t cur_index)
{
    return (cur_index + 1) % size;
}

static uint8_t prev_fifo(uint8_t size, uint8_t cur_index)
{
    if(cur_index == 0)
        return size - 1;
    else
        return cur_index - 1;
}
