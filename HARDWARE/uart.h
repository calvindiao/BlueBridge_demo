#ifndef __uart_h__
#define __uart_h__

//headfile
#include <headfile.h>
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)	
















//variable


extern u8 Rx_flag;		   //���ܳɹ���־λ
extern u8 RxCounter1;	   //�����������ٵļ�����
extern u8 RxBuffer1[30];   //���ܻ����������ܵ������ݶ�������





















//function
void uart_init(void);






#endif



































