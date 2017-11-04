/*
 * fifo_test.c
 *
 *  Created on: Nov 3, 2017
 *      Author: luke
 */

#include "Headers/fifo_test.h"
#include "../Drivers/Headers/fifo.h"
#include "../Drivers/Headers/uart.h"

void Test_Fifo()
{
    transmit_str("Testing FIFO");
    fifo_buffer* buf = init_fifo(10);

//    test_next_prev_fifo(buf);



    // insert data into the buffer
    add_fifo(buf, 'A');
    uint8_t data = get_fifo(buf);
    transmit_char(data);
//    transmit_str("Empty buffer?");
//    add_fifo(buf, '1');
//    add_fifo(buf, '2');
//    add_fifo(buf, '3');
//    add_fifo(buf, '4');
//    add_fifo(buf, '5');
//    add_fifo(buf, '6');
//    add_fifo(buf, '7');
//    add_fifo(buf, '8');
//    add_fifo(buf, '9');
//    add_fifo(buf, '0');
//    add_fifo(buf, '1');
//    add_fifo(buf, '2');
//    dump_fifo_uart(buf);
}


// Note: next_fifo() and prev_fifo() were not static for this test
void test_next_prev_fifo(fifo_buffer* buf)
{
    transmit_str("Next Prev Fifo Test");

    transmit_str("Next insert: ");
    transmit_num32((uint32_t) buf->next_index);

    transmit_str("Buff Size: ");
    transmit_num32((uint32_t) buf->size);
    transmit_str("Buff Count ");
    transmit_num32((uint32_t) buf->count);

    uint8_t i;
    for(i = 0; i <= buf->size; i++)
    {
        transmit_str("After next_fifo(): ");
        buf->next_index = next_fifo(buf->size, buf->next_index);
        transmit_num32((uint32_t) buf->next_index);
    }


}
