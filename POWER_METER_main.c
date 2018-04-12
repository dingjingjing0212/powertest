#include "LCD1602\LCD1602.h"
#include "INA219_DRV\INA219_DRV.h"
#include "common\common.h"
	
#define TH0_VALUE 0x4B
#define TL0_VALUE 0xFF										//50ms per cycle.

sbit BtnRefreshMode = P3^2;
bit RefreshRate = 0;											//0: 0.8s, 1: 0.5s
bit RefreshFlag = 0;

/*******延时函数*************/
void delay(unsigned int i)
{
    unsigned char j;
    for(i; i > 0; i--)   
        for(j = 255; j > 0; j--);
}

void send_char_com( unsigned char ch) 
 {  ES=0;
 	TI=0;
 	SBUF=ch; 
  	while (!TI );
    TI= 0 ;
	 ES=1 ;
	}  

void RefreshData(unsigned char WAddree)
{
//	unsigned short BusVolt, Current, Power;
//	unsigned short OffsetCurrent, OffsetPower;
	unsigned short AfterCurrent, Current		;
//	BusVolt = INA219_GetBusVolt(WAddree);
//	PrintChar(0, 0, BusVolt/10000+48);
//	PrintChar(1, 0, (BusVolt%10000)/1000+48);
//	PrintChar(3, 0, (BusVolt%1000)/100+48);
//	PrintChar(4, 0, (BusVolt%100)/10+48);
//	PrintChar(5, 0, BusVolt%10+48);
		
//	OffsetCurrent = (BusVolt >> 9) + 2;			//Gather statistics of the measured current under various voltage conditions when no load is connected to the output port. Use Excel to do curve fitting.
	Current = INA219_GetCurrent(WAddree);
	AfterCurrent=Current;
		send_char_com(0x00EF) ;
	send_char_com(WAddree) ;
	send_char_com((AfterCurrent & 0xFF00) >> 8) ;
		send_char_com(AfterCurrent & 0x00FF) ;
		P1  = 0x00; //置P0口为低电平 
//	  delay(30);
  P1  = 0xff; //置P0口为高电平
 //delay(30);
//	if(Current > OffsetCurrent)
//		Current -= OffsetCurrent;
//	else
//		Current = 0;
//	PrintChar(10, 0, Current/1000+48);
//	PrintChar(12, 0, (Current%1000)/100+48);
//	PrintChar(13, 0, (Current%100)/10+48);
//	PrintChar(14, 0, Current%10+48);
		
//	OffsetPower = ((BusVolt >> 3) * OffsetCurrent)/125 + 6;
//	Power = INA219_GetPower(WAddree);
//	if(Power > OffsetPower)
//		Power -= OffsetPower;
//	else
//		Power = 0;
//	PrintChar(0, 1, Power/10000+48);
//	PrintChar(1, 1, (Power%10000)/1000+48);
//	PrintChar(3, 1, (Power%1000)/100+48);
//	PrintChar(4, 1, (Power%100)/10+48);
//	PrintChar(5, 1, Power%10+48);
}

int main(void)
{	  
	INA219_Init(0x80);
	INA219_Init(0x8a);
	SCON = 0x50; //串口方式1,允许接收
	TMOD = 0x20; //定时器1定时方式2
	PCON=0x00;   //cup正常工作
	TCON = 0x50; //设定时器1开始计数
	TH1 = 0xfd; // 9600 11.0592MHz 1200波特率e8
	TL1 = 0xfd;
	TI = 1;//发送数据标志
	TR1 =1; //启动定时器1
	ES=1;
//	LCD_Init();
	
//	TMOD &= 0xF0;
//	TMOD |= 0x01;										//Timer 0 works in Mode 1 (16-bit Timer).

//	TH0 = TH0_VALUE;
//	TL0 = TL0_VALUE;
	
//	PrintChar(2, 0, '.');
//	PrintChar(6, 0, 'V');
//	PrintChar(11, 0, '.');
//	PrintChar(15, 0, 'A');
//	PrintChar(2, 1, '.');
//	PrintChar(6, 1, 'W');
//	PrintStr(10, 1, "R:0.8s");
	RefreshData(0x80);
		RefreshData(0x8a);
	
//	EA = 1;													//Global Interrupt Enable
//	ET0 = 1;												//Timer 0 Interrupt Enable
//	TR0 = 1;												//Enable Timer 0.
	
	while(1)
	{		 
		if(1)
		{
			RefreshData(0x80);
			RefreshData(0x8a);
			RefreshFlag = 0;
		
		}
		
	//	if(BtnRefreshMode == 0)				//If the refreshing-mode button is pressed
	//	{
	//		Delay_us(5000);
	//		if(BtnRefreshMode == 1)
	//		{
	//			Delay_us(5000);						//Debouncing
	//			if(BtnRefreshMode == 1)
	//			{
	//				RefreshRate= !RefreshRate;
	//				if(RefreshRate)
	//					PrintChar(14, 1, '5');
//					else
	//					PrintChar(14, 1, '8');
	//			}
	//		}
	//	}
	}

	return 0;
}

//void Timer0ISR(void) interrupt 1 using 2
//{
//	static unsigned char Counter = 0;

//	TH0 = TH0_VALUE;
//	TL0 = TL0_VALUE;
	
//	if(Counter < 15-6*RefreshRate)	//Approximately 0.8s for slow-refreshing mode and 0.5s for fast-refreshing mode
//		Counter++;
//	else
//	{
//		Counter = 0;
//		RefreshFlag = 1;
//	}
//}