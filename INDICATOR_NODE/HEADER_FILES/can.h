#include<lpc21xx.h>
typedef struct CAN_frame
{
	unsigned int ID;
	struct bitfield
	{
		unsigned int RTR : 1;
		unsigned int DLC : 4;
	}bfv;
	unsigned int data1,data2;
}CANF;
void Init_can(void);
void CAN1_Tx(CANF );
void CAN1_Rx(CANF*);
