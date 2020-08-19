#include <p30f4011.h>
#include "adc.h"

void init_ADC()
{
    ADCON1bits.ADON = 0; // Page. 416 in F.R.M.  Under "Enabling the Module".  Turn it off for a moment.

	// ============= ADC - Measure 
    ADCHSbits.CH123NA=0;    //negative reference voltage
    ADCHSbits.CH123SA=1;    // AN3 = CH1 = volt;// AN4 = CH2 = volt;// AN5 = CH3 = volt;
    ADCHSbits.CH0NA=0;      //negative reference voltage
    ADCHSbits.CH0SA =0;     // AN0 = CH0 = current;
	
    //ADCON1 register
    ADCON1 = 0;  // Starts this way anyway.  But just to be sure.   
    
    ADCON1bits.FORM = 0;      // unsigned integer in the range 0-1023
    ADCON1bits.SSRC = 0b011;  // Motor Control PWM interval ends sampling and starts conversion
    ADCON1bits.SIMSAM = 1;  // Simultaneous Sample Select bit (only applicable when CHPS = 01 or 1x)// Samples CH0, CH1, CH2, CH3 simultaneously (when CHPS = 1x)// Samples CH0 and CH1 simultaneously (when CHPS = 01)
    ADCON1bits.ASAM = 1;   // Sampling begins immediately after last conversion completes. // SAMP bit is auto set.
    
    //ADCON2 register
	ADCON2 = 0; // Page. 407 in F.R.M.// Page. 407 in F.R.M.
    
    ADCON2bits.CHPS=2;  // Samples CH0, CH1, CH2, CH3 simultaneously when CHPS = 1x
    ADCON2bits.VCFG=0;  // VCFG = 000; This selects the A/D High voltage as AVdd, and A/D Low voltage as AVss.
    ADCON2bits.CSCNA=0; //no scan mode 
    ADCON2bits.SMPI=0;  // SMPI = 0000; This makes an interrupt happen every time the A/D conversion process is done (for all 4 I guess, since they happen at the same time.)
	ADCON2bits.ALTS=0;	// ALTS = 0; Always use MUX A input multiplexer settings
	ADCON2bits.BUFM=0;	// BUFM = 0; Buffer configured as one 16-word buffer ADCBUF(15...0)

    //ADCON3 register
    ADCON3 = 0; // Page. 408 in F.R.M.// Page. 408 in F.R.M.
    
    ADCON3bits.ADRC=0;//system clock set
    ADCON3bits.ADCS =7;//Tcy = inv(40 Mhz)= 25 ns => ADC conversion time 100  ns = Tad
    //ADCON3bits.SAMC=ERROR SET THIS;//sampling time = SAMC*Tad = SAMC * 100 ns

    //ADPCFG
    ADPCFGbits.PCFG0=0;
    ADPCFGbits.PCFG3=0;
    ADPCFGbits.PCFG4=0;
    ADPCFGbits.PCFG5=0;
    
    // Turn on A/D module
    ADCON1bits.ADON = 1; // Pg. 416 in F.R.M.  Under "Enabling the Module"
						 // ** It's important to set all the bits above before turning on the A/D module. **
						 // Now the A/D conversions start happening once ADON == 1.
	
}

void adc_interrupt_set (unsigned prty)
{   
    IFS0bits.ADIF=0;
    _ADIP = prty;			 // A/D interrupt priority set to 4.  Default is 4.
	IEC0bits.ADIE = 1;	 // Enable interrupts to happen when a A/D conversion is complete. Pg. 148 of F.R.M.  	
}
