#include<stc15f2k60s2.h>
#include"uart.h"
#include"key.h"

#define fosc 11059200
#define baud 1200

unsigned char mode=0;
unsigned char rdata=0;
unsigned char sendflag=0;

void TimerConfiguration();
void AllInit();

void main()
{
    AllInit();
	TimerConfiguration();
    while(1)
	{
	     if(mode==0)
		 {
		      if(sendflag==1)
			  {
			     sendflag=0;
				 SendStr("i am a");
			  }	  	   
		/*	  if(keyvalue==5)
			  {
			      keyvalue=0;
				  SendBit('1');
			  }					*/
		 }
	}
}

void TimerConfiguration()
{
    TMOD=0x01;
	TH0=(65536-1000)/256;
	TL0=(65536-1000)%256;
	ET0=1;
	TR0=1;

	SCON=0x50;								  //串口方式设置
	AUXR=0x40;								  //不能写AUXR|=0X40;
	TH1=(65536-(fosc/4/baud))>>8;
	TL1=(65536-(fosc/4/baud));
	ET1=0;
	TR1=1;
	ES=1;

/*
    SCON = 0x50;		//8???,?????
	AUXR |= 0x40;		//???1???Fosc,?1T
	AUXR &= 0xFE;		//??1?????1???????
	TMOD &= 0x0F;		//?????1?16???????
	TL1 = 0xE0;		//??????
	TH1 = 0xFE;		//??????
	ET1 = 0;		//?????1??
	TR1 = 1;    
*/
	EA=1;
}

void AllInit()
{
     P0=0xff;
	 P2=(P2&0x1f)|0x80;
	 P2&=0x1f;

	 P0=0x00;
	 P2=(P2&0x1f)|0xa0;
	 P2&=0x1f;
}

void Timer0() interrupt 1
{
    TH0=(65536-1000)/256;
	TL0=(65536-1000)%256;
	KeyDown();
}

void Uart2() interrupt 4
{
   if(RI)
   {
       rdata=SBUF;
	   if(rdata=='k')					 //键盘按下会有0x00
	   {
	      sendflag=1;
	   }		   		
	   RI=0;
   }
}