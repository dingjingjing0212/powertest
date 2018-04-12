#include "IIC.h"

//Bus free time between a STOP and START condition: >1.3us
//LOW period of the SCL clock: >1.3us
//HIGH period of the SCL clock: >0.6us
//Set-up time for a repeated START condition: >0.6us
//Hold time (repeated) START condition: >0.6us
//Data set-up time: >0.1us
//Set-up time for STOP condition >0.6us
//Machine Cycle Time = 1.08us @ 11.0592MHz

void IIC_Start(void)
{
	SCL = 1;
	SDA = 1;
	SDA = 0;
	SCL = 0;
}

void IIC_Stop(void)
{
 	SDA = 0;
	SCL = 1;
	SDA = 1;
}

void IIC_SendACK(bit ACK_Type)
{
 	SDA = ACK_Type;
	SCL = 1;
	SCL = 0;
	SDA = 1;							//Release SDA.
}

bit IIC_RecvACK_Error(void)
{
	bit RecvAckError;

	SDA = 1;							//Write "1" before read.
	SCL = 1;
	RecvAckError = SDA;		//Read SDA.
	SCL = 0;

	return RecvAckError;
}

void IIC_SendOneByte(unsigned char TxValue)
{
	unsigned char i;

	for(i=0; i<8; i++)
	{
		TxValue <<= 1;			//Data is transferred with MSB first.
		SDA = CY;						//If MSB is 1, the Carry Flag (CY) will be set to 1 after left logical shift, and vice versa.
		SCL = 1;
		SCL = 0;
	}
}

unsigned char IIC_RecvOneByte(void)
{
	unsigned char RxValue = 0;
	unsigned char i;

	SDA = 1;							//Write "1" before read.
	for(i=0; i<8; i++)
	{
		RxValue <<= 1;
		SCL = 1;
		RxValue |= SDA;
		SCL = 0;
	}

	return RxValue;
}
