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
//		if (key_fall_flag == 1) //������������
//		{
//			if (GPIO_ReadInputPin(GPIOB, GPIO_PIN_4) == 0) //������������
//			{
//				if (key_holdon_ms <= 2000)
//				{
//					key_holdon_ms++;
//				}
//				else //�������µ�2000����������־
//				{
//					key_holdon_ms = 0;
//					short_key_flag = 0;		//����̰���־
//					key_long_down = 1??		//������־
//					key_fall_flag = 0?? //����������±�־
//				}
//			}
//			else //����̧��
//			{
//				if (key_holdon_ms > 50) //����ʱ�����50ms
//				{
//					key_holdon_ms = 0;
//					short_key_flag = 1;
//					key_long_down = 0;
//					key_fall_flag = 0;
//
//					//�����ϴε�����100-500ms֮�䣬���������¼�
//					if (keyupCnt > 100 && keyupCnt < 500)
//					{
//						doubleClick = TRUE;
//						short_key_flag = 0;
//					}
//				
//					keyUpFlag = TRUE; //����̧�����ɰ���̧���־
//				}
//				else //ʱ��С��50ms������
//				{
//					key_holdon_ms = 0;
//					short_key_flag = 0;
//					long_key_flag = 0;
//					key_fall_flag = 0;
//				}
//			}
//		}
//		if (keyUpFlag) //����̧�������������������500ms
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
