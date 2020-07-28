#ifndef _key_h_
#define _key_h_

//headfile
#include <headfile.h>




//define
#define Key1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
#define Key2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)
#define Key3 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)
#define Key4 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)









//variable
extern u8 key_flag;






//function

extern void Delay_Ms(u32 nTime);





void key_init(void);
void key_scan(void);			 //按键扫描，建议按键自己写，因为按键变化较多









#endif




