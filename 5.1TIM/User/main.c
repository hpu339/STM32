/*
 * @Author: Yang Lixin
 * @Date: 2023-01-30 16:00:00
 * @LastEditors: [you name]
 * @LastEditTime: 2023-02-05 18:07:38
 * @Description: 内部定时器
 */

#include "stm32f10x.h"                  // Device header
#include "TIM.h"
#include "interrupt.h"
#include "OLED.h"

uint16_t num = 0;
int main(void)
{
	OLED_Init();
	TIM2_Init();
	OLED_ShowString(1,1,"count:");
	while (1)
	{
		OLED_ShowNum(1,7,num,3);
	}
}

void TIM2_IRQHandler()
{
    if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
    {
		num++;
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }
}
