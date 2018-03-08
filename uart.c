#include"uart.h"

void SendBit(unsigned char dat)
{
    SBUF=dat;
	while(!TI);
	TI=0;
}

void SendStr(unsigned char *dat)
{
    while((*dat)!='\0')
	{
		 SendBit(*dat);
		 dat++;
	}
}