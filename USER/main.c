#include <headfile.h>


//variable
u32 TimingDelay = 0;
u16 adc_value;
double  test_variable;




extern u8 display[30];




//function	  declare
void Delay_Ms(u32 nTime);

//code
int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	SysTick_Config(SystemCoreClock / 1000);
	Delay_Ms(200);

	//LCD init
	STM3210B_LCD_Init();
	LCD_Clear(Blue);
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(White);

	//
	led_init();
	key_init();
	uart_init();
	i2c_init();
	rtc_init();
  tim4_Init(999,71);		//1ms

  adc_init();
  dht11_init();
//    ex_key_init();

//	pwm_tim2_init();
//	pwm_tim3_init();
//	pwm_Init();
//	Timer2_PwmIn();
    

	led_state=0xfe;
	while (1)
	{
		key_scan();
	

	}
}

//function
void Delay_Ms(u32 nTime)	 //ÑÓÊ±º¯Êý
{
	TimingDelay = nTime;
	while (TimingDelay != 0)
		;
}


