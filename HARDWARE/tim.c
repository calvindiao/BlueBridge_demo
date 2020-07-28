#include <tim.h>


//headfile


//variable


//function

void tim4_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);

	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM4, ENABLE);
}


void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{

		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	
	}
}

//void TIM3_IRQHandler(void) //TIM3 
//{
//	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
//	{
//		if (key_fall_flag == 1) //发生按键按下
//		{
//			if (GPIO_ReadInputPin(GPIOB, GPIO_PIN_4) == 0) //按键持续按下
//			{
//				if (key_holdon_ms <= 2000)
//				{
//					key_holdon_ms++;
//				}
//				else //按键按下到2000触发长按标志
//				{
//					key_holdon_ms = 0;
//					short_key_flag = 0;		//清除短按标志
//					key_long_down = 1??		//长按标志
//					key_fall_flag = 0?? //清除按键按下标志
//				}
//			}
//			else //按键抬起
//			{
//				if (key_holdon_ms > 50) //按下时间大于50ms
//				{
//					key_holdon_ms = 0;
//					short_key_flag = 1;
//					key_long_down = 0;
//					key_fall_flag = 0;
//
//					//距离上次单击在100-500ms之间，发生连击事件
//					if (keyupCnt > 100 && keyupCnt < 500)
//					{
//						doubleClick = TRUE;
//						short_key_flag = 0;
//					}
//				
//					keyUpFlag = TRUE; //单击抬起，生成按键抬起标志
//				}
//				else //时间小于50ms，忽略
//				{
//					key_holdon_ms = 0;
//					short_key_flag = 0;
//					long_key_flag = 0;
//					key_fall_flag = 0;
//				}
//			}
//		}
//		if (keyUpFlag) //单击抬起后启动计数，计数到500ms
//			keyupCnt++;
//		if (keyupCnt > 500)
//		{
//			keyupCnt = 0;
//			keyUpFlag = FALSE;
//		}
//	}
//
//	TIM_ClearITPendingBit(TIM3, TIM_IT_Update); 
//}
//}
