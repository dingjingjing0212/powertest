#include "LCD1602.h"

//(0, 0)--------------(15, 0)
//(0, 1)--------------(15, 1)

void LCD_WriteReg(bit RegType, unsigned char RegValue)
{
	LCD_RS = RegType;
	LCD_RW = 0;
	LCD_EN = 1;
	P2 = RegValue;
	LCD_EN = 0;
}

unsigned char LCD_ReadReg(bit RegType)
{
	unsigned char RegValue;

	LCD_RS = RegType;
	LCD_RW = 1;
	P2 = 0xFF;													//Write "1" before read.
	LCD_EN = 1;
	RegValue = P2;
	LCD_EN = 0;

	return RegValue;
}	

void LCD_Init(void)
{
	Delay_us(10000);										//Power on reset. No display.

	LCD_WriteReg(INST_REG, 0x38);
	Delay_us(4000);
	LCD_WriteReg(INST_REG, 0x38);
	Delay_us(80);
	LCD_WriteReg(INST_REG, 0x38);				//Set to 8-bit operation and select 2-line display line and 5 x 8 dot character font.

	while(LCD_BUSY);
	LCD_WriteReg(INST_REG, 0x08);				//Display off
	while(LCD_BUSY);
	LCD_WriteReg(INST_REG, 0x01);				//Display clear
	while(LCD_BUSY);
	LCD_WriteReg(INST_REG, 0x06);				//Entry mode set
	while(LCD_BUSY);
	LCD_WriteReg(INST_REG, 0x0C);				//Display on. Cursor off. Blinks off.
}


void SetCoordinate(unsigned char x, unsigned char y)
{//DB[7:0]-1aaaaaaa, 
	unsigned char RAM_Addr;

	if(y)
		RAM_Addr = x | 0xC0;							//aaaaaaa: 40H - 67H for the second line. 0x40 | 0x80 = 0xC0
	else
		RAM_Addr = x | 0x80;							//aaaaaaa: 00H - 27H for the first line.
	while(LCD_BUSY);
	LCD_WriteReg(INST_REG, RAM_Addr);		//Set display data RAM address
}

void PrintChar(unsigned char x, unsigned char y, unsigned char Character)
{
	if(x<16 && y<2)
	{
		SetCoordinate(x, y);
		while(LCD_BUSY);
		LCD_WriteReg(DATA_REG, Character);
	}
}

void PrintStr(unsigned char x, unsigned char y, unsigned char* Str)
{
	unsigned char Idx = 0;

	SetCoordinate(x, y);
	while(Str[Idx] != 0)
	{
		while(LCD_BUSY);
		LCD_WriteReg(DATA_REG, Str[Idx]);
		if(x + Idx < 15)
			Idx++;
		else
			break;
	}
}