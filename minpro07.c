#include<lpc21xx.h>
#include "4bit.h"
#define LED 1<<8
#define FAN 1<<11
void UART0_CONFIG(void);
void UART0_TX(unsigned char);
unsigned char UART0_RX(void);
int main()	
{
  
  unsigned char x;
  IODIR0|=LED|FAN;
  IOSET0=LED;
  IOCLR0=FAN;
  lcd_init();
  str("HOME AUTOMATION");
  UART0_CONFIG();
  while(1)
  {
  x=UART0_RX();
  if(x=='1')
  {
	IOCLR0=LED;
	lcd_cmd(0xC0);
	str("LED ON");
	}
  else if(x=='2')
  {
   IOSET0=LED;
   lcd_cmd(0xC0);
   str("LED OFF");
   }
   else if(x=='3')
   {
    IOSET0=FAN;
    lcd_cmd(0xC0);
	str("FAN ON");
	}
	else if(x=='4')
	{
	IOCLR0=FAN;
	lcd_cmd(0xC0);
	str("FAN OFF");
	}
  }
 }
 void UART0_CONFIG(void)
 {
  PINSEL0=0X00000005;
  U0LCR=0X83;
  U0DLL=97;
  U0LCR=0X03;
  }
void UART0_TX(unsigned char d)
  {
   while((U0LSR&(1<<5))==0);
   U0THR=d;
   }
unsigned char UART0_RX(void)
  {
   while((U0LSR&(1<<5))==0);
   return U0RBR;
   }


			