#include "common.h"

void Delay_us(unsigned short DelayCycle)//tDelay = (13+8*Cycle)*12/11.0592(us).
{
	while(DelayCycle)
		DelayCycle--;
}