/*
 * joystick_test.c
 *
 *  Created on: Nov 4, 2017
 *      Author: luke
 */

#include "Headers/joystick_test.h"
#include "../Drivers/Headers/uart.h"
#include "../Drivers/Headers/joystick.h"
#include <assert.h>
#include <stdint.h>


void Joystick_Tester()
{
    transmit_str("Testing Joystick!");
    JOYSTICK_DATA_TYPE x,y;
    assert(get_joystick(&x,&y) == JOYSTICK_NO_INIT);
    assert(x == 0 && y == 0);
    init_joystick();
    get_pos_joystick_test();
}



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
