#ifndef _led_h_
#define _led_h_



#include <headfile.h>

//variable
extern u8 led_state;














//function


void led_init(void);






void led_control(u8 led_state);	
//����led���������LED8-LED1 Ϊ�������� �������� ��Ӧ������Ϊ1100 0000 
//���������Ϊ0xC0









#endif
