#include<lpc21xx.h>
#include"can.h"
#include"can_defines.h"
CANF txF;
void Init_can(void)
{
	//cfg p0.25 as CAN1_RX_pin(RD1)
	PINSEL1|=0x00040000;
	//reset can1 controller
	C1MOD|=1<<RM_BIT;
	//all recieved messages are accepted
	//AFMR&=~(1<<AccOFF_BIT);
	AFMR=2;
	//set baud rate for CAN
	C1BTR=BTR_LVAL;
	//enable CAN1 controller
	C1MOD&=~(1<<RM_BIT); 
}
void CAN1_Tx(CANF txF)
{
  //CHECKING that the TX buffer is empty
  while(((C1GSR>>TBS1_BIT)&1)==0);
  //cfg Tx ID
  C1TID1=txF.ID;
  //cfg RTR & DLC
  C1TFI1=((txF.bfv.RTR<<RTR_BIT)|(txF.bfv.DLC<<DLC_BITS));
  //check whether data/remote frames to transmit
  if(txF.bfv.RTR!=1)
  {
  	//if D frame,wr to data transmit buffer
	C1TDA1=txF.data1;
	C1TDB1=txF.data2;
  }	
  //select Tx buffer 1 & start Xmission
  C1CMR=((1<<STB1_BIT)|(1<<TR_BIT));
  //wait until tx complete
  while(((C1GSR>>TCS1_BIT)&1)==0);
}
void CAN1_Rx(CANF*rxF)
{
	//wait for CAN frame recv status
	while(((C1GSR>>RBS_BIT)&1)==0);
	//read 11 bit can id of recieved frame
	rxF->ID=C1RID;
	//read & extract data/remote from status
	rxF->bfv.RTR=((C1RFS>>RTR_BIT)&1);
	//extract data length
	rxF->bfv.DLC=((C1RFS>>DLC_BITS)&15);
	//check if recieved frame is data frame
	if(rxF->bfv.RTR==0)
	{
		//extract data bytes 1-4
		rxF->data1=C1RDA;
		//extract data bytes 5-8
		rxF->data2=C1RDB;
	}
	//release recieve buffer command
	C1CMR|=(1<<RRB_BIT);
}
