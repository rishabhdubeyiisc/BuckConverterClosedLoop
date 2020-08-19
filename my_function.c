#include <p30f4011.h>
#include "global_variables.h"
#include "my_function.h"

char state;
int Vdc_satisfy;

unsigned int timer2_start_state_start ,timer2_start_state_end , timer2_start_state_log;
unsigned int timer2_period ;

volatile unsigned int faultbits;
unsigned int PWM_ramp_yes;
unsigned int pdc_open_loop_calculated ;
unsigned int ready_to_run ;
unsigned int stop_command;
unsigned int stop_logger;
unsigned int timer2_STOP_STATE_start , timer2_STOP_STATE_end,timer2_STOP_STATE_logger ;
unsigned int timer2_counter;

char protection_state;
int il_array[8],Vcap_array[8];
unsigned int logged_time_in_start_state ;
unsigned int logged_time_in_STOP_STATE;

void array_filler()
{   
    switch (ADC_count)
    {
        case 0 :
            il_array[0]=iL;
            Vcap_array[0]=Vcap;
            break ;
        case 1 :
            il_array[1]=iL;
            Vcap_array[1]=Vcap;
            break ;      
        case 2 :
            il_array[2]=iL;
            Vcap_array[2]=Vcap;
            break ;       
        case 3 :
            il_array[3]=iL;
            Vcap_array[3]=Vcap;
            break ;       
        case 4 :
            il_array[4]=iL;
            Vcap_array[4]=Vcap;
            break ;       
        case 5 :
            il_array[5]=iL;
            Vcap_array[5]=Vcap;
            break ;       
        case 6 :
            il_array[6]=iL;
            Vcap_array[6]=Vcap;
            break ;
        case 7 :
            il_array[7]=iL;
            Vcap_array[7]=Vcap;
            break ;
    }
    
}

void clear_watchdog()
{
    ClrWdt(); 
}

void read_from_EEPROM()
{

}

void idle ()
{
    CONTACT_BREAKER_LAT = 1;
    read_from_EEPROM();
    if ( (Vdc >= VdcL) && (Vdc<=VdcH) )
    {
        state = 'r';
    }
}
void ready()
{
    if ( (VdcL <= Vdc)  && (Vdc <= VdcH) )
    {
        Vdc_satisfy = 1;
    }
    else 
    {
        Vdc_satisfy = 0;
        state = 'i';
    }
    if (Vdc_satisfy == 1 && StartCommand == 1 )
    {
        state = 's';
    }
    else if (Vdc_satisfy == 1 && StartCommand == 0 )
    {
        state = 'r';
    }
    else 
    {
        state = 'i';
    }
}
void start ()
{   
    
    PRE_CHARGE_CONTACTOR_LAT = 1;
    unsigned int difference;
    difference = timer2_start_state_end +( (~timer2_start_state_start) + 0x0001 )  ; // counts  
    timer2_start_state_log += difference;//in counts only 1 count takes 50 us
    logged_time_in_start_state = ( ( timer2_start_state_log ) * (timer2_period<<10) ) >> 8;
    float five_rc_t_DC_bus;
    five_rc_t_DC_bus = FIVE_RC_TOU_DC_BUS;
    float templog;
    templog = (float)(logged_time_in_start_state>>3);
    if (logged_time_in_start_state > five_rc_t_DC_bus ) // checking bus voltage
    {
        if ( VdcL <= Vdc && Vdc <= VdcH) 
        {
            DIRECT_CONTACT_LAT = 1;
            //wait here for 10 us 
            Delay10uS();
            if (VdcL < Vcap < VdcH)
            {
                CONTACT_BREAKER_LAT = 1 ;
                PWM_ramp_yes = 1 ;
            }
            else 
            {
                faultbits = DIRECT_CONTACT_FAULT;
                state = 'f';
            }
        }
        else 
        {
            faultbits = PRE_CHARGE_FAULT;
            state = 'f';
        }
    }
    
}
void pwm_ramper()
{
    PDC1+= (PTPER>>8);
}
void pwm_control()
{
    if (PWM_ramp_yes == 1 )
    {   
        if (  (PDC1)  >= pdc_open_loop_calculated)
        {
            ready_to_run = 1;
        }
        else 
        {

            pwm_ramper();
            ready_to_run = 0;
        }
    }
    if (ready_to_run == 1 )
    {
        state = 'u';
    }
}
void stop_switch()
{
    running_status = 1 ;
    if (StartCommand == 0 )
    {
        state = 't';
    }
}

void stop()
{   
    unsigned int pdc_null_hit ;
    pwm_decliner(); // reduced pdc gradually
    pdc_null_hit = pdc_force_null(); // operates for pdc less than 10 
    //pdc forced null 
    if (pdc_null_hit == 1 && stop_logger ==0)
    {
        DIRECT_CONTACT_LAT = 0;
        Delay10uS();
        DISCHARGE_CAP_GATE_LAT = 1;
        stop_logger = 1;
    }
    if (stop_logger == 1)
    {   
        unsigned int difference ;
        difference= timer2_STOP_STATE_end - timer2_STOP_STATE_start;
        timer2_STOP_STATE_logger += difference ;
        
        logged_time_in_STOP_STATE = ( ( timer2_STOP_STATE_logger ) * timer2_period ) >> 3;
        float dc_bus_tou = DC_BUS_DISCHARGE_TIME;
        if (((float)logged_time_in_STOP_STATE) > dc_bus_tou )
        {   
            float Discharged_cap_volatge;
            Discharged_cap_volatge=DISCHARGE_CAP_VOLT ;
            
            if (Vcap < Discharged_cap_volatge)
            {
                state = 'i';
            }
            else
            {
                faultbits = DC_BUS_DISCHARGE_FAIL;
                state = 'f';
            }
        }
    }
    
}
void pwm_decliner()
{
    if (PDC1 != 0) 
    {
        PDC1 -= (PTPER>>8);
    }
}
unsigned int pdc_force_null ()
{
    if (PDC1 < 10)
    {
        PDC1 = 0;
        return 1;
    }    
    else 
    {
        return 0;
    }
}

void process_control ()
{
    switch (state)
    {
        case 'i': //IDLE close breaker EEPROM read
            idle ();
            break;
                
        case 'r' : //READY >> Wait for Vdc stable if yes wait for GUI startcommand if yes change state to s else r else i 
            ready();
            break;
        
        case 's' : //START 
             //16b reg
            if (PWM_ramp_yes == 0)
            {
                start();
            }
            pwm_control();
            
            break;
        
        case 'u' : //RUN
            stop_switch();
            break;
            
        case 't' : //STOP
            timer2_STOP_STATE_start = TMR2; 
            stop();
            timer2_STOP_STATE_end = TMR2;
            break;
        
        case 'f' : //FAULT
            
            break;        
    }
}
void Delay1uS() 
{  // Assuming 10MIPs.
	Nop(); Nop(); Nop(); Nop();	Nop(); 
    Nop(); Nop(); Nop(); Nop(); Nop(); 
}
void Delay10uS() 
{  // Assuming 10MIPs.
	Nop(); Nop(); Nop(); Nop();	Nop(); 
    Nop(); Nop(); Nop(); Nop(); Nop(); 
    
    Nop(); Nop(); Nop(); Nop();	Nop(); 
    Nop(); Nop(); Nop(); Nop(); Nop(); 
    
    Nop(); Nop(); Nop(); Nop();	Nop(); 
    Nop(); Nop(); Nop(); Nop(); Nop(); 
    
    Nop(); Nop(); Nop(); Nop();	Nop(); 
    Nop(); Nop(); Nop(); Nop(); Nop(); 
    
    Nop(); Nop(); Nop(); Nop();	Nop(); 
    Nop(); Nop(); Nop(); Nop(); Nop(); 
    
    Nop(); Nop(); Nop(); Nop();	Nop(); 
    Nop(); Nop(); Nop(); Nop(); Nop(); 
    
    Nop(); Nop(); Nop(); Nop();	Nop(); 
    Nop(); Nop(); Nop(); Nop(); Nop(); 
    
    Nop(); Nop(); Nop(); Nop();	Nop(); 
    Nop(); Nop(); Nop(); Nop(); Nop(); 
    	
    Nop(); Nop(); Nop(); Nop();	Nop(); 
    Nop(); Nop(); Nop(); Nop(); Nop(); 
    	
    Nop(); Nop(); Nop(); Nop();	Nop(); 
    Nop(); Nop(); Nop(); Nop(); Nop(); 
    
}
