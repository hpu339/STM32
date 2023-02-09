/*
 * @Author: Yang Lixin
 * @Date: 2023-02-08 23:22:36
 * @LastEditors: [you name]
 * @LastEditTime: 2023-02-09 10:45:49
 * @Description:ADC,PA0口模拟输入 
 */

#include "stm32f10x.h"                  // Device header
#include "TIM.h"
#include "OLED.h"
#include "Delay.h"
#include "ADC.h"

uint16_t ADvalue,VolatgeInt,VolatgeFloat;
int main(void)
{
	OLED_Init();
	AD_Init();
	OLED_ShowString(1,1,"ADvalue:");//AD值
	OLED_ShowString(2,1,"Volatge:0.00V");//电压值
	while(1)
	{
		ADvalue = AD_GetValue();
		VolatgeInt = (float)ADvalue / 4095 * 3.3;//转换成小数
		VolatgeFloat = (uint16_t)(VolatgeInt * 100) % 100;//取余
		OLED_ShowNum(1,9,ADvalue,5);
		OLED_ShowNum(2,9,VolatgeInt,1);
		OLED_ShowNum(2,11,VolatgeFloat,2);
		Delay_ms(100);
	}
}
