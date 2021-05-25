/*
 * File:   DS1631.c
 * Author: raykman
 * FINAL
 * Created on May 2, 2021, 9:34 PM
 */


#include "xc.h"
#include "math.h"
#include "DS1631.h"
#include "I2C.h"



void config_DS1631(void){
    startI2C2();
    putI2C2(DS1631_ADDRESS);
    putI2C2(DS1631_CMD_ACCESS_CONFIG);
    putI2C2(DS1631_CONFIG_DATA);
    stopI2C2();
}

void DS1631_startConvert(void){
    startI2C2();
    putI2C2(DS1631_ADDRESS);
    putI2C2(DS1631_CMD_START_CONVERT);
    stopI2C2();
}

float DS1631_readTemp(void){
    startI2C2();
    putI2C2(DS1631_ADDRESS);
    putI2C2(DS1631_CMD_READ_TEMP);
    rstartI2C2();
    putI2C2(DS1631_ADDRESS_READ);
    unsigned char temp_hi = getI2C2(I2C_ACK);
    unsigned char temp_lo = getI2C2(I2C_NACK);
    stopI2C2();
    float temp = 0;
    int i;
    for (i=0;i<8;i++){
        if(temp_hi & (1<<i)){
            // incorporate negative situation
            temp = temp + pow(2,i);
        }
        if(temp_lo & (1<<i)){
            temp = temp + pow(2,-(8-i));
        }
    }
    temp = (1.8*temp) +32; // Fahrenheit Conversion
    
    return(temp);
}

