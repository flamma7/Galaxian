/*
 * uart.h
 *
 *  Created on: Sep 15, 2017
 *      Author: luke
 */

#ifndef DRIVERS_HEADERS_UART_H_
#define DRIVERS_HEADERS_UART_H_

#include <stdint.h>
// a better procedure is to make a buffer with intrpts that publish the letters

/* Configures the eUSCI_A module to UART mode */
void config_uart();
static void _config_baud_9600();
static void _uitoa32(uint32_t num, char * str);

/* Transmits a string over UART, reads until NULL terminator */
void transmit_str(const char * str);
/* Transmits a single char over UART */
void transmit_char(const char a);

/* Convert an unsigned number to string and transmit */
void transmit_num8(uint8_t num);
void transmit_num16(uint16_t num);
void transmit_num32(uint32_t num);

// read functions

#endif /* DRIVERS_HEADERS_UART_H_ */
