#ifndef FUNCTION_H
#define	FUNCTION_H

#define PRE_CHARGE_CONTACTOR_TRIS        _TRISB1 
#define DIRECT_CONTACT_TRIS              _TRISB2
#define CONTACT_BREAKER_TRIS             _TRISB6
#define DISCHARGE_CAP_GATE_TRIS          _TRISB7

#define PRE_CHARGE_CONTACTOR_LAT         _LATB1 
#define DIRECT_CONTACT_LAT               _LATB2
#define CONTACT_BREAKER_LAT              _LATB6
#define DISCHARGE_CAP_GATE_LAT           _LATB7
    
#define FIVE_RC_TOU_DC_BUS 0.001
#define DC_BUS_DISCHARGE_TIME 0.01
#define DISCHARGE_CAP_VOLT 0.001

#define PRE_CHARGE_FAULT (1u << 0)
#define DIRECT_CONTACT_FAULT (1u << 1)
#define DC_BUS_DISCHARGE_FAIL (1u << 2)

// MY variable for global 
extern unsigned int ADC_count ;
extern char state;
extern int Vdc_satisfy;

extern unsigned int timer2_start_state_start ,timer2_start_state_end , timer2_start_state_log;
extern unsigned int timer2_period ;

extern volatile unsigned int faultbits;
extern unsigned int PWM_ramp_yes;
extern unsigned int pdc_open_loop_calculated ;
extern unsigned int ready_to_run ;
extern unsigned int stop_command;
extern unsigned int stop_logger;
extern unsigned int timer2_STOP_STATE_start , timer2_STOP_STATE_end,timer2_STOP_STATE_logger ;
extern unsigned int timer2_counter;

extern char protection_state;
extern int il_array[8],Vcap_array[8];
extern unsigned int logged_time_in_start_state ;
extern unsigned int logged_time_in_STOP_STATE;
extern unsigned int running_status ;
//MY FUNCTIONS

void Delay1uS();
void Delay10uS();
void clear_watchdog();
void read_from_EEPROM();
void idle ();
void ready();
void start ();
void pwm_ramper();
void pwm_control();
void stop_switch();
void stop();
void pwm_decliner();
unsigned int pdc_force_null ();
void process_control ();
void array_filler();

#endif	/* FUNCTION_H */

