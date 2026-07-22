#include<lpc21xx.h>
#include "can.h"
#include "can_defines.h"
#include "delay.h"
#include "lcd.h"
#include "i2c.h"
//port0.1
//port0.7
#define CH_NO_0 14
#define CH_NO_2 16

int node1=0,node2=0;

int flag_eint0=0;
int flag_eint2=0;
 CANF TXF;
	 CANF RXF;

void eint0_isr()__irq
{
    flag_eint0=!flag_eint0;  
	flag_eint2=0;
	EXTINT=1<<0;
    VICVectAddr=0;
}
void eint2_isr()__irq
{
    flag_eint2=!flag_eint2;
	flag_eint0=0;
    EXTINT=1<<2;
    VICVectAddr=0;
}
void enable_eint_2()
{
		PINSEL0|=0x0000C000;
    VICIntEnable=(1<<CH_NO_2);
    VICIntSelect&=~((1<<CH_NO_2));
    VICVectAddr2=(unsigned int)eint2_isr;
    VICVectCntl2=(1<<5) |(CH_NO_2);
    EXTMODE=1<<2;    
}
void enable_eint_0()
{
    PINSEL0|=0x0000000C;
    VICIntEnable=(1<<CH_NO_0);
    VICIntSelect&=~((1<<CH_NO_0));
    VICVectAddr0=(unsigned int)eint0_isr;
    VICVectCntl0=(1<<5) |(CH_NO_0);
    EXTMODE=1<<0;
}
int main()
{
    
    //INDICATORS
	IODIR0|=3<<21;
	IOSET0=3<<21;
   
    enable_eint_0();
    enable_eint_2();
	Init_lcd();
	Init_can();
	Init_I2C();
	Init_accelerometer();
	string_lcd("CAN PROJECT");
	cmd_lcd(0x94);
	string_lcd("fuel=");
	cmd_lcd(0xD4);
	string_lcd("INDICATOR:");
	cmd_lcd(0x48);
	left_indicator();
	cmd_lcd(0x40);
	right_indicator();
	cmd_lcd(0xD4+10);
	char_lcd(1);
	cmd_lcd(0xD4+12);
	char_lcd(0);
	cmd_lcd(0xA2);

    while(1)		
    {
	node1++;
	node2++;
			read_accelerometer();
			//CAN1_Rx(&RXF);
	 if(flag_eint0==1)
	 {
	  IOCLR0=1<<21;
	  TXF.ID=0X2;
        TXF.data1='L';
        TXF.bfv.DLC=4;
        TXF.bfv.RTR=0;
        CAN1_Tx(TXF);
	  IOSET0=1<<22;
	  cmd_lcd(0xd4+10);
	  char_lcd(1);
	  delay_ms(500);
	  cmd_lcd(0xd4+10);
	  char_lcd(' ');
	  delay_ms(500);
	    //IOSET0=1<<22;
	 }
	if(flag_eint2==1)
	{
		IOCLR0=1<<22;	
		TXF.ID=0X2;
        TXF.data1='R';
        TXF.bfv.DLC=4;
        TXF.bfv.RTR=0;
        CAN1_Tx(TXF);
	  IOSET0=1<<21;
	  cmd_lcd(0xd4+12);
	  char_lcd(0);
	  delay_ms(500);
	  cmd_lcd(0xd4+12);
	  char_lcd(' ');
	  delay_ms(500);
		//IOSET0=1<<21;
	}
	if((flag_eint0==1) && (flag_eint2==1)) 
	{
		TXF.ID=0X2;
        TXF.data1='O';
        TXF.bfv.DLC=4;
        TXF.bfv.RTR=0;
        CAN1_Tx(TXF);
		IOSET0=3<<23;
  	}   
	//CAN1_Rx(&RXF);
	/*if(RXF.ID==0x08)
	{
		node1=0;
	}*/
	delay_ms(200);
	if((C1GSR&1)==1)
	{
  	CAN1_Rx(&RXF);
	if(RXF.ID==0x3)
	{	
		cmd_lcd(0x94);
		string_lcd("                   ");
		node2=0;
		cmd_lcd(0x94);
	  string_lcd("fuel=");
		cmd_lcd(0x94+5);
		unsigned_lcd(RXF.data1);
		cmd_lcd(0x94+10);
		char_lcd('%');	
	} 
	delay_ms(200);
	}
/*else
{
	cmd_lcd(0x94);
		string_lcd("                   ");
		cmd_lcd(0x94);
		string_lcd("node disconnnected");	
}	*/
/*if(node1>20)
	{
		cmd_lcd(0xD4);
		string_lcd("                   ");
		cmd_lcd(0xD4);
		string_lcd("node disconnnected");		 */
	
	/*if(node2>2000)
	{
		cmd_lcd(0x94);
		string_lcd("                   ");
		cmd_lcd(0x94);
		string_lcd("node disconnnected");		
	} */    
  }
}
