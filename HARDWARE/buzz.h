#ifndef __BUZZ_H
#define __BUZZ_H
#include <headfile.h>

#define Beep_On()   GPIO_ResetBits(GPIOB,GPIO_Pin_4)	 //�򿪷�����
#define Beep_Off()  GPIO_SetBits(GPIOB,GPIO_Pin_4)		 //�رշ�����
//������Ҫʵ��������������ز��˳����
void Buzz_init(void);

#endif
