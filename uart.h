/* 
 * File:   uart.h
 * Author: rls
 * Modified: Ray Kman
 * FINAL
 * Created on May 2, 2021
 */

#ifndef UART_H
#define UART_H

#include <xc.h>

#define BAUDRATE 19200
#define FCY 7370000/2

void configUART(void);
void putch(char c);

#endif

