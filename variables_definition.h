/**********************************************************************
* Indian Institute of Science Bengaluru
*
* FileName:       variables_definition.h
*
* This code can be used for academic purpose only. Industrial or any 
* commercial usage is prohibited.
*
* REVISION HISTORY:
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author            Date      Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Kaushik Basu 07/08/18  First release of source file
*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* ADDITIONAL NOTES:
*
*
**********************************************************************/


// MODBUS Communication variables
unsigned int T3_5= 45000; //Wait > 3.5 Character times ~ 4.5 msecs
unsigned int T1_5= 20000; //Wait > 1.5 Character times ~ 2 msecs

unsigned char ModBusState=0,QR_cycle_over=1, BufferCounter, DataCount, dataLength=7, discard_msg=0, dustbin, RcvDataCount, slave_addr=0x04, func_code=0x02;
unsigned char CRC_Check_OK, ModBusStart=0, offset=0, register_count=0;
unsigned char memory_buffer[20];

// Structures
typedef struct mbFRAMEs {  
        unsigned char address;
        unsigned char function;
        unsigned char databytes[20];
} volatile mbFRAME;
// For receive
volatile mbFRAME transmit_Frame;     //Frame to be transmitted 
volatile mbFRAME receive_Frame;      //Received Frame
volatile unsigned char TxCount=0;      //Number of bytes transmitted
volatile unsigned char RxCount=0;      //Number of bytes received
