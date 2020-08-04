#ifndef __DHT11_H
#define __DHT11_H


#include <headfile.h>








void dht11_init (void );
void delay(unsigned int n);

unsigned int dht11_read(void);
void DisplayDht11(void);

#endif
