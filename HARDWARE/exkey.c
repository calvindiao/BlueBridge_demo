#include "exkey.h"

void ex_key_init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2 | RCC_APB2Periph_GPIOA, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC2, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC2, ADC_Channel_5, 1, ADC_SampleTime_239Cycles5);
	ADC_Cmd(ADC2, ENABLE);

	/* Enable ADC1 reset calibration register */
	ADC_ResetCalibration(ADC2);
	/* Check the end of ADC1 reset calibration register */
	while (ADC_GetResetCalibrationStatus(ADC2))
		;

	/* Start ADC1 calibration */
	ADC_StartCalibration(ADC2);
	/* Check the end of ADC1 calibration */
	while (ADC_GetCalibrationStatus(ADC2))
		;
}


uint16_t get_adc2(void)		 //获取ADC的数值
{
	ADC_SoftwareStartConvCmd(ADC2, ENABLE);
	while (!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC))
		;
	return ADC_GetConversionValue(ADC2);
}

u8 ex_key_scan(void)
{
    int temp=get_adc2();
    if (0<=temp&&temp<=50)  return 1;
    else if (150<=temp&&temp<=250)  return 2;
    else if (500<=temp&&temp<=600)  return 3;
    else if (900<=temp&&temp<=1100)  return 4;
    else if (1300<=temp&&temp<=1450)  return 5;
    else if (1700<=temp&&temp<=1900)  return 6;
    else if (2200<=temp&&temp<=2300)  return 7;
    else if (2700<=temp&&temp<=2900)  return 8;
    else return 0;
}
