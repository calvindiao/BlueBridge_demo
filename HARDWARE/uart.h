#ifndef __uart_h__
#define __uart_h__

//headfile
#include <headfile.h>
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)	
















//variable


extern u8 Rx_flag;		   //接受成功标志位
extern u8 RxCounter1;	   //接受数量多少的计数器
extern u8 RxBuffer1[30];   //接受缓存区，接受到的数据都在这里





















//function
void uart_init(void);






#endif



































