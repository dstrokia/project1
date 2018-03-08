#include"key.h"

unsigned char keytime=0,keyvalue=0;
unsigned char bdata IN=0xff;
unsigned char col=0,row=0;
sbit IN1=IN^0;
sbit IN2=IN^1;
sbit IN3=IN^2;
sbit IN4=IN^3;
sbit IN5=IN^4;
sbit IN6=IN^5;
sbit IN7=IN^6;
sbit IN8=IN^7;

void xin()
{
   IN1=P30;
   IN2=P31;
   IN3=P32;
   IN4=P33;
   IN5=P34;
   IN6=P35;
   IN7=P42;
   IN8=P44;
}

void xout()
{
   P30=IN1;
   P31=IN2;
   P32=IN3;
   P33=IN4;
   P34=IN5;
   P35=IN6;
   P42=IN7;
   P44=IN8;
}

void KeyDown()
{
   IN=0x0f;
   xout();
   xin();
   row=IN;
   if(row!=0x0f)
   {
       keytime++;
	   if(keytime==25)
	   {
	       IN=0xf0;
		   xout();
		   xin();
		   col=IN;
		   col=col|row;
		   switch(col)
		   {
		      case(0x77):keyvalue=4;break;
			  case(0x7b):keyvalue=5;break;
			  case(0x7d):keyvalue=6;break;
			  case(0x7e):keyvalue=7;break;
			  case(0xb7):keyvalue=8;break;
			  case(0xbb):keyvalue=9;break;
			  case(0xbd):keyvalue=10;break;
			  case(0xbe):keyvalue=11;break;
			  case(0xd7):keyvalue=12;break;
			  case(0xdb):keyvalue=13;break;
			  case(0xdd):keyvalue=14;break;
			  case(0xde):keyvalue=15;break;
			  case(0xe7):keyvalue=16;break;
			  case(0xeb):keyvalue=17;break;
			  case(0xed):keyvalue=18;break;
			  case(0xee):keyvalue=19;break;
		   }
	   }
	   else if(keytime>=26)
	   {
	      keytime=26;
	   }
   } 
   else keytime=0;
}