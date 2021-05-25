/* 
 * File:   uart.h
 * Author: rls
 * Modified: Ray Kman
 * FINAL
 * Created on May 2, 2021
 */

#ifndef I2C_H
#define I2C_H

#include <xc.h>

#define I2C_ACK 0
#define I2C_NACK 1

typedef unsigned char BYTE;

void config_I2C();
void startI2C2(void);
void rstartI2C2(void);
BYTE putI2C2(BYTE);
void stopI2C2(void);
BYTE getI2C2(BYTE);

#endif
