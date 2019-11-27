/* 
 * File:   UART.h
 * Author: Ricardo
 *
 * Created on 18 de febrero de 2017, 05:55 PM
 */
#include "system.h"

#ifndef UART_H
#define	UART_H

void UART_config(unsigned long baudrate);
unsigned int urx(void);
void utx(unsigned int data);

#endif	/* UART_H */

