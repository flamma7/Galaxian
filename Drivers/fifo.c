/*
 * fifo.c
 *
 *  Created on: Nov 3, 2017
 *      Author: luke
 */

#include "Headers/fifo.h"
#include "Headers/uart.h"
#include <stdlib.h>


void init_fifo()
{
    fifo = (uint8_t *) malloc(size(uint8_t) * FIFO_SIZE);
    // next_index, oldest_index, and count already in correct values
}
