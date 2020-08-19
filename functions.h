/**********************************************************************
* Indian Institute of Science Bengaluru
*
* FileName:        functions.h
*
* This code can be used for academic purpose only. Industrial or any 
* commercial usage is prohibited.
*
* REVISION HISTORY:
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author            Date      Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Kaushik Basu 06/08/18  First release of source file
*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* ADDITIONAL NOTES:
*
*
**********************************************************************/


/* Interrupts */
void __attribute__((__interrupt__,__auto_psv__)) _T3Interrupt(void);
void __attribute__((__interrupt__,__auto_psv__)) _T4Interrupt(void);
void __attribute__((__interrupt__,__auto_psv__)) _U2RXInterrupt(void);
void __attribute__((__interrupt__,__auto_psv__)) _U2TXInterrupt(void);


/* MODBUS Communication Functions */
void TIMER3_INIT(void);
void TIMER4_INIT(void);
void UART2_INIT(void);
void GEN_NORMAL_REPLY(void);
void GEN_ERROR_REPLY(void);
void SEND_REPLY(void);
void clearBuffer(mbFRAME *buff_ptr);
