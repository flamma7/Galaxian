/*
 * uart.c
 *
 *  Created on: Sep 15, 2017
 *      Author: luke & derek
 *
 *      See Header file for implementation
 */

#include "msp.h"
#include "Headers/uart.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


#define ASCII_ZERO          48

// 4 eUSCI_A modules !

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
    UCA0CTLW0 &= ~UCSWRST;
}

void transmit_char(const unsigned char a)
{
    while(!(UCA0IFG & UCTXIFG));
    UCA0TXBUF = a;
}

void transmit_str(const char * str)
{
    uint8_t i = 0;
    while(str[i++] == '0');             // skip through leading zeros (for number transmits)
    i--;                                // Go back one place
    while(str[i] != '\0')
    {
        if(UCA0IFG & UCTXIFG)
            UCA0TXBUF = str[i++];
    }
    transmit_char('\r');
    transmit_char('\n');
}

void transmit_num32(uint32_t num)
{
    uint32_t radix = 11;                // max chars in decimal 32 bit (10) + '\0'
    char * str = (char *) malloc(sizeof(char) * radix);
    _uitoa32(num, str);
    transmit_str(str);
    free(str);
}

static void _config_baud_9600()
{
    UCA0CTLW0 |= UCSSEL_2;
    UCA0MCTLW |= UCOS16;
    UCA0BRW |= 19;                      // UCBRx
    UCA0MCTLW |= 0xAA00;                // UCBRSx
    UCA0MCTLW |= 0x80;                  // UCBRFx
}

// assumes str has radix of >= 11
static void _uitoa32(uint32_t num, char * str)
{
    str[9] = (num % 10) + ASCII_ZERO;
    int8_t i;
    for(i = 8; i > -1; i--)
    {
        num = num / 10;
        str[i] = (num % 10) + ASCII_ZERO;
    }
    str[10] = '\0';
}
