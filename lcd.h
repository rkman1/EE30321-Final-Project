/*
 * File: lcd.h
 * Author : rls
 * Modified: Ray Kman
 *  FINAL
 * Created on March 20, 2020, 9:12 PM
 
 */

#ifndef LCD_H
#define	LCD_H

#include "xc.h"

typedef unsigned char LCDBYTE;

// Pins for LCD Control Signals
#define LCD_SCE LATBbits.LATB12
#define LCD_SCE_PIN TRISBbits.TRISB12
#define LCD_RESET LATBbits.LATB13
#define LCD_RESET_PIN TRISBbits.TRISB13
#define LCD_DC LATBbits.LATB14
#define LCD_DC_PIN TRISBbits.TRISB14

// Pins for SPIx 
#define USESPI1 // define to USESPI1/USESPI2 depending on what set you are using

        
#define IN 1
#define OUT 0

#define LOW 0
#define HIGH 1

#define LCD_COMMAND     LOW
#define LCD_DATA     HIGH

void LCDWrite(LCDBYTE, LCDBYTE);
void LCDCharacter(char);
void LCDclr(void);
void configure_lcd();
void LCD_string(char *arr);
void LCDSnow();
void LCDFlame();
void LCDBignum(char *character);
#endif	/* UI_H */

