/*
 * @Author: Yang Lixin
 * @Date: 2023-02-27 13:18:37
 * @LastEditors: [you name]
 * @LastEditTime: 2023-03-06 18:30:30
 * @Description: RCT6,mini  串口收发
 */

#include "stm32f10x.h"                  // Device header
#include "Serial.h"
#include "Delay.h"
#include "LED.h"
#include <string.h>

uint8_t RX_Data;

extern uint8_t TxPacket[4];
extern uint8_t RxPacket[4];
extern char RxText[4];

int main(void)
{
	int temp;
	Serial_Init();
	LED_Init();
	Serial_Printf("%d\r\n",123);
	Serial_Printf("你好\r\n");
	while (1)
	{
		if(Serial_GetRxFlag() == 1)
		{
			//led返了
			if(strcmp(RxText,"LED_on") == 0)
			{
				LED_TurnOn();
				Serial_SendString("LED_TurnOn_ok\r\n");
			}
			else if (strcmp(RxText,"LED_off") == 0)
			{
				LED_TurnOff();
				Serial_SendString("LED_TurnOff_ok\r\n");
			}
			else
			{
				temp = strcmp(RxText,"LED_off");
				Serial_SendString(RxText);
			}
		}
	}

}
	// 边接收边发送
	// while(1)
	// {
	// 	if(Serial_GetRxFlag() == 1)
	// 	{
	// 		TxPacket[0] = RxPacket[0];
	// 		TxPacket[1] = RxPacket[1];
	// 		TxPacket[2] = RxPacket[2];
	// 		TxPacket[3] = RxPacket[3];
	// 		Serial_SendPacket();
	// 	}
	// }

	// 发送
	// TxPacket[0] = 0xA0;
	// TxPacket[1] = 0xB1;
	// TxPacket[2] = 0xC2;
	// TxPacket[3] = 0xD3;

	// Serial_SendPacket();
	// while (1)
	// {}	
