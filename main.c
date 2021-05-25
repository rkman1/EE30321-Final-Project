/*
 * File:   main.c
 * Author: raykman
 * FINAL
 * Created on May 11, 2021, 9:16 PM
 */


#include "xc.h"
#include <stdio.h>

#include "config.h"
#include "uart.h"
#include "i2c.h"
#include "spi.h"
#include "DS1631.h"
#include "trigger.h"
#include "buttons.h"
#include "rgbLED.h"
#include "lcd.h"
#include "ui.h"


int main(void) {
    
    // Setup serial logging
    configUART();
    printf("\033[2J\033[;H");
    printf("BEGINNING OF LOG\r\n\n");
    printf("Initializing System\r\n");
    
    printf("    Configuring Hardware\r\n");
    // Setup LCD screen to provide user messages
    config_SPI();
    configure_lcd();
    LCDclr();
    LCD_string("Initializing");
    
    // Configure system
    config_I2C();
    config_DS1631();
    configure_buttons();
    configure_rgbLED();
    
    printf("    Start Measuring Temperature\r\n");
    DS1631_startConvert();
    
    printf("    Start the UI\r\n\n");
    configure_ui();
    
    printf("System Up and Running\r\n");
    
    while(1){
        Idle();
    }
    
    return 0;
}
