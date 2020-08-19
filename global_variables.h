#include<p30f4011.h>

extern int VdcL, VdcH, iLL, iLH, Dutyref, Vref;
extern int Vdc, Vout, iL, Duty, Vcap;
extern int A0, A1, A2, A3; 
extern int count1, count2, count3, count4;
extern int Protection_State, State, Reset, StartCommand, ControlCommand, fault, ControlType, ContactorStatus, FaultType;

/*
Count 3 - Protection Wait
Count 4 - Process Control Wait for precharging
*/
