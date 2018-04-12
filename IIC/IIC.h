#ifndef __IIC_H__
#define __IIC_H__

#include "..\common\common.h"

sbit SCL = P0^0;
sbit SDA = P0^1;

#define ACK 0
#define NACK 1

void IIC_Start(void);
void IIC_Stop(void);
void IIC_SendACK(bit ACK_Type);
bit IIC_RecvACK_Error(void);
void IIC_SendOneByte(unsigned char TxValue);
unsigned char IIC_RecvOneByte(void);

#endif /* __IIC_H__ */