/*
 * File:   ui.c
 * Author: raykman
 * FINAL
 * Created on May 11, 2021, 9:26 PM
 */


#include "xc.h"
#include <stdio.h>
#include "DS1631.h"
#include "rgbLED.h"
#include "lcd.h"
#include "buttons.h"
#include "ui.h"
#include "trigger.h"
#include "spi.h"

// Tracking Temperature
double temp;
double old_temp = 72.0;
double low_temp = 73.0 ;
double high_temp = 75.0, old_high_temp = 0;
double temp_diff;
int set = 1;
extern int edit_mode; //Indicates whether we are in low, high or no edit for temp range

void configure_ui(){
    
    /* Configure UI timer */
    
    UI_TIMER_OFF;
    UI_TIMER_CONFIG;
    UI_TIMER_RESET;
    UI_TIMER_PERIOD = UI_TIMER_CYCLE_TIME; //timer set to every 200 ms
    UI_TIMER_INTERRUPT_CONFIG;
    UI_TIMER_ON;
}

void __attribute__((__interrupt__, no_auto_psv)) _T3Interrupt(void)
{
    UI_TIMER_ON;
    ui();
    UI_TIMER_FLAG_CLEAR;   //Clear Timer1 Interrupt flag
}

void ui(void){ // Update temp, system status, led, LCD panel, entry to log
    char high_buffer[50]; //character array to store float values
    char low_buffer[50];
    char temp_buffer[50];
    temp = DS1631_readTemp(); //Reads in temp from sensor
    if (temp > old_temp){
        temp_diff = temp - old_temp;
        if (temp_diff>.3){
            printf("    Temperature increased %.2f degrees to %.2f\r\n",temp_diff,temp); //Log output
            old_temp = temp;
        }
          
    }
    else if (temp < old_temp){
        temp_diff = old_temp - temp;
        if (temp_diff>.3){
            printf("    Temperature decreased %.2f degrees to %.2f\r\n",temp_diff,temp); // Log output
            old_temp = temp;
        }
    }
    LCDclr();
    sprintf(temp_buffer,"%.1f",temp);
    sprintf(high_buffer,"%.0f",high_temp);
    sprintf(low_buffer,"%.0f",low_temp);
    LCDBignum(temp_buffer); // Write temp as big number
    LCDWrite(LCD_COMMAND,0x80); //Shifts temp range to bottom left of LCD for temp range
    LCDWrite(LCD_COMMAND,0x45);
    LCDCharacter('[');
    LCD_string(low_buffer); // Low temp range
    LCD_string(",");
    LCD_string(high_buffer); // High temp range
    LCDCharacter(']');
    LCDWrite(LCD_COMMAND,0x80|55); //Shifts cursor to end of the big number
    LCDWrite(LCD_COMMAND,0x43);
    LCDCharacter('.');
    LCDCharacter(temp_buffer[3]); // Adds the tenth place of temp
    if (temp< low_temp+.5){ // Logic to set Heating
        rgbLED_Set(RED);
        LCDFlame();
        if (set){
           printf("    Heat has turned on\r\n");
           set = !set;
        }
    }
    else if(temp>high_temp+.5){ // Logic to set Cooling
        rgbLED_Set(BLUE);
        LCDSnow();
        if (set){
           printf("    Cooling has turned on\r\n");
           set = !set;
        }
    }
    else{
        rgbLED_Set(GREEN); // Within temp range
        set = 1;
    }
    
    if (edit_mode == LOW_EDIT){
        LCDWrite(LCD_COMMAND,0x80|70);
        LCDWrite(LCD_COMMAND,0x40);
        LCDCharacter('L');
    }
    else if (edit_mode == HIGH_EDIT){
        LCDWrite(LCD_COMMAND,0x80|70);
        LCDWrite(LCD_COMMAND,0x40);
        LCDCharacter('H');
    }
    
}
