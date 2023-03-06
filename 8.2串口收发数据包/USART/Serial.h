/*
 * @Author: Yang Lixin
 * @Date: 2023-02-27 13:25:06
 * @LastEditors: [you name]
 * @LastEditTime: 2023-03-06 17:14:27
 * @Description: 
 */
#ifndef _SERIAL_H
#define _SERIAL_H
#include <stdio.h>

// uint8_t TxPacket[4];
// uint8_t RxPacket[4];

void Serial_Init(void);
void Serial_SendByte(uint8_t data);
void Serial_SendArray(uint8_t *Array, uint16_t Length);
void Serial_SendString(char *String);
void Serial_SendPacket(void);
void Serial_SendNumber(uint32_t Number, uint8_t Length);
void Serial_Printf(char *format, ...);
int fputc(int ch, FILE *f);
uint32_t Serial_Pow(uint32_t X, uint32_t Y);
uint8_t Serial_GetRxFlag(void);
uint8_t Serial_GetRxData(void);


#endif

