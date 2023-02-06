/*
 * @Author: Yang Lixin
 * @Date: 2023-01-30 16:00:00
 * @LastEditors: [you name]
 * @LastEditTime: 2023-02-06 12:19:14
 * @Description: 内部定时器
 */

#include "stm32f10x.h"                  // Device header
#include "EXTI.h"
#include "OLED.h"
#include "Delay.h"

uint16_t num = 0;
int main(void)
{
	OLED_Init();
	EXTI_TIM2Init();
	OLED_ShowString(1,1,"num:");
	OLED_ShowString(2,1,"count:");
	while (1)
	{
		OLED_ShowNum(1,7,EXTI_CountGet(),3);//计数次数
		OLED_ShowNum(2,5,num,5);//满了进入中断次数
	}
}

void TIM2_IRQHandler()
{
    if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
    {
		num++;
		// if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 1)
		// {
		// 	num++;
		// }
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }
}
