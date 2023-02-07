/*
 * @Author: Yang Lixin
 * @Date: 2023-02-07 09:51:38
 * @LastEditors: [you name]
 * @LastEditTime: 2023-02-07 11:37:10
 * @Description: 
 */

#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "OLED.h"
#include "Delay.h"

int main(void)
{
	OLED_Init();
	Motor_Init();
	while (1)
	{
		Motor_Left();
		Delay_ms(5000);
		Motor_Right();
		Delay_ms(5000);
		Motor_Break();
		Delay_ms(5000);
	}
}
