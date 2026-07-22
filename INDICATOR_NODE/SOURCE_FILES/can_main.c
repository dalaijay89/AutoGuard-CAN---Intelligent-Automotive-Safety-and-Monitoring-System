#include<lpc21xx.h>
#include"can.h"
#include"delay.h"
#include"declaration.h"
#include"defines.h"
int i;
//extern int flag1,flag2;
int main()
{
	CANF TXF;
	CANF RXF;
	//initialize CAN
	Init_can();
	//giving direction for leds for the signals whether left or right
	IODIR0|=255<<8;
	//since all the leds in lpc2129 are active low first we need to off those leds so we are setting these leds
	IOSET0=255<<8;
	while(1)
	{
		CAN1_Rx(&RXF);
		if((RXF.ID==0x2)&&(RXF.data1=='R'))
		{
			IOSET0=15<<12;
			for(i=11;i>=8;i--)
			{
				IOCLR0=1<<i;
				delay_ms(50);
			}
			IOSET0=15<<8;
		}
		//left signal
		if((RXF.ID==0x2)&&(RXF.data1=='L'))
		{			
			IOSET0=15<<8;
			for(i=12;i<=15;i++)
			{
				IOCLR0=1<<i;
				delay_ms(50);
			}
				IOSET0=15<<12;
		}	
		//when both switches are pressed	
		if((RXF.ID==0x2)&&(RXF.data1=='O'))
		{
			IOSET0=255<<8;
		}
		}
		//C01CMR|=1<<2;
}
