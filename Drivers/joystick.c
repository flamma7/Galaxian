/*
 * joystick.c
 *
 *  Created on: Nov 4, 2017
 *      Author: luke
 */

#include "msp.h"
#include "Headers/joystick.h"
#include "Headers/fifo.h"

void init_joystick()
{
// configure pins pg 501
    // J1.2 horizontal = MSP p6.0 -> secondary A15 (out of 23)
    // J3.26 Vertical == MSP p4.4 -> 4th A9
    // p6.0 primary mode
    P6SEL0 |= BIT0;
    P6SEL1 &= ~BIT0;
    // p4.4 tertiary mode
    P4SEL0 |= BIT4;
    P4SEL1 |= BIT4;

    // Set up for 8 bit'll do
    ADC14->CTL0 &= ~ADC14_CTL0_ENC;     // reset
    ADC14->CTL0 &= ~ADC14_CTL0_SC;

    ADC14->CTL0 |= ADC14SSEL2;


    ADC14CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;    // ready for conversions
    ADC14CTL0 |= ADC14_CTL0_ON;


}

JOYSTICK_ERR get_joystick(JOYSTICK_DATA_TYPE* x, JOYSTICK_DATA_TYPE* y)
{

}

void stop_joystick()
{

}

void ADC14_Handler(void)
{
    ;
}
