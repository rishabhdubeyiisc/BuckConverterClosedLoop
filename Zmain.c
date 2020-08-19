#include <p30f4011.h>

_FOSC(CSW_FSCM_OFF & XT_PLL4);
_FWDT(WDT_OFF);
_FBORPOR(PBOR_OFF & MCLR_EN);
_FGS(CODE_PROT_OFF);

#include "variables_definition.h"
#include "global_variables.h"
#include "macros.h"

#include "adc.h"
#include "gpio.h"
#include "my_function.h"
#include "pwm.h"
#include "timer2.h"

int VdcL, VdcH, iLL, iLH, Dutyref, Vref;
int Vdc, Vout, iL, Duty, Vcap;
int Protection_State, State, Reset, StartCommand, ControlCommand, fault, ControlType, ContactorStatus, FaultType;

unsigned int ADC_count ;
long unsigned int main_logger ;
unsigned int running_status ;

int main ()
{   
    VdcL = 0;
    Vdc = 10 ;
    Vcap = 10 ;
    VdcH = 1000;
    Dutyref= 1;
    state = 'i';
    StartCommand = 1;

    ADC_count = 0;
    timer2_counter = 0;
    init_Gpio();
    //**************SIR 
    TIMER3_INIT();
    TIMER4_INIT();
    UART2_INIT();
    //**************
    init_PWM();
    init_Timer2();
    init_ADC(); 
    timer2_period = 4;
    //priority functions
    adc_interrupt_set (5);
    timer2_interrupt_set (6);
    main_logger = 0 ;
    while (1)
    {   
        main_logger++;
        if (running_status == 1)
        {
            running_status = 2;
        }
        if(main_logger > 0x000FFFFF)
        {
            StartCommand = 0;
        }
        clear_watchdog();
    };
    return (7);
}
void __attribute__((__interrupt__,__auto_psv__)) _ADCInterrupt( void )
{   
    //clear flag first
    IFS0bits.ADIF=0;
    /*create a counter for ADC interrupt of how many times it comes */
    ADC_count++;

    //routine variables declare if needed globals can be used
    
    // read ADC Buffers
    /*compute the variables want*/
    
    Vdc = ADCBUF0; // AN0 = CH0;
	Vout  = ADCBUF1;// AN3 = CH1; 
	iL  = ADCBUF2;// AN4 = CH2;
	Vcap = ADCBUF3;// AN5 = CH3
    
    Vdc = 10;
    iL= 5;
    Vout=25;
    Vcap=10;
    //ARRAY_FILLER
    array_filler(); 
    //start a timer and store in a variable this timer will start when ADC interrupt begins
    
    //start_timer_value_ADC=TMR4;
    
    //Clear ADC flag
    

    
    /*time taken by interrupt will be 
    TMR4 - start_timer_value_ADC 
     */
    if (ADC_count == 7)
    {
        ADC_count = 0;
    }
}

void __attribute__((__interrupt__,__auto_psv__)) _T2Interrupt( void )
{   
    
    //clear flag first
    IFS0bits.T2IF=0; //clear flag
    timer2_start_state_start = TMR2 ;
    timer2_counter++;
    //protection loop
    //compute average of Vcap il
        
    //count log for process control
    if ( ( timer2_counter % 8 ) == 0 )
    {   
        pdc_open_loop_calculated = (Dutyref * PTPER);
        process_control ();
        timer2_counter = 0;
    }
    timer2_start_state_end = TMR2;
}
