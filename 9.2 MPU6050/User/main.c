/*
 * @Author: Yang Lixin
 * @Date: 2023-03-19 11:28:31
 * @LastEditors: [you name]
 * @LastEditTime: 2023-03-22 16:14:54
 * @Description: 
 */

#include "stm32f10x.h"                  // Device header
#include "OLED_4.h"
#include "Delay.h"
#include "MPU6050.h"

int16_t AccX,AccY,AccZ,GyroX,GyroY,GyroZ;
int main(void)
{

	OLED_Init();
	MPU6050_Init();

	//MPU6050_WriteByte(0x19,0xAB);//
	OLED_ShowString(1,1,"Acc    Gyro");
	DateStruct MPU6050_DateStruct;

	while(1)
	{
		MPU6050_DateStruct = MPU6050_GetDate();
		OLED_ShowSignedNum(2,1,MPU6050_DateStruct.AccX,5);
		OLED_ShowSignedNum(3,1,MPU6050_DateStruct.AccY,5);
		OLED_ShowSignedNum(4,1,MPU6050_DateStruct.AccZ,5);
		OLED_ShowSignedNum(2,8,MPU6050_DateStruct.GyroX,5);
		OLED_ShowSignedNum(3,8,MPU6050_DateStruct.GyroY,5);
		OLED_ShowSignedNum(4,8,MPU6050_DateStruct.GyroZ,5);
	}
}



