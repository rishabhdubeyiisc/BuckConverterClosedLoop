#include <p30f4011.h>
#include "timer2.h"

void init_Timer2()
{ 
    T2CONbits.TON = 0; 
    TMR2 = 0;
    T2CONbits.TCS = 0;
    T2CONbits.TCKPS = 1;
    PR2 = 500 ;
    T2CONbits.TON = 1; 
}
void timer2_interrupt_set (unsigned int prty)
{
    IFS0bits.T2IF = 0;
    IPC1bits.T2IP = prty;
    IEC0bits.T2IE = 1;
}
