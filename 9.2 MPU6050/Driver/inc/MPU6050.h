/*
 * @Author: Yang Lixin
 * @Date: 2023-03-19 11:28:29
 * @LastEditors: [you name]
 * @LastEditTime: 2023-03-22 14:47:43
 * @Description: 
 */
#ifndef _MPU6050_H
#define _MPU6050_H

/**********MPU6050寄存器地址*********/
#define	MPU6050_SMPLRT_DIV		0x19 //采样率分频
#define	MPU6050_CONFIG			0x1A //配置数字低通滤波器
#define	MPU6050_GYRO_CONFIG		0x1B //触发陀螺仪自检，配置陀螺仪量程范围
#define	MPU6050_ACCEL_CONFIG	0x1C //配置加速度计

#define	MPU6050_ACCEL_XOUT_H	0x3B //X轴加速度值高8位
#define	MPU6050_ACCEL_XOUT_L	0x3C //低8位
#define	MPU6050_ACCEL_YOUT_H	0x3D //.....
#define	MPU6050_ACCEL_YOUT_L	0x3E
#define	MPU6050_ACCEL_ZOUT_H	0x3F
#define	MPU6050_ACCEL_ZOUT_L	0x40
#define	MPU6050_TEMP_OUT_H		0x41 //温度
#define	MPU6050_TEMP_OUT_L		0x42
#define	MPU6050_GYRO_XOUT_H		0x43 //陀螺仪
#define	MPU6050_GYRO_XOUT_L		0x44
#define	MPU6050_GYRO_YOUT_H		0x45
#define	MPU6050_GYRO_YOUT_L		0x46
#define	MPU6050_GYRO_ZOUT_H		0x47
#define	MPU6050_GYRO_ZOUT_L		0x48

#define	MPU6050_PWR_MGMT_1		0x6B
#define	MPU6050_PWR_MGMT_2		0x6C
#define	MPU6050_WHO_AM_I		0x75

typedef struct datestruct
{
    int16_t AccX;
    int16_t AccY;
    int16_t AccZ;
    int16_t Temp;
    int16_t GyroX;
    int16_t GyroY;
    int16_t GyroZ;
}DateStruct,*pDateStruct;
void MPU6050_Init(void);
void MPU6050_WriteByte(uint8_t RegAddr,uint8_t Date);
//void MPU6050_GetDate(int16_t *AccX,int16_t *AccY,int16_t *AccZ,
//                        int16_t *GyroX,int16_t *GyroY,int16_t *GyroZ);
uint8_t MPU6050_ReadByte(uint8_t RegAddr);
//int16_t GetDate(uint8_t RegAddr);

DateStruct MPU6050_GetDate();
DateStruct MPU6050_DateProsess(DateStruct SourceDate);

#endif