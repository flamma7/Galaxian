/*
 * fifo_test.c
 *
 *  Created on: Nov 3, 2017
 *      Author: luke
 */

#include "Headers/fifo_test.h"
#include "../Drivers/Headers/fifo.h"
#include "../Drivers/Headers/uart.h"
#include <assert.h>

//#define FIFO_TEST_NEXT_PREV
//#define FIFO_TEST_UINT16
//#define FIFO_TEST_UINT8

void Test_Fifo()
{
    transmit_str("Testing FIFO");
    fifo_buffer* buf = init_fifo(20);

#ifdef FIFO_TEST_NEXT_PREV
    test_next_prev_fifo(buf);
#endif
#ifdef FIFO_TEST_UINT16
    test_uint16_fifo(buf);
#endif
#ifdef FIFO_TEST_UINT8
    test_char_fifo(buf);
#endif
}


#ifdef FIFO_TEST_UINT16
void test_uint16_fifo(fifo_buffer* buf)
{
    transmit_str("Testing uint16 FIFO");
    uint8_t empty = 0;
    uint16_t data = get_fifo(buf, &empty);
    add_fifo(buf, 0xFFFF);
    add_fifo(buf, 0xFFFF);
    add_fifo(buf, 0xFFFF);
    add_fifo(buf, 0xFFFF);
    add_fifo(buf, 0xAAAA);
    transmit_str("Dumping FIFO");
    dump_fifo_uart(buf);
}
#endif

#ifdef FIFO_TEST_UINT8
void test_char_fifo(fifo_buffer* buf)
{
    uint8_t empty = 0;
    uint8_t data = get_fifo(buf, &empty);
    assert(empty == 1);

    // insert data into the buffer
    add_fifo(buf, 'A');
    data = get_fifo(buf, &empty);
    assert(empty == 0);
    transmit_char((uint8_t) data);
    transmit_str("Empty buffer?");
    add_fifo(buf, '1');
    add_fifo(buf, '2');
    add_fifo(buf, '3');
    add_fifo(buf, '4');
    data = get_fifo(buf, &empty);
    assert(empty == 0);
    transmit_char((uint8_t) data);
    add_fifo(buf, '5');
    add_fifo(buf, '6');
    add_fifo(buf, '7');
    data = get_fifo(buf, &empty);
    assert(empty == 0);
    transmit_char((uint8_t) data);
    add_fifo(buf, '8');
    add_fifo(buf, '9');
    add_fifo(buf, '0');
    data = get_fifo(buf, &empty);
    assert(empty == 0);
    transmit_char(data);
    add_fifo(buf, '1');
    add_fifo(buf, '1');
    add_fifo(buf, '1');
    add_fifo(buf, '1');
    transmit_str("Buff Size: ");
    transmit_num32((uint32_t) buf->size);
    transmit_str("Buff Count ");
    transmit_num32((uint32_t) buf->count);
    dump_fifo_uart(buf);
    transmit_str("\n\rAfter dump: ");
    add_fifo(buf, '1');
    add_fifo(buf, '1');
    add_fifo(buf, '1');
    dump_fifo_uart(buf);

    uint8_t j = 0;
    for(j; j < 44; j++)
    {
        add_fifo(buf, 'D');
    }
    dump_fifo_uart(buf);
}
#endif

#ifdef FIFO_TEST_NEXT_PREV

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
#endif
