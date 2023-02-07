/*
 * @Author: Yang Lixin
 * @Date: 2023-02-07 09:51:38
 * @LastEditors: [you name]
 * @LastEditTime: 2023-02-07 21:34:03
 * @Description: 
 */

#include "stm32f10x.h"                  // Device header
#include "PWMI.h"
#include "OLED.h"
#include "Delay.h"
#include "PWM.h"

int main(void)
{
	OLED_Init();
	PWM_TIM2Init();
	IC_TIM3Init();
	OLED_ShowString(1,1,"freq:00000Hz");
	OLED_ShowString(2,1,"pwm:00%");
	PWM_Set(50);
	PWM_FreqSet(72-1);//改成10khz
	while(1)
	{
		OLED_ShowNum(1,6,IC_FreqGet(),5);
		OLED_ShowNum(2,5,IC_DutyGet(),2);
		// Delay_ms(5000);
		
	}

}
