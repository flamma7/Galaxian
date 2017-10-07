/*
 * adc.c
 *
 *  Created on: Oct 6, 2017
 *      Author: luke
 */

#include "Headers/adc.h"
#include "msp.h"


void configADC()
{


    // config pins for adc

    // TODO Make these into one statement
    ADC14->CTL0 &= ~ADC14_CTL0_SC;              // No sample-and-conv-start
    ADC14->CTL0 &= ~ADC14_CTL0_ENC;             // ADC14 disabled
    ADC14->CTL0 &= ~ADC14_CTL0_ON;              // ADC off or on
    ADC14->CTL0 |= ADC14_CTL0_MSC; // sample-and-conversions performed after prior conversion completes
//    ADC14->CTL0
}
