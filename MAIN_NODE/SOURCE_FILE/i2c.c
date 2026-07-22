#include "delay.h"
#include "lcd.h"
// defines for cfg SCL and SDA
//#define SCA 0x00000010
#define SCA_SDA 0x00000050
//defines for CCLK and I2C speed
#define FOSC 12000000
#define CCLK (FOSC*5)
#define PCLK (CCLK/4)
#define I2C_SPEED 100000
#define LOAD_VAL ((PCLK/I2C_SPEED)/2)

//defines for CONSET sfr
#define AA_BIT 2
#define SI_BIT 3
#define STO_BIT 4
#define STA_BIT 5
#define I2_EN 6

//defines for CONCLR sfr
#define AAC_BIT 2
#define SIC_BIT 3


//defines for accelerometer
#define MMA_ADDR 0x4C
#define X_DATA_REG 0x00
#define Y_DATA_REG 0x01
#define Z_DATA_REG 0x02
#define MODE_REG 0x07
#define STANDBY_MODE 0x00
#define ACTIVE_MODE 0x01

#include<lpc21xx.h>
unsigned char x,y,z;
void Init_I2C()
{
	PINSEL0|=SCA_SDA;
	I2SCLL=LOAD_VAL;
	I2SCLH=LOAD_VAL;
	I2CONSET=1<<I2_EN;
}

void I2C_start()
{
	I2CONSET=(1<<STA_BIT);
	//I2CONCLR=1<<SIC_BIT;
	while(((I2CONSET >> SI_BIT)&1)==0);
	I2CONCLR=(1<<STA_BIT);
}
 
void I2C_restart()
{
	I2CONSET=(1<<STA_BIT);
	I2CONCLR=1<<SIC_BIT;
	while(((I2CONSET >> SI_BIT)&1)==0);
	I2CONCLR=(1<<STA_BIT);
}
void I2C_write(char data)
{
	I2DAT=data;
	I2CONCLR=1<<SIC_BIT;
	while(((I2CONSET >> SI_BIT)&1)==0);
}


void I2C_stop()
{
	I2CONSET=(1<<STO_BIT);
	I2CONCLR=(1<<SIC_BIT);
}

char read_nack()
{
	I2CONCLR=(1<<AA_BIT);
	I2CONCLR=1<<SIC_BIT;
	while(((I2CONSET >> SI_BIT)&1)==0);
	return I2DAT;
}	
char read_mack()
{
	I2CONCLR=1<<SIC_BIT;
	I2CONSET=1<<AAC_BIT;
	while(((I2CONSET >>SI_BIT)&1)==0);
	return I2DAT;	
}

void MMA_write(char wbufferAddr,char data)
{
	I2C_start();
	I2C_write((MMA_ADDR<<1)|0);
	//I2C_write(wbufferAddr>>8);
	I2C_write(wbufferAddr);
	I2C_write(data);
	I2C_stop();
}

char MMA_read(char rbufferAddr)
{
	char data;
	I2C_start();
	I2C_write((MMA_ADDR<<1)|0);
	I2C_write(rbufferAddr>>8);
	I2C_write(rbufferAddr);
	I2C_restart();
	I2C_write((MMA_ADDR<<1)|1);
	data=read_nack();
	I2C_stop();
	return data;
}
void Init_accelerometer()
{
	MMA_write(MODE_REG,STANDBY_MODE);
	delay_ms(10);
	MMA_write(MODE_REG,ACTIVE_MODE);
	delay_ms(10);
}

char convert_6_bit(char val)
{
	val&=0x03F;
	if(val &0x20)
	{
		val|=0xc0;
	}
	return (char)val;
}

void read_accelerometer()
{
	x=convert_6_bit(MMA_read(X_DATA_REG));
	y=convert_6_bit(MMA_read(Y_DATA_REG));
	z=convert_6_bit(MMA_read(Z_DATA_REG));
	if(x>15 && y>0 && z>240)
	{
		cmd_lcd(0x01);
		delay_ms(5);
		cmd_lcd(0x80);
		string_lcd("Air bags deployed1");
		char_lcd(' ');
		unsigned_lcd(x);
		char_lcd(' ');
		unsigned_lcd(y);
		char_lcd(' ');
		unsigned_lcd(z);
		char_lcd(' ');
		while(1);
	}
	else if(x>235 && y>240 && z>235)
	{
		cmd_lcd(0x01);
		delay_ms(5);
		cmd_lcd(0x80);
		string_lcd("Air bags deployed2");
		char_lcd(' ');
		unsigned_lcd(x);
		char_lcd(' ');
		unsigned_lcd(y);
		char_lcd(' ');
		unsigned_lcd(z);
		char_lcd(' ');
		while(1);
	}
	else if(x>4 && y>240 && z>240)
	{
		cmd_lcd(0x01);
		delay_ms(5);
		cmd_lcd(0x80);
		string_lcd("Air bags deployed3");
		char_lcd(' ');
		unsigned_lcd(x);
		char_lcd(' ');
		unsigned_lcd(y);
		char_lcd(' ');
		unsigned_lcd(z);
		char_lcd(' ');
		while(1);
	}
	else if(x>2 && y>10 && z>240)
	{
		cmd_lcd(0x01);
		delay_ms(5);
		cmd_lcd(0x80);
		string_lcd("Air bags deployed4");
		char_lcd(' ');
		unsigned_lcd(x);
		char_lcd(' ');
		unsigned_lcd(y);
		char_lcd(' ');
		unsigned_lcd(z);
		char_lcd(' ');
		while(1);
	}
	else
	{
		cmd_lcd(0xc0);
		string_lcd("Safe condition");
	}
}
