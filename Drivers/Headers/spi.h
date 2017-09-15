/*
 * spi.h
 *
 *  Created on: Sep 15, 2017
 *      Author: luke
 */

#ifndef DRIVERS_HEADERS_SPI_H_
#define DRIVERS_HEADERS_SPI_H_

/* Crystalfontz CFAF128128B-0145T*/
    // 20 FPS
    // 262K colors, contrast 350
#include <stdint.h>

/* Configures pins 4.1(STE), 1.5(SCK), 1.6(MOSI), 1.7(MISO)
 * for SPI mode using UCB0CTLW0 */
void configure_SPI_p14_p15_p16_p17_UCB0CTLW0(void);
void _configure_SPI_p14_p15_p16_p17_UCB0CTLW0_pins(void);

uint8_t read_spi(uint8_t reg);
void write_spi(uint8_t reg, uint8_t data);

/* Make a begin transaction and end transaction function?? */
/* Or simply a send and receive thing */


/* J1.7 LCD SPI clock = p1.5
 * J2.13 LCD SPI chip select = p5.0
 * J2.15 LCD SPI MOSI = p1.6
 * J4.31 LCD reset pin = p3.7
 * J4.39 LCD backlight
 *    multiplexed with RGB LED through J5..?
 *    */

/* Receive and transmit operations operate concurrently
 * I'll probably need to work the slave select myself
 * Questinons:
 * 7-bit or 8-bit data len?
 * LSB or MSB first
 * 3-pin or 4pin
 */

#endif /* DRIVERS_HEADERS_SPI_H_ */
