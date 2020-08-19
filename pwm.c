#include <p30f4011.h>
#include "pwm.h"

void init_PWM()
{
    // PWM Initialization

	PTPER = 500;	// 29,491,200/((PTPER + 1)*2) = 9997Hz. 
    PTCONbits.PTCKPS=0;
    PWMCON1bits.PMOD1=0;
    
    _DTAPS = 0;
    _DTA = 5;

	PWMCON1bits.PEN1H = 1; // enabled. Enables pwm1h.  That's not the correct procedure captain!  Put your hand on the key sir!  I'm sorry... I'm so sorry.. Put your hand on the key sir!  -War Games.
	PWMCON1bits.PEN1L = 1; // enabled. Enables pwmll.
	
    PTMR = 0;
    PDC1=0;
    PTCONbits.PTEN=1;
}
