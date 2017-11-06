/*
 * joystick.c
 *
 *  Created on: Nov 4, 2017
 *      Author: luke
 */

#include "msp.h"
#include "Headers/joystick.h"
#include "Headers/fifo.h"

void init_joystick() // single channel; single conversion
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
    ADC14->CTL0 &= ~ADC14_CTL0_ENC;         // reset
    ADC14->CTL0 &= ~ADC14_CTL0_SC;
    // SHI bit to trigger first conversion
    ADC14->CTL0 &= ~ADC14_CTL0_MSC;          // requires rising edge of SHI signal
    // TODO sample and hold time?
    ADC14->CTL0 |= ADC14_CTL0_CONSEQ_0;     // just single-channel conversion
    ADC14->CTL0 |= ADC14_CTL0_SSEL__ACLK;   // aclk clock
    ADC14->CTL0 |= ADC14_CTL0_DIV__8;       // clock divider by 8
//     TODO SHS and SHP bits?
    ADC14->CTL0 |= ADC14_CTL0_PDIV__64;     // predivide clock by 64
    ADC14->CTL1 |= ADC14_CTL1_RES__8BIT;    // 8 bit resolution

    // Thresholds? x2 types? they're fine where they are
    ADC14->MCTL[0] |= ADC14_MCTLN_INCH_9;       // INPUT A9 FOR MEM0



    ADC14->IER0 |= ADC14_IER0_IE0;          // Enable intrpt request for ADC14IFG0
    // read ADC14->IFGR0 to tell if intrpt is pending in ADC14MEM0
    // write to ADC14CLRIFGR0 to clear ADC14IG0

    ADC14->CTL0 |= ADC14_CTL0_ENC;         // READY
    ADC14->CTL0 |= ADC14_CTL0_SC;
    ADC14->CTL0 |= ADC14_CTL0_ON;

}

JOYSTICK_ERR get_joystick(JOYSTICK_DATA_TYPE* x, JOYSTICK_DATA_TYPE* y)
{
    ;
}


void stop_joystick()
{
    // poll busy bit until reset then clear ADC14ENC
    // ADC14->CTL0 & ADC14BUSY
}

void restart_joystick()
{
    // set ADC14ENC
}

void ADC14_Handler(void)
{
    ;
}
