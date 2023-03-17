/*
 * @Author: Yang Lixin
 * @Date: 2023-02-27 13:18:37
 * @LastEditors: C8T6 MPU6050
 * @LastEditTime: 2023-03-17 20:52:55
 * @Description: RCT6,mini  串口收发
 */

#include "stm32f10x.h"                  // Device header
#include "Serial.h"
#include "Delay.h"
#include "my_IIC.h"

uint8_t RX_Data;
int main(void)
{
	uint8_t ACK;
	Serial_Init();
	IIC_Init();
	IIC_Start();
	IIC_SendByte(0xD0);//1101 000 0(写入为0) 
	ACK = IIC_ReceiveACK();
	IIC_Stop();
	Serial_SendNumber(ACK,1);
	while(1)
	{

	}
}
