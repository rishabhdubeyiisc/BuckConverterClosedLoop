/**********************************************************************
* Indian Institute of Science Bengaluru
*
* FileName:       variables.h
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


//All Variables // MODBUS Communication variables
extern unsigned int T3_5; //Wait > 3.5 Character times ~ 4.5 msecs
extern unsigned int T1_5; //Wait > 1.5 Character times ~ 2 msecs

extern unsigned char ModBusState,QR_cycle_over, BufferCounter, DataCount, dataLength, discard_msg, dustbin, RcvDataCount, slave_addr, func_code;
extern unsigned char CRC_Check_OK, ModBusStart, offset, register_count;
extern unsigned char memory_buffer[20];

// Structures
typedef struct mbFRAMEs {  
        unsigned char address;
        unsigned char function;
        unsigned char databytes[20];
} volatile mbFRAME;

// For receive
extern volatile mbFRAME transmit_Frame;     //Frame to be transmitted 
extern volatile mbFRAME receive_Frame;      //Received Frame
extern volatile unsigned char TxCount;      //Number of bytes transmitted
extern volatile unsigned char RxCount;      //Number of bytes received
