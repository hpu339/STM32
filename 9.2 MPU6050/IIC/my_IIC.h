#ifndef _MY_IIC_H
#define _MY_IIC_H


void IIC_Start(void);
void IIC_Stop(void);
void IIC_Init(void);
void IIC_W_SCL(uint8_t value);
void IIC_W_SDA(uint8_t value);
void IIC_SendACK(uint8_t ACKBit);
void IIC_SendByte(uint8_t date);
uint8_t IIC_R_SCL(void);
uint8_t IIC_R_SDA(void);
uint8_t IIC_ReceiveByte(void);
uint8_t IIC_ReceiveACK(void);

#endif // !MY_IIC_H

