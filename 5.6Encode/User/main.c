/*
 * @Author: Yang Lixin
 * @Date: 2023-02-08 10:54:16
 * @LastEditors: [you name]
 * @LastEditTime: 2023-02-08 18:57:48
 * @Description: 
 */

#include "stm32f10x.h"                  // Device header
#include "TIM.h"
#include "OLED.h"
#include "Delay.h"
#include "Encoder.h"

int16_t speed;
int main(void)
{
	OLED_Init();
	Encoder_Init();
	TIM2_Init();
	OLED_ShowString(1,1,"count:");
	OLED_ShowString(2,1,"speed:");
	while(1)
	{
		OLED_ShowSignedNum(1,7,Encoder_GetCount(),5);
		OLED_ShowSignedNum(2,7,speed,5);
		// OLED_ShowNum(2,5,IC_DutyGet(),2);
		// Delay_ms(5000);
		
	}

}

void TIM2_IRQHandler()
{
    if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
    {
		speed = Encoder_GetSpeed(); //1s进一次中断，获取一次脉冲次数
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }
}