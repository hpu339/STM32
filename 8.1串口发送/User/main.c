/*
 * @Author: Yang Lixin
 * @Date: 2023-02-27 13:18:37
 * @LastEditors: [you name]
 * @LastEditTime: 2023-02-27 18:48:11
 * @Description: RCT6,mini  串口收发
 */

#include "stm32f10x.h"                  // Device header
#include "Serial.h"
#include "Delay.h"

uint8_t RX_Data;

int main(void)
{
	Serial_Init();
	Serial_Printf("%d\r\n",123);
	Serial_Printf("你好\r\n");
	while(1)
	{
		if(Serial_GetRxFlag() == 1)
		{
			RX_Data = Serial_GetRxData();
			Serial_SendByte(RX_Data);
		}
	}
}
