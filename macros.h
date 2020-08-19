/**********************************************************************
* Indian Institute of Science Bengaluru
*
* FileName:        WriteToEEPROM.c
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

//Modbus slave operation state
#define INITIAL 0x10
#define MODBUSIDLE 0x11
#define RECEIVE_QUERY 0x12
#define PROBATION 0x15
#define CHECK_REQUEST 0x16
#define PROCESS_REPLY 0x17
#define TRANSMIT_REPLY 0x14
#define READ_REG 0x02
#define WRITE_REG 0x03

