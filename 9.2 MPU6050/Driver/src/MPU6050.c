/*
 * @Author: Yang Lixin
 * @Date: 2023-03-19 11:28:29
 * @LastEditors: [you name]
 * @LastEditTime: 2023-03-22 16:12:39
 * @Description: 
 */
#include "stm32f10x.h"
#include "my_IIC.h"
#include "MPU6050.h"

#define MPU6050_add 0xD0

// typedef struct datestruct
// {
//     int16_t AccX;
//     int16_t AccY;
//     int16_t AccZ;
//     int16_t Temp;
//     int16_t GyroX;
//     int16_t GyroY;
//     int16_t GyroZ;
// }DateStruct,*pDateStruct;

DateStruct p = {0,0,0,0,0,0,0};

void MPU6050_Init(void)
{
    IIC_Init();
    MPU6050_WriteByte(MPU6050_PWR_MGMT_1,0x01);//
	MPU6050_WriteByte(MPU6050_PWR_MGMT_2,0x00);//
	MPU6050_WriteByte(MPU6050_SMPLRT_DIV,0x00);//
	MPU6050_WriteByte(MPU6050_CONFIG,0x06);
    MPU6050_WriteByte(MPU6050_GYRO_CONFIG,0x18);
    MPU6050_WriteByte(MPU6050_ACCEL_CONFIG,0x18);//满量程±16g
}

void MPU6050_WriteByte(uint8_t RegAddr,uint8_t Date)
{
    IIC_Start();
    IIC_SendByte(MPU6050_add);
    IIC_ReceiveACK();
    IIC_SendByte(RegAddr);
    IIC_ReceiveACK();
    IIC_SendByte(Date);
    IIC_ReceiveACK();
    IIC_Stop();
}

uint8_t MPU6050_ReadByte(uint8_t RegAddr)
{
    uint8_t Date;
    IIC_Start();
    IIC_SendByte(MPU6050_add);
    IIC_ReceiveACK();
    IIC_SendByte(RegAddr);
    IIC_ReceiveACK();

    IIC_Start();
    IIC_SendByte(MPU6050_add | 0x01);//
    IIC_ReceiveACK();
    Date = IIC_ReceiveByte();
    IIC_SendACK(1);//停止接收
    IIC_Stop();

    return Date;
}


DateStruct MPU6050_GetDate()
{
	uint8_t DateH,DateL;
    int16_t *temp = &p.AccX; //将结构体首地址给temp 
    for(uint8_t address = MPU6050_ACCEL_XOUT_H;address<MPU6050_GYRO_ZOUT_L;address+=2)
    {
        DateH = MPU6050_ReadByte(address);
        DateL = MPU6050_ReadByte(address+1);
        *temp = (DateH<<8) | DateL; //给结构体赋值
        temp++;
    }
    return p;
}





