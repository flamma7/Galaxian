/*
 * spi.c
 *
 *  Created on: Sep 15, 2017
 *      Author: luke
 */

#include "Headers/spi.h"
#include "msp.h"
#include <stdio.h>


void configure_SPI_p14_p15_p16_p17_UCB0CTLW0(void)
{
    UCB0CTLW0 |= UCSWRST;   // software reset
    UCB0CTLW0 |= UCCKPH;    // data changed on first UCLK edge?
    UCB0CTLW0 |= UCCKPL;    // clock polarity inactive high
    UCB0CTLW0 |= UCMSB;     // MSB first
    UCB0CTLW0 &= ~UC7BIT;   // 8-bit data
    UCB0CTLW0 |= UCMST;     // master mode
    UCB0CTLW0 |= UCMODE_0;  // 3-pin, p1.4(UCB0STE) doesn't have pin on MSP
    UCB0CTLW0 |= UCSYNC;    // Synchronous mode
    UCB0CTLW0 |= UCSSEL_3;  // SMCLK clock (3MHz)
    UCB0BRW = 4;            // 4 Bit clock prescalar
    //UCB0CTLW0 |= UCSTEM;  // STE pin used in 4-wire slave
    UCB0CTLW0 &= ~UCSWRST;  // register open for operation

    _configure_SPI_p14_p15_p16_p17_UCB0CTLW0_pins();
}

void _configure_SPI_p14_p15_p16_p17_UCB0CTLW0_pins(void)
{
    // page 139 of MSP432p401r_Overview.pdf
//  P1SEL1 &= ~BIT4;
//  P1SEL0 |= BIT4;     UCB0STE p1.4 doesn't have pin on MSP

    // New SS p4.1
    P4DIR |= BIT1;      // OUTPUT
    P4SEL1 &= ~BIT1;    // I/O mode
    P4SEL0 &= ~BIT1;
    P4OUT |= BIT1;      // Active low, start high

    P1SEL1 &= ~BIT5;
    P1SEL0 |= BIT5;

    P1SEL1 &= ~BIT6;
    P1SEL0 |= BIT6;

    P1SEL1 &= ~BIT7;
    P1SEL0 |= BIT7;
}

void write_spi(uint8_t reg, uint8_t data)
{
    P4OUT &= ~BIT1;                 // SS
    UCB0TXBUF = reg;
    while(!(UCB0IFG & UCTXIFG));    // wait for the data to be sent
    UCB0TXBUF = data;
    P4OUT |= BIT1;
}


/* When UCB0RXBUF has not been updated, it defaults to 0xFF */
uint8_t read_spi(uint8_t reg)
{
    P4OUT &= ~BIT1;                 // SS
    UCB0TXBUF = reg;
    while(!(UCB0IFG & UCRXIFG));    // wait for the data to be received
    UCB0TXBUF = 0xff;
    uint8_t data = UCB0RXBUF;
    printf("SPI Data1: %x\n", data);
    while(!(UCB0IFG & UCRXIFG));
    UCB0TXBUF = 0xff;
    while(!(UCB0IFG & UCRXIFG));
    data = UCB0RXBUF;
    printf("SPI Data2: %x\n", data);
    P4OUT |= BIT1;
    return data;
}



/* TODO
 *  1) Locate pins and make a spi library
 *  2) Make a adc read library
 *  3) Start making a CFAF128128B display library
 *  4) Create a state diagram of game
 *  5) Create data structures for game
 *  6) Create graphics for game
 *  7) Start putting it together->modular as possible of course ;)*/
