#ifndef _led_h_
#define _led_h_



#include <headfile.h>

//variable
extern u8 led_state;














//function


void led_init(void);






void led_control(u8 led_state);	
//控制led的亮灭，如果LED8-LED1 为亮亮灭灭 灭灭灭灭 对应二进制为1100 0000 
//即输入参数为0xC0









#endif
