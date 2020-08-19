#include <p30f4011.h>
#include "gpio.h"
#include "my_function.h"

void init_Gpio()
{
    PRE_CHARGE_CONTACTOR_TRIS   =0; 
    DIRECT_CONTACT_TRIS         =0;
    CONTACT_BREAKER_TRIS        =0;
    DISCHARGE_CAP_GATE_TRIS     =0;
    
    PRE_CHARGE_CONTACTOR_LAT    =0;
    DIRECT_CONTACT_LAT          =0;
    CONTACT_BREAKER_LAT         =0;
    DISCHARGE_CAP_GATE_LAT      =0;
}
