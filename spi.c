/*
 * File:   spi.c
 * Author: raykman
 * FINAL
 * Created on May 11, 2021, 9:26 PM
 */


#include "xc.h"
#include "spi.h"

void config_SPI(){
    MASTER;
    PRIMARY_PRE;
    SEC_PRE;
    TRANSFER_MODE;
    SAMPLE;
    OUTPUT_FALLING;
    CLK;
    SPI_EN;
}

unsigned char ioSPI(unsigned char data){
    SPI1BUF = data; // Put data in transmit buffer
    while(!SPI1STATbits.SPIRBF){} // Wait until received 
    return(SPI1BUF); // Return received byte
}

