/*
  程序说明: CT117E嵌入式竞赛板GPIO模拟I2C总线驱动程序
  软件环境: Keil uVision 4.10 
  硬件环境: CT117E嵌入式竞赛板
  日    期: 2011-8-9
*/

#include <i2c.h>
/** I2C 总线接口 */
#define I2C_PORT GPIOB
#define SDA_Pin GPIO_Pin_7
#define SCL_Pin GPIO_Pin_6

#define FAILURE 0
#define SUCCESS 1

//配置SDA信号线为输入模式
void SDA_Input_Mode()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = SDA_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;

    GPIO_Init(I2C_PORT, &GPIO_InitStructure);
}

//配置SDA信号线为输出模式
void SDA_Output_Mode()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = SDA_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    GPIO_Init(I2C_PORT, &GPIO_InitStructure);
}

//
void SDA_Output(uint16_t val)
{
    if (val)
    {
        GPIO_SetBits(I2C_PORT, SDA_Pin);
    }
    else
    {
        GPIO_ResetBits(I2C_PORT, SDA_Pin);
    }
}

//
void SCL_Output(uint16_t val)
{
    if (val)
    {
        GPIO_SetBits(I2C_PORT, SCL_Pin);
    }
    else
    {
        GPIO_ResetBits(I2C_PORT, SCL_Pin);
    }
}

//
uint8_t SDA_Input()
{
    return GPIO_ReadInputDataBit(I2C_PORT, SDA_Pin);
}

//延时程序
void delay1(unsigned int n)
{
    unsigned int i;
    for (i = 0; i < n; ++i)
        ;
}

//I2C总线启动
void I2CStart(void)
{
    SDA_Output(1);
    delay1(500);
    SCL_Output(1);
    delay1(500);
    SDA_Output(0);
    delay1(500);
    SCL_Output(0);
    delay1(500);
}

//I2C总线停止
void I2CStop(void)
{
    SCL_Output(0);
    delay1(500);
    SDA_Output(0);
    delay1(500);
    SCL_Output(1);
    delay1(500);
    SDA_Output(1);
    delay1(500);
}

//等待应答
unsigned char I2CWaitAck(void)
{
    unsigned short cErrTime = 5;
    SDA_Input_Mode();
    delay1(500);
    SCL_Output(1);
    delay1(500);
    while (SDA_Input())
    {
        cErrTime--;
        delay1(500);
        if (0 == cErrTime)
        {
            SDA_Output_Mode();
            I2CStop();
            return FAILURE;
        }
    }
    SDA_Output_Mode();
    SCL_Output(0);
    delay1(500);
    return SUCCESS;
}

//发送应答位
void I2CSendAck(void)
{
    SDA_Output(0);
    delay1(500);
    delay1(500);
    SCL_Output(1);
    delay1(500);
    SCL_Output(0);
    delay1(500);
}

//
void I2CSendNotAck(void)
{
    SDA_Output(1);
    delay1(500);
    SCL_Output(1);
    delay1(500);
    SCL_Output(0);
    delay1(500);
}

//通过I2C总线发送一个字节数据
void I2CSendByte(unsigned char cSendByte)
{
    unsigned char i = 8;
    while (i--)
    {
        SCL_Output(0);
        delay1(500);
        SDA_Output(cSendByte & 0x80);
        delay1(500);
        cSendByte += cSendByte;
        delay1(500);
        SCL_Output(1);
        delay1(500);
    }
    SCL_Output(0);
    delay1(500);
}

//从I2C总线接收一个字节数据
unsigned char I2CReceiveByte(void)
{
    unsigned char i = 8;
    unsigned char cR_Byte = 0;
    SDA_Input_Mode();
    while (i--)
    {
        cR_Byte += cR_Byte;
        SCL_Output(0);
        delay1(500);
        delay1(500);
        SCL_Output(1);
        delay1(500);
        cR_Byte |= SDA_Input();
    }
    SCL_Output(0);
    delay1(500);
    SDA_Output_Mode();
    return cR_Byte;
}

//I2C总线初始化
void i2c_init()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = SDA_Pin | SCL_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // **

    GPIO_Init(I2C_PORT, &GPIO_InitStructure);
}

//my code
void i2c_sendByte(u8 addr, u8 dat)
{
    I2CStart();

    I2CSendByte(0xa0);

    I2CWaitAck();

    I2CSendByte(addr);

    I2CWaitAck();

    I2CSendByte(dat);

    I2CWaitAck();

    I2CStop();
}

u8 i2c_readByte(u8 addr)
{
    u8 dat;

    I2CStart();
    I2CSendByte(0xa0);
    I2CWaitAck();

    I2CSendByte(addr);
    I2CWaitAck();

    I2CStart();
    I2CSendByte(0xa1);
    I2CWaitAck();

    dat = I2CReceiveByte();

    I2CSendNotAck();
    I2CStop();

    return dat;
}

void u24_write_int(u8 addr, int dat)
{
    i2c_sendByte(addr, (u8)(dat & 0xff));
    Delay_Ms(2);
    i2c_sendByte(addr + 1, (u8)(dat >> 8 & 0xff));
    Delay_Ms(2);
    i2c_sendByte(addr + 2, (u8)(dat >> 16 & 0xff));
    Delay_Ms(2);
    i2c_sendByte(addr + 3, (u8)(dat >> 24 & 0xff));
    Delay_Ms(2);
}

int u24_read_int(u8 addr)
{
    int dat;
    dat = (int)i2c_readByte(addr);
    Delay_Ms(2);
    dat += (int)i2c_readByte(addr + 1) << 8;
    Delay_Ms(2);
    dat += (int)i2c_readByte(addr + 2) << 16;
    Delay_Ms(2);
    dat += (int)i2c_readByte(addr + 3) << 24;
    Delay_Ms(2);
    return dat;
}
