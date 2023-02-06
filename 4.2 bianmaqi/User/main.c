
/*
 * @Author: Yang Lixin
 * @Date: 2023-01-30 16:00:00
 * @LastEditors: [you name]
 * @LastEditTime: 2023-02-06 11:02:09
 * @Description: 编码器
 */

#include "stm32f10x.h"                  // Device header
#include "Encoder.h"
#include "OLED.h"

int main(void)
{
	int16_t a = 0;
	OLED_Init();
	Encoder_Init();
	OLED_ShowString(1,1,"count:");
	while (1)
	{
		a += Encoder_Get();
		OLED_ShowSignedNum(1,7,a,5);
	}
}
