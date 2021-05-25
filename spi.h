/* 
 * File:   spi.h
 * Author: Ray Kman
 * FINAL
 * Created on May 2, 2021
 */

#ifndef SPI_H
#define SPI_H

#include <xc.h>

#define MASTER SPI1CON1bits.MSTEN = 1; // Make master
#define PRIMARY_PRE SPI1CON1bits.PPRE = 0b11; // 1:1 primary prescale
#define SEC_PRE SPI1CON1bits.SPRE = 0b111; // 1:1 secondary prescale
#define TRANSFER_MODE SPI1CON1bits.MODE16 = 0; // 8-bit transfer mode
#define SAMPLE SPI1CON1bits.SMP = 0; // Sample in middle
#define OUTPUT_FALLING SPI1CON1bits.CKE = 1; // Output on falling edge
#define CLK SPI1CON1bits.CKP = 0; // CLK idle state low
#define SPI_EN SPI1STATbits.SPIEN = 1; // Enable SPI1

void config_SPI();
unsigned char ioSPI(unsigned char data);

#endif

