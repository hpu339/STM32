/*
 * @Author: Yang Lixin
 * @Date: 2023-02-27 13:24:49
 * @LastEditors: [you name]
 * @LastEditTime: 2023-03-06 18:28:17
 * @Description: 
 */
#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>

uint8_t R_Data;//接收数据
uint8_t R_Flag;//接收标志位

uint8_t TxPacket[4];
uint8_t RxPacket[4]; //FF .........FE
uint8_t RxState = 0;

char RxText[20];//20byte的字符串  @.......\r\n

void Serial_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1,&USART_InitStructure);
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART1,ENABLE);
}
/**
 * @Author: Yang Lixin
 * @description: 串口发送字节，一byte
 * @param {uint8_t} data
 * @return {*}
 */
void Serial_SendByte(uint8_t data)
{
    USART_SendData(USART1,data);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}

/**
 * @Author: Yang Lixin
 * @description: 串口发送数组
 * @param {uint8_t} *Array
 * @param {uint16_t} Length
 * @return {*}
 */
void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
	uint16_t i;
	for (i = 0; i < Length; i ++)
	{
		Serial_SendByte(Array[i]);
	}
}

/**
 * @Author: Yang Lixin
 * @description: 串口发送字符串
 * @param {char} *String
 * @return {*}
 */
void Serial_SendString(char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++)
	{
		Serial_SendByte(String[i]);
	}
}
/**
 * @Author: Yang Lixin
 * @description: 10的几次方
 * @param {uint32_t} X
 * @param {uint32_t} Y
 * @return {*}
 */
uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y --)
	{
		Result *= X;
	}
	return Result;
}
/**
 * @Author: Yang Lixin
 * @description: 串口发送数字
 * @param {uint32_t} Number
 * @param {uint8_t} Length
 * @return {*}
 */
void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i ++)
	{
		Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
	}
}
//printf重定向,重定向到一个串口
int fputc(int ch, FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}

void Serial_Printf(char *format, ...)
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Serial_SendString(String);
}

/**
 * @Author: Yang Lixin
 * @description: 串口接收标志位
 * @return {*}
 */
uint8_t Serial_GetRxFlag(void)
{
	if (R_Flag == 1)
	{
		R_Flag = 0;
		return 1;
	}
	return 0;
}

uint8_t Serial_GetRxData(void)
{
	return R_Data;
}

void Serial_SendPacket()
{
    //Serial_SendByte(0xFF);//帧头
    Serial_SendArray(TxPacket,4);
    //Serial_SendByte(0xFE);//帧尾
}
/**
 * @Author: Yang Lixin
 * @description: 单字节接收中断
 * @return {*}
 */
// void USART1_IRQHandler(void)
// {
//     if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)//有数据输入
//     {
//         R_Data = USART_ReceiveData(USART1);
//         R_Flag = 1;//接收完毕
//         USART_ClearITPendingBit(USART1,USART_IT_RXNE);
//     }
// }

/**
 * @Author: Yang Lixin
 * @description: HEX数据包接收中断
 * @return {*}
 */
// void USART1_IRQHandler(void)
// {
//     static uint8_t p=0;//初始化一次
//     if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)//有数据输入
//     {
//         R_Data = USART_ReceiveData(USART1);//接收数据
//         if(RxState == 0)
//         {
//             if(R_Data == 0xFF)//是否是帧头
//             {
//                 RxState = 1;
//             }
//         }
//         else if (RxState == 1)
//         {
//             RxPacket[p] = R_Data;
//             p++;
//             if(p >= 4) RxState = 2;
//         }
//         else if(RxState == 2)
//         {
//             if(R_Data == 0xFE) RxState = 0;
//             R_Flag = 1;
//             p = 0;
//         }
//         USART_ClearITPendingBit(USART1,USART_IT_RXNE);//每传输一个字节，清楚一下标志位，等待下次进入中断
//     }
// }

/**
 * @Author: Yang Lixin
 * @description: 文本数据包接收中断
 * @return {*}
 */
void USART1_IRQHandler(void)
{
    static uint8_t p=0;//初始化一次
    if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)//有数据输入
    {
        R_Data = USART_ReceiveData(USART1);//接收数据
        if(RxState == 0)
        {
            if(R_Data == '@')//是否是帧头
            {
                RxState = 1;
            }
        }
        else if (RxState == 1)
        {
            if(R_Data == '\r') 
            {
                RxState = 2;
            }
            else
            {
                RxText[p] = R_Data;
                p++;
            }
        }
        else if(RxState == 2)
        {
            if(R_Data == '\n') 
            {
                RxState = 0;
                R_Flag = 1;//接收完毕
                RxText[p] = '\0'; //结尾标志
                p = 0;
            }
        }
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);//每传输一个字节，清楚一下标志位，等待下次进入中断
    }
}
