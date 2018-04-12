#ifndef __INA219_DRV_H__
#define __INA219_DRV_H__

#define INA219_RD_Operation 0x81
#define INA219_WR_Operation 0x80

unsigned short INA219_ReadReg(unsigned char WAddree,unsigned char RegBase);
bit INA219_WriteReg(unsigned char WAddree,unsigned char RegBase, unsigned short RegValue);
void INA219_Init(unsigned char WAddree);
unsigned short INA219_GetBusVolt(unsigned char WAddree);
unsigned short INA219_GetPower(unsigned char WAddree);
unsigned short INA219_GetCurrent(unsigned char WAddree);

#endif