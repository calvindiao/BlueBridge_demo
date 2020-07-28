#include <rtc.h>

//variable
#define HH 11
#define MM 55
#define SS 50

//function
void rtc_init()
{
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
    /* Allow access to BKP Domain */
    PWR_BackupAccessCmd(ENABLE);

    /* Reset Backup Domain */
    BKP_DeInit();

    /* Enable the LSI OSC */
    RCC_LSICmd(ENABLE);
    /* Wait till LSI is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
    {
    }
    /* Select the RTC Clock Source */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);

    /* Enable RTC Clock */
    RCC_RTCCLKCmd(ENABLE);

    /* Wait for RTC registers synchronization */
    RTC_WaitForSynchro();

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

    /* Enable the RTC Second */
    RTC_ITConfig(RTC_IT_SEC, ENABLE);

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

    /* Set RTC prescaler: set RTC period to 1sec */
    RTC_SetPrescaler(39999);

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

    RTC_SetCounter(HH * 60 * 60 + MM * 60 + SS);

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

    /* Enable the RTC Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


void display_RTC()
{
    u8 str[20];
	u32  Time;
    Time = RTC_GetCounter();
    sprintf((char*)str,"      %0.2d-%0.2d-%0.2d",Time/3600,(Time%3600)/60,(Time%3600)%60);
	LCD_DisplayStringLine(Line2, str);	   //µÚ¶þÐÐ
}






void RTC_IRQHandler(void)
{
    if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
    {
        if (RTC_GetCounter() == 86400 - 1)
            RTC_SetCounter(0);

        RTC_ClearITPendingBit(RTC_FLAG_SEC);
    }
}
