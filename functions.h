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
