/*
 * File:   I2C.c
 * Author: raykman
 *
 * Created on May 2, 2021, 8:49 PM
 */


#include "xc.h"

#include <stdio.h>
#include "i2c.h"


#define FCY 7370000/2 //Frc runs at 7.37 MHz
#define FSCL 100      // Clock frequency in kHz


void config_I2C(){
    
    // Determine the Baud Rate Generator reload value
    //  brg = FCY/(1000*FSCL) - (FCY/1000000) - 2 = 31;
    I2C2BRG = 0x1F;
    
    // Enable I2C
    I2C2CONbits.I2CEN = 1;
}

void rstartI2C2(void){
    I2C2CONbits.RSEN = 1; //look at datasheet
    while(I2C2CONbits.RSEN);

}
void startI2C2(void){
    I2C2CONbits.SEN = 1; // initialize start
    while(I2C2CONbits.SEN); // wait until start finished
}

BYTE putI2C2(BYTE data){
    I2C2TRN = data; // put data in transmit buffer
    while(I2C2STATbits.TRSTAT); // wait until transfer finished
    
    return(I2C2STATbits.ACKSTAT); // return ACK signal
}

void stopI2C2(void){
    I2C2CONbits.PEN = 1; //initiate stop, PEN = 1
    while(I2C2CONbits.PEN); // wait until stop finished
}

BYTE getI2C2 (BYTE ack2send){
    BYTE inByte;
    
    while(I2C2CON & 0x1F); //wait for idle condition
    I2C2CONbits.RCEN=1;    // enable receive
    while(!I2C2STATbits.RBF); //wait for receive byte
    inByte = I2C2RCV; //read byte
    
    while(I2C2CON & 0x1F); //wait for idle
    I2C2CONbits.ACKDT = ack2send; // ACK type to send
    I2C2CONbits.ACKEN = 1; // enable ACK bit transmission
    while(I2C2CONbits.ACKEN); // wait until done
    
    return(inByte);
}