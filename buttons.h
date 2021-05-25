/* 
 * File: buttons.h  
 * Author: rls
 * Modified: Ray Kman
 * Comments: FINAL
 * Revision history: 
 */

#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define SW_UP PORTAbits.RA2
#define SW_UP_PIN TRISAbits.TRISA2
#define SW_DOWN PORTBbits.RB4
#define SW_DOWN_PIN TRISBbits.TRISB4

#define BOUNCE_TIMER_ON T1CONbits.TON = 1
#define BOUNCE_TIMER_OFF T1CONbits.TON = 0
#define BOUNCE_TIMER_RESET TMR1 = 0
#define BOUNCE_TIMER_PERIOD PR1
#define BOUNCE_TIMER_CONFIG T1CONbits.TCS = 0; T1CONbits.TGATE = 0; T1CONbits.TCKPS = 0b00;
#define BOUNCE_TIMER_INTERRUPT_CONFIG IPC0bits.T1IP = 4; IFS0bits.T1IF = 0; IEC0bits.T1IE = 1; //Try putting lower than CN priority? Changed from 4 to 3
#define BOUNCE_TIMER_FLAG_CLEAR IFS0bits.T1IF = 0

#define BOUNCE_TIMER_CYCLE_TIME 60000 // needs to be < 65K

//18425

#define CN_UP_PIN CNENAbits.CNIEA2
#define CN_UP_PULL CNPUAbits.CNPUA2
#define CN_DOWN_PIN CNENBbits.CNIEB4
#define CN_DOWN_PULL CNPUBbits.CNPUB4
#define CN_FLAG IFS1bits.CNIF
#define CN_STATUS IEC1bits.CNIE
#define CN_INTERRUPT_CONFIG IFS1bits.CNIF = 0; IPC4bits.CNIP = 3; IEC1bits.CNIE = 1;


/* Button States */
#define PRESSED 0
#define RELEASED 1
#define BOTH_PRESSED 3
#define UP_PRESSED 1
#define DOWN_PRESSED 2
#define NONE_PRESSED 0

/* Internal Pull Up */
#define OFF 0
#define ON 1

/* Pin States */
#define OUT 0
#define IN 1

/* Edit Mode */
#define HIGH_EDIT 2
#define LOW_EDIT 1

void configure_buttons();
int check_buttons();

#endif	/* BUTTONS_H */
