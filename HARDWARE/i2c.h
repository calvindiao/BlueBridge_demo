#ifndef  __I2C_H__
#define  __I2C_H__


//headfile
#include <headfile.h>



//variable



//function


void i2c_init(void);
void delay1(unsigned int n);

void I2CStart(void);
void I2CStop(void);
void I2CSendAck(void);
void I2CSendNotAck(void);
unsigned char I2CWaitAck(void);

void I2CSendByte(unsigned char cSendByte);
unsigned char I2CReceiveByte(void);



extern void Delay_Ms(u32 nTime);



//my code


u8 i2c_readByte(u8 addr);							//读入1个字节的数据
void i2c_sendByte(u8 addr, u8 dat);					//读出1个字节的数据

void u24_write_int(u8 addr, int dat);			   	//读入4个字节的数据
int u24_read_int(u8 addr);							//读出4个字节的数据

#endif
