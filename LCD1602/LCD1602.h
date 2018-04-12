#ifndef __LCD1602_H__
#define __LCD1602_H__

#include "..\common\common.h"

sbit LCD_EN = P0^4;
sbit LCD_RW = P0^3;
sbit LCD_RS = P0^2;

#define INST_REG	0				//Instruction Register
#define DATA_REG	1				//Data Register
#define LCD_BUSY	LCD_ReadReg(INST_REG)>>7

void LCD_WriteReg(bit RegType, unsigned char RegValue);
unsigned char LCD_ReadReg(bit RegType);
void LCD_Init(void);
void SetCoordinate(unsigned char x, unsigned char y);
void PrintChar(unsigned char x, unsigned char y, unsigned char Character);
void PrintStr(unsigned char x, unsigned char y, unsigned char* Str);

#endif
	