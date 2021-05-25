/* 
 * File:   DS1631.h
 * Author: rls
 * Modified: Ray Kman
 * FINAL
 * Created on May 2, 2021
 */

#ifndef DS1631_H
#define DS1631_H

#include <xc.h>

#define FCY 7370000/2
#define FSCL 100

#define NO_I2C_ERROR 1
#define I2C_ERROR 0

#define DS1631_ADDRESS 0b10010000
#define DS1631_ADDRESS_READ 0b10010001
#define DS1631_CMD_ACCESS_CONFIG 0xAC
#define DS1631_CMD_START_CONVERT 0x51
#define DS1631_CMD_STOP_CONVERT 0x22
#define DS1631_CMD_READ_TEMP 0xAA
#define DS1631_CMD_ACCESS_TH 0xA1
#define DS1631_CMD_ACCESS_TL 0xA2
#define DS1631_CMD_SOFTWARE_POR 0x54
#define DS1631_CONFIG_DATA 0x0C


void config_DS1631(void);
void DS1631_startConvert(void);
float DS1631_readTemp(void);

#endif