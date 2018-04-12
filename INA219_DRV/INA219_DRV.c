#include "INA219_DRV.h"
#include "..\IIC\IIC.h"

unsigned short INA219_ReadReg(unsigned char WAddree,unsigned char RegBase)
{
	unsigned short RegValue = 0;

	IIC_Start();
	IIC_SendOneByte(WAddree);
	if(!IIC_RecvACK_Error())
	{
		IIC_SendOneByte(RegBase);
		if(!IIC_RecvACK_Error())
		{
			//IIC_Stop();
			IIC_Start();
			IIC_SendOneByte(WAddree+1);
			if(!IIC_RecvACK_Error())
			{
				RegValue = IIC_RecvOneByte();
				IIC_SendACK(ACK);
				RegValue = RegValue << 8; 
				RegValue |= IIC_RecvOneByte();
				IIC_SendACK(NACK);
			}
		}
	}
	IIC_Stop();

	return RegValue;
}

bit INA219_WriteReg(unsigned char WAddree,unsigned char RegBase, unsigned short RegValue)
{
	bit WrRegError = 1;

	IIC_Start();
	IIC_SendOneByte(WAddree);
	if(!IIC_RecvACK_Error())
	{
		IIC_SendOneByte(RegBase);
		if(!IIC_RecvACK_Error())
		{
			IIC_SendOneByte((RegValue & 0xFF00) >> 8);
			IIC_RecvACK_Error();
			IIC_SendOneByte(RegValue & 0x00FF);
			WrRegError = IIC_RecvACK_Error();
		}
	}
	IIC_Stop();

	return !WrRegError;
}

void INA219_Init(unsigned char WAddree)
{
	INA219_WriteReg(WAddree,0x00, 0x399F);//16V FSR, GAIN = 1, 16 samples, Shunt and Bus, Continuous. 0x0667
	INA219_WriteReg(WAddree,0x05, 0x0C80);//Use INA219 EVM software to calculate a full-scale calibration value (initial calbration), and then compute the corrected full-scale calibration value based on measured current (second calbration). 
}

unsigned short INA219_GetBusVolt(unsigned char WAddree)
{
	unsigned short BusVoltRegVal = INA219_ReadReg(WAddree,0x02);
	if(BusVoltRegVal & 0x0001)								//Overflow
		return 0x0FA0;
	else
		return (BusVoltRegVal & 0xFFF8) >> 1;		//((BusVoltRegVal & 0xFFF8) >> 3)*4mV
}

unsigned short INA219_GetPower(unsigned char WAddree)
{
	unsigned short PowerRegVal = INA219_ReadReg(WAddree,0x03);
	return (PowerRegVal >> 1)*5;							//2.5mW/bit
}

unsigned short INA219_GetCurrent(unsigned char WAddree)
{
	unsigned short CurrentRegVal = INA219_ReadReg(WAddree,0x04);
	return CurrentRegVal ;								//0.125mA/bit
}