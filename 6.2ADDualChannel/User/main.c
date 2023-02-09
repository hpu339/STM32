/*
 * @Author: Yang Lixin
 * @Date: 2023-02-08 23:22:36
 * @LastEditors: [you name]
 * @LastEditTime: 2023-02-09 12:04:27
 * @Description:ADC,PA0口模拟输入 
 */

#include "stm32f10x.h"                  // Device header
#include "TIM.h"
#include "OLED.h"
#include "Delay.h"
#include "ADC.h"

uint16_t AD0,AD1,AD2;
uint16_t ADvalue,VolatgeInt,VolatgeFloat;
int main(void)
{
	OLED_Init();
	AD_Init();
	OLED_ShowString(1,1,"AD0:");//AD值
	OLED_ShowString(2,1,"AD1:");//AD值
	OLED_ShowString(3,1,"AD2:");//AD值
	while(1)
	{
		AD0 = AD_GetValue(ADC_Channel_0);
		AD1 = AD_GetValue(ADC_Channel_1);
		AD2 = AD_GetValue(ADC_Channel_2);

		OLED_ShowNum(1,5,AD0,5);
		OLED_ShowNum(2,5,AD0,5);
		OLED_ShowNum(3,5,AD0,5);
		Delay_ms(100);
	}
}
