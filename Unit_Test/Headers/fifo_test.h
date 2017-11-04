/*
 * fifo_test.h
 *
 *  Created on: Nov 3, 2017
 *      Author: luke
 */

#ifndef UNIT_TEST_HEADERS_FIFO_TEST_H_
#define UNIT_TEST_HEADERS_FIFO_TEST_H_

#include "../../Drivers/Headers/fifo.h"

void Test_Fifo();

void test_uint16_fifo(fifo_buffer* buf);
void test_char_fifo(fifo_buffer* buf);

void test_next_prev_fifo(fifo_buffer* buf);

#endif /* UNIT_TEST_HEADERS_FIFO_TEST_H_ */
