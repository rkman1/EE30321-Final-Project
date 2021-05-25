/*
 * File: ui.h
 * Author : rls
 * Modified: Ray Kman
 *  FINAL
 * Created on March 20, 2020, 9:12 PM
 */

#ifndef UI_H
#define	UI_H


#include <xc.h>

#define INITIALIZING 1
#define RUNNING 1
#define NONE 0

#define UI_TIMER_ON T3CONbits.TON = 1
#define UI_TIMER_OFF T3CONbits.TON = 0
#define UI_TIMER_RESET TMR3 = 0
#define UI_TIMER_PERIOD PR3
#define UI_TIMER_CONFIG T3CONbits.TCS = 0; T3CONbits.TGATE = 0; T3CONbits.TCKPS = 0b00;
#define UI_TIMER_INTERRUPT_CONFIG IPC2bits.T3IP = 1; IFS0bits.T3IF = 0; IEC0bits.T3IE = 1;
#define UI_TIMER_FLAG_CLEAR IFS0bits.T3IF = 0

#define UI_TIMER_CYCLE_TIME 64000 // needs to be < 65K

void ui();
void configure_ui();

#endif	/* UI_H */

