#include<LPC21xx.h>

#define lcd_d 0xF<<4

#define rs 1<<12

//#define rw 1<<18

#define e 1<<13


typedef unsigned int U32;

typedef unsigned char U8;

typedef signed char S8;

typedef float F32;

				 

										 

void delay_milliseconds(U32 milliseconds)

{

	//T0CTCR=0X00;

	T0PR = 15000-1;

	T0TCR = 0X01;

	while(T0TC<milliseconds);

	T0TCR = 0x03;

	T0TCR = 0x00;

}


void lcd_cmd(U8 d)

{

   IOCLR0=lcd_d;

	IOSET0 = (d&0xF0);

	IOCLR0 = rs;

	//IOCLR0 = rw;

	IOSET0 =e;

	delay_milliseconds(2);

	IOCLR0 =e;


	IOCLR0=lcd_d;

	IOSET0 = (d&0x0F)<<4;

	IOCLR0 = rs;

	//IOCLR0 = rw;

	IOSET0 =e;

	delay_milliseconds(2);

	IOCLR0 =e;

}


void lcd_data(U8 d)

{


	IOCLR0=lcd_d;

	IOSET0 = (d&0xF0);

	IOSET0 = rs;

	//IOCLR0 = rw;

	IOSET0 =e;

	delay_milliseconds(2);

	IOCLR0 =e;


	IOCLR0=lcd_d;

	IOSET0 = (d&0x0F)<<4;

	IOSET0 = rs;

	//IOCLR0 = rw;

	IOSET0 =e;

	delay_milliseconds(2);

	IOCLR0 =e;

}


void lcd_init(void)

{

	IODIR0 |= lcd_d|rs|e;

	lcd_cmd(0x01);

	lcd_cmd(0x02);

	lcd_cmd(0x0C);

	lcd_cmd(0x28);

	lcd_cmd(0x80);

}


void str(U8 *s)

{

	while(*s)

		lcd_data(*s++);

}
