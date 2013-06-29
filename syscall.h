#ifndef _SERIAL
#define _SERIAL

int Serial_ReadByte(unsigned char *dest);
int Serial_ReadBytes(unsigned char *dest, int max, short *size);
int Serial_WriteByte(unsigned char byte);
int Serial_WriteBytes(unsigned char *src, int size);
int Serial_WriteByteFIFO(unsigned char byte);
int Serial_GetRxBufferSize(void);
int Serial_GetTxBufferFreeCapacity(void);
int Serial_ClearReceiveBuffer(void);
int Serial_ClearTransmitBuffer(void);
int Serial_Open(unsigned char *conf);
int Serial_Close(int mode);
int Serial_Peek(int index, unsigned char *dest);
int Serial_IsOpen(void);
void RebootOS();
int memcopy();
char* VRam_Base();

int RTC_GetTicks();

#endif

