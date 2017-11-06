/*
 * joystick_test.c
 *
 *  Created on: Nov 4, 2017
 *      Author: luke
 */

#include "msp.h"
#include "Headers/joystick_test.h"
#include "../Drivers/Headers/uart.h"
#include "../Drivers/Headers/joystick.h"
#include <assert.h>
#include <stdint.h>

//#define STOP_JOYSTICK_TEST
//#define GET_POS_JOYSTICK_TEST

void Joystick_Tester()
{
    transmit_str("Testing Joystick!");
    JOYSTICK_DATA_TYPE x,y;
//    assert(get_joystick(&x,&y) == JOYSTICK_NO_INIT);
//    assert(x == 0 && y == 0);
    init_joystick();
    uart_positions();
#ifdef GET_POS_JOYSTICK_TEST
    get_pos_joystick_test();
#endif
#ifdef STOP_JOYSTICK_TEST
    stop_restart_joystick_test();
#endif
}

static void uart_positions()
{
    uint32_t val[32];
    uint32_t val2[32];
    uint8_t i = 0;
    for(i=0; i < 32; i++)
    {
        val[i] = ADC14->MEM[i];
        val2[i] = val[i];
    }
    while(1)
    {
        ADC14->CTL0 |= ADC14_CTL0_SC;
        for(i=0; i < 32; i++)
        {
            val[i] = ADC14->MEM[i];
        }
        for(i=0; i < 32; i++)
        {
            if(val[i] != val2[i])
            {
                transmit_str("Not equal");
                transmit_num32((uint32_t) i);
                transmit_num32(val[i]);
            }
            val2[i] = val[i];
        }

    }
}

#ifdef GET_POS_JOYSTICK_TEST
static void get_pos_joystick_test()
{
    transmit_str("Testing Joystick Position.");
    JOYSTICK_DATA_TYPE x=0, y=0;
    while(1)
    {
        transmit_str("--------");
        assert(get_joystick(&x,&y) == JOYSTICK_NO_ERR);
        transmit_num32((uint32_t) x);
        transmit_num32((uint32_t) y);
    }
}
#endif

#ifdef STOP_JOYSTICK_TEST
static void stop_restart_joystick_test()
{
    stop_joystick();
    uint8_t i;
    for(i = 0; i < 0xffff; i++);        // simple delay
    restart_joystick();
}
#endif
