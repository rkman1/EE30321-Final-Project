/*
 * File:   lcd.c
 * Author: raykman
 * FINAL
 * 
 */

#include "xc.h"
#include "lcd.h"
#include <stdio.h>
#include <string.h>
#include "fonts.h"



void LCDWrite(LCDBYTE dc, LCDBYTE data) {
    LCD_SCE = LOW;    // Selection LCD panel
    LCD_DC = dc;      // Indicate Data/Command signal
    SPI1BUF = data;   // Put data in output buffer for SPI1
    while(!SPI1STATbits.SPIRBF){} // wait for it to send
    Nop();            // A little extra wait time
    LCD_SCE = HIGH;   // Deselect LCD panel
       
}

void LCDCharacter(char character)
{
    int index;
    LCDWrite(LCD_DATA, 0x00);
    for (index = 0; index < 5; index++) {
        LCDWrite(LCD_DATA, ASCII[character - 0x20][index]);
    }
    LCDWrite(LCD_DATA, 0x00);
}

void LCDSnow(){
    int i;
    int j;
    LCDWrite(LCD_COMMAND,0x80 | 70); // Move cursor to bottom right
    LCDWrite(LCD_COMMAND,0x44);
   
    for (i = 0; i < 14; i++) { //Top half of image
        LCDWrite(LCD_DATA, SNOW[0][i]);
    }
    LCDWrite(LCD_COMMAND,0x80 | 70 );
    LCDWrite(LCD_COMMAND,0x45);
    for (i = 0; i < 15; i++) { // Bottom half of image
         LCDWrite(LCD_DATA, SNOW[1][i]);
    }
}

void LCDFlame(){
    int i;
    int j;
    LCDWrite(LCD_COMMAND,0x80 | 70); // Move cursor to bottom right
    LCDWrite(LCD_COMMAND,0x44);
   
    for (i = 0; i < 15; i++) { // Top half of image
        LCDWrite(LCD_DATA, FLAME[0][i]);
    }
    LCDWrite(LCD_COMMAND,0x80 | 70 );
    LCDWrite(LCD_COMMAND,0x45);
    for (i = 0; i < 15; i++) { // Bottom half of image
         LCDWrite(LCD_DATA, FLAME[1][i]);
    }
    
}

void LCDBignum(char *character){
    int pos = 25; // Control x axis position on LCD. 0 to 83 in decimal.
    int i;
    int j;
    for (i=0;i<2;i++){
        LCDWrite(LCD_DATA, 0x00);
        LCDWrite(LCD_COMMAND,0x80 | pos ); 
        LCDWrite(LCD_COMMAND,0x41);
        for(j=0;j<14;j++){
            LCDWrite(LCD_DATA, BIGNUM[character[i] - 0x30][0][j]); // Top third
          }
        LCDWrite(LCD_COMMAND,0x80 | pos );
        LCDWrite(LCD_COMMAND,0x42);
        for(j=0;j<14;j++){
            LCDWrite(LCD_DATA, BIGNUM[character[i] - 0x30][1][j]); // Middle third
          }
        LCDWrite(LCD_COMMAND,0x80 | pos );
        LCDWrite(LCD_COMMAND,0x43);
        for(j=0;j<14;j++){
            LCDWrite(LCD_DATA, BIGNUM[character[i] - 0x30][2][j]); // Bottom third
          }
        pos = pos + 16; // Shifting cursor to write one's place
    }
    LCDWrite(LCD_DATA, 0x00);
   
}
void LCDclr(void){
    int i;
    for (i=0;i<6*84;i++){
        LCDWrite(LCD_DATA,0x00);
    }
    LCDWrite(LCD_COMMAND,0x40);
    LCDWrite(LCD_COMMAND,0x80);
}

void configure_lcd(){
    LCD_SCE_PIN = OUT;
    LCD_RESET_PIN = OUT;
    LCD_DC_PIN = OUT;

    SPI1CON1bits.MSTEN = 1;    // make master
    SPI1CON1bits.PPRE = 0b11;  // 1:1 primary prescale
    SPI1CON1bits.SPRE = 0b111; // 1:1 secondary prescale
    SPI1CON1bits.MODE16 = 0;   // 8-bit transfer mode
    SPI1CON1bits.SMP = 0;      // sample in middle
    SPI1CON1bits.CKE = 1;      // Output on falling edge
    SPI1CON1bits.CKP = 0;      // CLK idle state low
    SPI1STATbits.SPIEN = 1;    // enable SPI1
    
    LCD_RESET = LOW;
    LCD_RESET = HIGH;
        
    LCDWrite(LCD_COMMAND, 0x21);  // LCD Extended Commands.
    LCDWrite(LCD_COMMAND, 0xCA );  // Set LCD Vop (Contrast). 
    LCDWrite(LCD_COMMAND, 0x04 );  // Set Temp coefficent. //0x04
    LCDWrite(LCD_COMMAND, 0x13 );  // LCD bias mode 1:48. //0x13
    LCDWrite(LCD_COMMAND, 0x20 );  // LCD Basic Commands
    LCDWrite(LCD_COMMAND, 0x0C );  // LCD in normal mode.
}

void LCD_string(char *arr){ 
    int i;
    for (i=0;i<strlen(arr);i++){ // Iterate through each character stored in the array
        LCDCharacter(arr[i]); 
    } 
}