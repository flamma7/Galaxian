/*
 * uart.c
 *
 *  Created on: Sep 15, 2017
 *      Author: luke
 */

#include "msp.h"
#include "Headers/uart.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

// 4 eUSCI_A modules !

// assumes str has been given radix of 3
static void uitoa8(uint8_t num, char * str)
{
    str[2] = num % 10;
    uint8_t i;
    for(i = 1; i > -1; i--)
    {
        num = num / 10;
        str[i] = (num % 10) + 48;
    }
    str[3] = '\0';
}

void transmit_char(const char a)
{
    while(!(UCA0IFG & UCTXIFG));
    UCA0TXBUF = a;
}

void transmit_str(const char * str)
{
    uint8_t i = 0;
    while(str[i] != '\0')
    {
        if(UCA0IFG & UCTXIFG)
            UCA0TXBUF = str[i++];
    }
}

void transmit_num8(uint8_t num)
{
    uint8_t radix = 3;
    char str[radix + 1];
    uitoa8(num, str);
    transmit_str(str);
}

void transmit_num16(uint16_t num)
{
    uint8_t radix = 3;
    char str[radix];
//    itoa(num, str, radix);
    transmit_str(str);
}

void transmit_num32(uint32_t num)
{

}


void config_uart()
{
    P1SEL0 |= BIT2 | BIT3;       //Configures UART mode
    P1SEL1 &= ~BIT2 & ~BIT3;
    UCA0CTLW0 |= UCSWRST;
    UCA0CTLW0 &= ~UCPEN;
    UCA0CTLW0 &= ~UCMSB;
    UCA0CTLW0 &= ~UC7BIT;
    UCA0CTLW0 &= ~UCSPB;
    UCA0CTLW0 &= ~UCMODE_3;             // mode 0
    UCA0CTLW0 &= ~UCSYNC;
    _config_baud_9600();
    // UCAxCTLW1 register?

    UCA0CTLW0 &= ~UCSWRST;
}

static void _config_baud_9600()
{
    UCA0CTLW0 |= UCSSEL_2;
    UCA0MCTLW |= UCOS16;
    UCA0BRW |= 19;                      // UCBRx
    UCA0MCTLW |= 0xAA00;                // UCBRSx
    UCA0MCTLW |= 0x80;                  // UCBRFx
//    UCA0MCTLW |=      // how to configure?
}
