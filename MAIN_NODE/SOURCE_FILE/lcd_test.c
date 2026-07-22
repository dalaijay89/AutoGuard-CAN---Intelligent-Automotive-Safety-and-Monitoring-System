#include<lpc21xx.h>
#include "delay.h"
#define RS 16
#define RW 18
#define EN 17
#define DATA 8
void write_lcd(int );
void cmd_lcd(int data)
{
	IOCLR0=1<<RS;
	write_lcd(data);
}
void Init_lcd()
{
	IODIR0 |=1<<RS;
	IODIR0 |=1<<RW;
	IODIR0 |=1<<EN;
	IODIR0 |=0XFF<<DATA;
	delay_ms(15);
	cmd_lcd(0x30);
	delay_ms(5);
	cmd_lcd(0x30);
	delay_us(100);
	cmd_lcd(0x30);
	cmd_lcd(0x38);
	cmd_lcd(0x02);
	cmd_lcd(0x01);
	cmd_lcd(0x0E);
	cmd_lcd(0x06);	
}
void write_lcd(int data)
{
	//we go for write /output device at present
	// RW:0/1  0: WRITE 1: READ
	IOCLR0=1<<RW;
	//clear disply and update command
	IOPIN0 = (IOPIN0&~(0XFF<<DATA))| (data<<DATA);
	// enable should high to low for write operation
	// enable should low to high for read operation
	IOSET0 =1<<EN;
	//give some delay for updation
	delay_us(1);
	IOCLR0 =1<<EN;
	delay_ms(2);
}
void char_lcd(char data)
{
	//to display data RS should be data register
	//RS: 1 
	IOSET0 = 1<<RS;
	write_lcd(data);
}
void string_lcd(char*str)
{
	while(*str)
	{ 
	  char_lcd(*str++);
	}		  
}
void unsigned_lcd(char n)
{
	char a[10];
	short int i=0;
	if(n==0)
	{
		char_lcd('0');
	}
	else
	{
		while(n)
		{
			a[i++]=(n%10)+48;
			n/=10;
		}
		for(--i; i>=0; i--)
		{
			char_lcd(a[i]);
		}
	}
}

void float_lcd(float f, char nDP)
{
	int n,i;
	if(f<0)
	{
		char_lcd('-');
		f=-f;
	}
		n=f;
		unsigned_lcd(n);
		char_lcd('.');
	for(i=0; i<nDP; i++)
	{
		f=(f-n)*10;
		n=f;
		char_lcd(n+'0');
	}
}
void right_indicator(void)
{
	int i;
	char LUT[]={0x04,0x06,0x1F,0x06,0x04,0x00,0x00};
	for(i=0;i<8;i++)
	{
		char_lcd(LUT[i]);
	}
}
void left_indicator(void)
{
	int i;
	char LUT[]={0x04,0x0c,0x1f,0x0c,0x04,0x00,0x00};
	for(i=0;i<8;i++)
	{
		char_lcd(LUT[i]);
	}
}
