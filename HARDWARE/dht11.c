#include <dht11.h>

#define delay_us(X)  delayd(X*72/5)

void delayd(unsigned int n)
{
  while (n--);
}

void dht11_init (void )
{
  GPIO_InitTypeDef GPIO_InitStructure;
  /* Enable  clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  , ENABLE);
  
  /* Configure Ports */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_SetBits(GPIOA, GPIO_Pin_7);

}

void mode_input(void )
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void mode_output(void )
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

unsigned int dht11_read(void)
{
  int i;
  long long val;
  int timeout;

  GPIO_ResetBits(GPIOA, GPIO_Pin_7);
  delay_us(18000);  //pulldown  for 18ms
  GPIO_SetBits(GPIOA, GPIO_Pin_7);
  delay_us( 20 );	//pullup for 30us

  mode_input();

  //等待DHT11拉高，80us
  timeout = 5000;
  while( (! GPIO_ReadInputDataBit  (GPIOA, GPIO_Pin_7)) && (timeout > 0) ) timeout--;	 //wait HIGH

  //等待DHT11拉低，80us
  timeout = 5000;
  while( GPIO_ReadInputDataBit (GPIOA, GPIO_Pin_7) && (timeout > 0) ) timeout-- ;	 //wait LOW

#define CHECK_TIME 28

  for(i=0;i<40;i++)
  {
	timeout = 5000;
	while( (! GPIO_ReadInputDataBit  (GPIOA, GPIO_Pin_7)) && (timeout > 0) ) timeout--;	 //wait HIGH

	delay_us(CHECK_TIME);
	if ( GPIO_ReadInputDataBit (GPIOA, GPIO_Pin_7) )
	{
	  val=(val<<1)+1;
	} else {
	  val<<=1;
	}

	timeout = 5000;
	while( GPIO_ReadInputDataBit (GPIOA, GPIO_Pin_7) && (timeout > 0) ) timeout-- ;	 //wait LOW
  }

  mode_output();
  GPIO_SetBits(GPIOA, GPIO_Pin_7);

  if (((val>>32)+(val>>24)+(val>>16)+(val>>8) -val ) & 0xff  ) return 0;
    else return val>>8; 

}
void DisplayDht11(void)
{
    u8 display[30];
    unsigned int value=dht11_read();
    

    
    sprintf((char*)display,"M:%d",value>>24);
    LCD_DisplayStringLine(Line0,display);
   
    sprintf((char*)display,"T:%d",(value&0x0000ff00)>>8);
    LCD_DisplayStringLine(Line1,display);
    
    sprintf((char*)display,"v:%d",value);
    LCD_DisplayStringLine(Line2,display);

   
}
