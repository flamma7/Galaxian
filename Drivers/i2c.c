/*
 * i2c.c
 *
 *  Created on: Sep 15, 2017
 *      Author: luke
 */

#include "msp.h"
#include "Headers/i2c.h"

/*
 * Configures pins 6.4 (SDA) and 6.5 (SCL) for I2C mode
 * Also configures register UCB1CTLW0 for I2C mode
 * See pg 160 of MSP432p401r_Overview.pdf for pin configs
 */
void configure_I2C_p64_p65_UCB1CTLW0(void)
{
        /* Configure pin 6.4 (SDA) and 6.5 (SCL) for I2C*/
        P6SEL0 |= BIT4 | BIT5;
        P6SEL1 &= ~BIT4;
        P6SEL1 &= ~BIT5;
        P6REN |= BIT4 | BIT5;       // init pull up resistors

        /* Configure UCB1CTLW0 for I2C mode */
        UCB1CTLW0 |= UCSWRST;           // set software reset
        UCB1CTLW0 |= UCSSEL_2;          // SMCLK clock = 3MHz clock
        UCB1BRW = 0x000F;               // baudrate = SMCLK / 0x0F = 200kHz
                                        // within I2C rate of 100-400kHz
        UCB1CTLW0 |= UCSYNC;            // synchronous mode
        UCB1CTLW0 |= UCMODE_3;          // I2C mode
        UCB1CTLW0 |= UCMST;             // Master mode
        UCB1CTLW0 &= ~UCMM;             // Single master
        UCB1CTLW0 &= ~UCSLA10;          // 7-bit slave address
        UCB1CTLW0 &= ~UCSWRST;          // disable software reset

        //__enable_interrupt();
        //UCB1IE |= UCNACKIE;
        //NVIC_EnableIRQ(EUSCIB1_IRQn); //Enable p1.4 interrupt with NVIC (STEP 7)
}

/* Transmits one byte of data to given register of slave_addr */
I2C_ERR writeByteUCB1(uint8_t slave_reg, uint8_t data)
{
    UCB1CTLW0 |= UCTR;              // set to transmitter mode
    UCB1I2CSA = UCB1_SLAVE_ADDR;    // set the slave address

    UCB1CTLW0 |= UCTXSTT;           // generate START
    while(!(UCB1IFG & UCTXIFG0));   // wait for open bus
    while(UCB1CTLW0 & UCTXSTT);     // wait for slave addr to be sent
    UCB1TXBUF = slave_reg;          // specify 8 bit slave reg addr
    while(!(UCB1IFG & UCTXIFG0));   // wait for open bus
    UCB1TXBUF = data;               // send 8 reg addr LSBs
    UCB1CTLW0 |= UCTXSTP;           // generate STOP

    if(UCB1IFG & UCNACKIFG)
        return NACK_ERROR;
    else
        return NO_ERROR;
}

uint8_t readByteUCB1(uint8_t slave_reg)
{
    uint8_t data;

    UCB1CTLW0 |= UCTR;              // set to write mode
    UCB1I2CSA = UCB1_SLAVE_ADDR;    // set the slave address

    UCB1CTLW0 |= UCTXSTT;           // generate START
    while(!(UCB1IFG & UCTXIFG0));   // wait for open bus
    while(UCB1CTLW0 & UCTXSTT);     // wait for slave addr to be sent
    UCB1TXBUF = slave_reg;          // specify 8 bit slave reg addr
    UCB1CTLW0 |= UCTXSTP;           // generate STOP

    UCB1CTLW0 &= ~UCTR;             // set to read mode
    UCB1CTLW0 |= UCTXSTT;           // generate RESTART
    while(UCB1CTLW0 & UCTXSTT);     // wait for slave addr to be sent
    while(!(UCB1IFG & UCRXIFG));    // wait for data to be received
    data = UCB1RXBUF;
    UCB1CTLW0 |= UCTXSTP;           // generate STOP

    return data;
}
