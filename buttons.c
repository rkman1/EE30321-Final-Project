/*
 * File:   buttons.c
 * Author: raykman
 *  FINAL
 * Created on May 11, 2021, 9:24 PM
 */


#include "buttons.h"
#include <stdio.h>
#include "lcd.h"

extern double high_temp;
 extern double low_temp;
int button;
int edit_mode = 0;
int state = 0;

int check_buttons(){
    if ((SW_UP == PRESSED) && (SW_DOWN == PRESSED)){
        button = BOTH_PRESSED;
    }
    else if(SW_DOWN == PRESSED){
        button = DOWN_PRESSED;
    }
    else if (SW_UP == PRESSED){
        button = UP_PRESSED;
    }
    else{
        button = NONE_PRESSED;
    }
    return button;
}


void configure_buttons(){
    SW_UP_PIN = IN;
    SW_DOWN_PIN = IN;
    CN_UP_PIN = ON;
    CN_DOWN_PIN = ON;
    CN_UP_PULL = ON;
    CN_DOWN_PULL = ON;  
    INTCON2bits.GIE = 1;
    CN_INTERRUPT_CONFIG;
    BOUNCE_TIMER_OFF;
    BOUNCE_TIMER_CONFIG;
    BOUNCE_TIMER_RESET;
    BOUNCE_TIMER_PERIOD = BOUNCE_TIMER_CYCLE_TIME;
    BOUNCE_TIMER_INTERRUPT_CONFIG;
}


void __attribute__((__interrupt__, no_auto_psv)) _CNInterrupt(void)
{
    /* Controls the generation of the PWM waveform based on value of dimValue */
    CN_STATUS = 0; // Turn off CN interrupts
    PR1 = BOUNCE_TIMER_CYCLE_TIME; //Idles the program to debounce button
    BOUNCE_TIMER_ON;
    CN_FLAG = 0;   //Clear NC interrupt
}

void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
{
   
    BOUNCE_TIMER_OFF;
   
    CN_STATUS = 1; //Turn on CN interrupts
    button = check_buttons();
    switch(button){
         case BOTH_PRESSED: // Both pressed
             state = !state;
             if (state ==1){
                 if (edit_mode==0){ // Enter low temp range editing mode
                     edit_mode = LOW_EDIT;
                     printf("    System is programming Low Temperature\r\n");
                 }
                 else if(edit_mode==1 ){ // Enter high temp range editing mode
                     edit_mode = HIGH_EDIT;
                     printf("    System is programming High Temperature\r\n");
                 }
                 else if(edit_mode>1){ // Exits editing mode
                     edit_mode=0;
                     printf("    Low Temperature Setting = %.0f;  High Temperature Setting = %.0f\r\n",low_temp,high_temp);
                 }
                 else{
                     printf("    System in Running Mode\r\n");
                 }
             }
             break;
         case DOWN_PRESSED: // Down pressed
             if (edit_mode == HIGH_EDIT){
                 high_temp--; //Decrements high temp range
             }
             else if (edit_mode == LOW_EDIT){
                 low_temp--; //Decrements low temp range
             }
             break;
         case UP_PRESSED: //Up pressed
             if (edit_mode == HIGH_EDIT){
                 high_temp++; // Increments high temp range
             }
             else if (edit_mode == LOW_EDIT){
                 low_temp++; // Decrements low temp range
             }
             break;
     }
    BOUNCE_TIMER_FLAG_CLEAR;   //Clear Timer1 Interrupt flag
}

