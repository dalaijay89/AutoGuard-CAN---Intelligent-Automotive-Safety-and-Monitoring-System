#include<lpc21xx.h> 
#include"can.h"
#include"adc_defines.h"
#include"adc_lcd_declaration.h"
unsigned int adcDval;
float ear;
int high=2.42,low=0.40;
int fuel_per;
int main()
{	
	
	CANF TXF;
	Init_can();
	Init_lcd();
	Init_adc();
		TXF.ID=0X3;
		TXF.bfv.DLC=8;
        TXF.bfv.RTR=0;
	str_lcd("Fuel Checking...");
	IODIR0|=1<<1;
	while(1)
	{
		read_adc(1,&adcDval,&ear);
		cmd_lcd(0xc0);
		/*float_lcd(ear,2);
		delay_ms(100);*/
		fuel_per=((ear-0)/(100-0))*100;
		//fuel_per=ear*100;
		cmd_lcd(0x94);
		//unsigned_lcd(fuel_per);
	
        TXF.data1=fuel_per;;
        
        CAN1_Tx(TXF);
	  IOPIN0^=1;
	  delay_ms(500);

		/*unsigned_lcd(fuel_per);
		cmd_lcd(0xc2);
		char_lcd('%');*/
	}
}
