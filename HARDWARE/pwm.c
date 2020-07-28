#include <pwm.h>



/*

以下对应的1、2、6、7对应PA1\PA2\PA6\PA7


以PA1为例，PA1输出的是2kHZ，20%占空比的PWM波


CCR1_Val为计数值，如果输出2khzPWM，1/2000=500us，所以输入的CCR1_Val为500

duty_ratio1为占空比


*/


//variable
__IO uint16_t CCR1_Val = 500;
__IO uint16_t CCR2_Val = 1000;
__IO uint16_t CCR6_Val = 65535;
__IO uint16_t CCR7_Val = 2000;

float duty_ratio1 = 0.2;
float duty_ratio2 = 0.3;
float duty_ratio6 = 0;
float duty_ratio7 = 0.5;

u8 pa1_state = 0, pa2_state = 0;
u8 pa6_state = 0, pa7_state = 0;
__IO uint16_t IC1Value,IC2Value,IC3Value;
u32 Frequency_1,Frequency_2;
//function

void pwm_tim2_init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Enable the TIM3 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_TimeBaseStructure.TIM_Period = 65535;
	TIM_TimeBaseStructure.TIM_Prescaler = 71;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	/* Output Compare Toggle Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);

	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Disable);

	/* Output Compare Toggle Mode configuration: Channel2 */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;

	TIM_OC3Init(TIM2, &TIM_OCInitStructure);

	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Disable);
	TIM_Cmd(TIM2, ENABLE);

	/* TIM IT enable */
	TIM_ITConfig(TIM2, TIM_IT_CC2 | TIM_IT_CC3, ENABLE);
}
void pwm_tim3_init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Enable the TIM3 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_TimeBaseStructure.TIM_Period = 65535;
	TIM_TimeBaseStructure.TIM_Prescaler = 71;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/* Output Compare Toggle Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR6_Val;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);

	/* Output Compare Toggle Mode configuration: Channel2 */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = CCR7_Val;

	TIM_OC2Init(TIM3, &TIM_OCInitStructure);

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Disable);
	TIM_Cmd(TIM3, ENABLE);

	/* TIM IT enable */
	TIM_ITConfig(TIM3, TIM_IT_CC1 | TIM_IT_CC2, ENABLE);
}




void TIM3_IRQHandler(void)
{
	uint16_t capture = 0;
	/* TIM3_CH1 toggling with frequency = 183.1 Hz */
	if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
		capture = TIM_GetCapture1(TIM3);
		if (pa6_state == 0)
		{
			TIM_SetCompare1(TIM3, capture + duty_ratio6 * (u16)CCR6_Val);
			pa6_state = 1;
		}
		else
		{
			TIM_SetCompare1(TIM3, capture + (1 - duty_ratio6) * (u16)CCR6_Val);
			pa6_state = 0;
		}
	}

	/* TIM3_CH2 toggling with frequency = 366.2 Hz */
	if (TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);
		capture = TIM_GetCapture2(TIM3);
		if (!pa7_state)
		{
			TIM_SetCompare2(TIM3, capture + duty_ratio7 * CCR7_Val);
			pa7_state = 1;
		}
		else
		{
			TIM_SetCompare2(TIM3, capture + (1 - duty_ratio7) * CCR7_Val);
			pa7_state = 0;
		}
	}
}
void pwm_Init()
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = 999;
    TIM_TimeBaseStructure.TIM_Prescaler = 71;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 400;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 500;
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM3, ENABLE);

    TIM_Cmd(TIM3, ENABLE);
}







void Timer2_PwmIn(void){
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  TIM_TimeBaseStructure.TIM_Period = 0xffff;
  TIM_TimeBaseStructure.TIM_Prescaler = 35;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_ICInit(TIM2, &TIM_ICInitStructure);
	

	
	 TIM_SelectInputTrigger(TIM2, TIM_TS_TI2FP2);
  TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Reset);
  TIM_SelectMasterSlaveMode(TIM2, TIM_MasterSlaveMode_Enable);
  TIM_Cmd(TIM2, ENABLE);
  TIM_ITConfig(TIM2, TIM_IT_CC2, ENABLE);
	
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
void TIM2_IRQHandler(void)
{
	__IO uint16_t temp;
	static __IO uint16_t IC1Value_temp,IC2Value_temp;
	if(TIM_GetITStatus(TIM2, TIM_IT_CC2)!= RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);
		IC2Value = TIM_GetCapture2(TIM2);
		temp = IC2Value - IC1Value_temp;
		if(temp==0){
			Frequency_1=0;
		}
		else{
			Frequency_1 = 2000000/temp; //此处的2_000_000 与上面的72M/36相关 
		}
		IC1Value_temp = IC2Value;
		printf("%d\r\n",temp);
	}

}
