#include<lpc21xx.h>
#include"delay.h"
#include"adc_defines.h"
void write_lcd(unsigned char data)
{
        //to write we need to make RW as 0
        IOCLR0=1<<RW;
        //masking the data which is present and writing the data to port 0.8 to 0.15
        IOPIN0=(IOPIN0&~(255<<LCD_DATA))|(data<<LCD_DATA);
        //whenever we set and clear,the data will be latched
        IOSET0=1<<EN;
        delay_us(1);
        IOCLR0=1<<EN;
        delay_ms(2);
}
void cmd_lcd(unsigned char cmd)
{
        //select command register by making the RS as 0 
        IOCLR0=1<<RS;
        //write command into lcd
        write_lcd(cmd);
}
void char_lcd(unsigned char ascii)
{
        //select the data register by making the RS as 1
        IOSET0=1<<RS;
        //passing the ascii value to write into lcd 
        write_lcd(ascii);
}
void Init_lcd(void)
{
        //cfg po 0.8 to po 0.15 as outputs for lcd data pins
        IODIR0|=255<<LCD_DATA;
        //cfg the registers RS,RW,EN as outputs
        IODIR0|=7<<RS;
        delay_ms(15);
        //8 bit mode 1 line
        cmd_lcd(0x30);
        delay_ms(5);
        cmd_lcd(0x30);
        delay_us(100);
        //8 bit mode 2line
        cmd_lcd(0x38);
	  cmd_lcd(0x02);
        //to clear the lcd
        cmd_lcd(0x01);
        //to display on cursor on
        cmd_lcd(0x0E);
        //to shift right
        cmd_lcd(0x06);
}
void str_lcd(unsigned char* ptr)
{
        //run the loop untill string reaches the null character 
        while(*ptr)
        {
                //sending word by word to the char_lcd to get displayed on the lcd
                char_lcd(*ptr++);
        }
}
void unsigned_lcd(unsigned int n)
{
        unsigned char a[10];
        int i=0;
        if(n==0)
        {
                char_lcd('0');
        }
        else
        {
                //running untill it reaches 0
                while(n!=0)
                {
                        //converting the integer values into ascii and storing them in an array
                        a[i++]=(n%10)+48;
                        n/=10;
                }
        }
        for(--i;i>=0;i--)
        {
                //sending the data to display on the lcd
                char_lcd(a[i]);
        }
}
void float_lcd(float f,unsigned int n)
{
        unsigned  int num;
        signed int i;
        //for negative values
		if(f<0.0)
        {
                char_lcd('-');
                f=-f;
        }
        //first converting the float to integer and displaying that value first 
        num=f;
        unsigned_lcd(num);
        //to display a point 
        char_lcd('.');
        //loop for how many places after the point
        for(i=0;i<n;i++)
        {
                f=(f-num)*10;
                //float value is assigned to integer variable so that float gets converted into integer
                num=f;
                //integer to ascii
                char_lcd(num+48);
        }
}
