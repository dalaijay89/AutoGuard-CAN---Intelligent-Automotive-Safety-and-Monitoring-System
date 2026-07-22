#include<lpc21xx.h>
#include"adc_lcd_declaration.h"
#include"adc_defines.h"
void Init_adc(void)
{
 	PINSEL1|=0;
	//cfg port 0.28 as AINl
	PINSEL1|=0x15400000;
	//enable ADCR by using PDN
	ADCR|=PDN|CLKDIV_VAL;
}
void read_adc(unsigned int chno,unsigned int*adcDval,float*ear)
{
	//clear the channel
	ADCR&=~(255<<0);
	//select the channel number and start conversion
	ADCR|=1<<chno|START_CONV;
	//wait for conversion
	//we need to take a delay more than equal to 2.44 us
	delay_ms(10);
	//wait for the conversion to be done
	while(((ADDR>>DONE_BIT)&1)==0);
	//after the conversion is done stop the conversion
	ADCR&=~START_CONV;
	//extract values
	*adcDval=((ADDR>>RESULT)&1023);
	*ear=(3.3/1023)*(*adcDval);
}
