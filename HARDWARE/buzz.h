#ifndef __BUZZ_H
#define __BUZZ_H
#include <headfile.h>

#define Beep_On()   GPIO_ResetBits(GPIOB,GPIO_Pin_4)	 //打开蜂鸣器
#define Beep_Off()  GPIO_SetBits(GPIOB,GPIO_Pin_4)		 //关闭蜂鸣器
//尽量不要实验蜂鸣器，会下载不了程序的
void Buzz_init(void);

#endif
