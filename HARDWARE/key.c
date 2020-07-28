#include <key.h>

//variable
u8 key_flag = 0;



/*以下这些不用管
//u8 key_fall_flag;
//u8 short_key_flag;
//u8 key_long_down;
//u8 key_fall_flag;
//u8 doubleClick;
//u8 keyUpFlag;
//u8 long_key_flag;
//u16 keyupCnt;
//u32 key_holdon_ms;

*/


//这个按键仅支持单次使用，蓝桥杯省赛应该单次够用了


//function

void key_init()
{

    EXTI_InitTypeDef EXTI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    //PA0
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);

    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    //PA8

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource8);

    EXTI_InitStructure.EXTI_Line = EXTI_Line8;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    //PB1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);

    EXTI_InitStructure.EXTI_Line = EXTI_Line1;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    //PB2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource2);

    EXTI_InitStructure.EXTI_Line = EXTI_Line2;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}



void key_scan()
{
	switch (key_flag)
	{
	case 1:
		Delay_Ms(10);
		if (Key1 == 0)
		{
			LCD_Clear(White);		//按键1要执行的操作放这里
		}
		break;
	case 2:
		Delay_Ms(10);
		if (Key2 == 0)
		{
			LCD_Clear(Blue);	   	//按键2要执行的操作放这里
		}
		break;
	case 3:
		Delay_Ms(10);
		if (Key3 == 0)
		{
			LCD_Clear(Red);		  	//按键3要执行的操作放这里
		}
		break;
	case 4:
		Delay_Ms(10);
		if (Key4 == 0)
		{
			LCD_Clear(Yellow);	  	//按键4要执行的操作放这里
		}
		break;
	default:;
		break;
	}
	key_flag = 0;
}

void EXTI0_IRQHandler(void)
{
    if (Key1 == 0)
    {
        key_flag = 1;
    }
    EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI9_5_IRQHandler(void)
{
    if (Key2 == 0)
    {
        key_flag = 2;
    }
    EXTI_ClearITPendingBit(EXTI_Line8);
}
void EXTI1_IRQHandler(void)
{
    if (Key3 == 0)
    {
        key_flag = 3;
    }
    EXTI_ClearITPendingBit(EXTI_Line1);
}
void EXTI2_IRQHandler(void)
{
    if (Key4 == 0)
    {
        key_flag = 4;
    }
    EXTI_ClearITPendingBit(EXTI_Line2);
}




/*以下代码是支持连续长按

//---------------按键c---------------



 #include "anjian.h"
_Bool Key_Flag=1;
void Key_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
}

u8 Key_Scan(void){
	if((Key1==0||Key2==0||Key3==0||Key4==0)&&Key_Flag){
		Delay_Ms(10);
		Key_Flag=0;
		if(Key1==0) return 1;
		else if(Key2==0) return 2;
		else if(Key3==0) return 3;
		else if(Key4==0) return 4;
	}
	else if(Key1==1&&Key2==1&&Key3==1&&Key4==1) Key_Flag=1;
	return 0;
}

//---------------按键h---------------

#ifndef __ANJIAN_H
#define __ANJIAN_H
extern _Bool Key_Flag;

#include "stm32f10x.h"

#define Key1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
#define Key2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)
#define Key3 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)
#define Key4 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)

void Key_Init(void);
u8 Key_Scan(u8 mode);

#endif


//---------------定时器c---------------

#include "timer.h"

void Timer2_Init(void){
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseStructure.TIM_Period = 999;
	TIM_TimeBaseStructure.TIM_Prescaler = 71;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
}
u32 Timer2_AnjianFlag=0;
void TIM2_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
  {
	if(Key2==0){
		Timer2_AnjianFlag++;
		if(Timer2_AnjianFlag>=800){
			Key_Flag=1;		//这个变量就是Key_Scan()里面的标志位
		}
	}
	else if(Key1==1&&Key2==1&&Key3==1&&Key4==1){
		Timer2_AnjianFlag=0;
	}
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);	
  }
}


//---------------定时器h---------------
#ifndef __TIMER_H
#define __TIMER_H


#include "stm32f10x.h"
#include "anjian.h"

void Timer2_Init(void);

#endif


*/
