/*
 * i2c.h
 *
 *  Created on: Sep 15, 2017
 *      Author: luke
 */

#ifndef DRIVERS_HEADERS_I2C_H_
#define DRIVERS_HEADERS_I2C_H_

#define UCB1_SLAVE_ADDR 0x13


#include <stdint.h>

typedef enum I2C_ERR_t{
    NO_ERROR = 0,
    NACK_ERROR = 1,
}I2C_ERR;

/* Configures pins 6.4 & 6.5 for I2C mode using UCB1CTLW0 */
void configure_I2C_p64_p65_UCB1CTLW0(void);
/* Transmits one byte of data to given register of slave_addr */
I2C_ERR writeByteUCB1(uint8_t slave_reg, uint8_t data);
/* Returns one byte of data of given register of slave address */
uint8_t readByteUCB1(uint8_t slave_reg);

#endif /* DRIVERS_HEADERS_I2C_H_ */
