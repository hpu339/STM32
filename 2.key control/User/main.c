
/*
 * @Author: Yang Lixin
 * @Date: 2023-01-30 16:00:00
 * @LastEditors: [you name]
 * @LastEditTime: 2023-01-30 17:56:48
 * @Description: 加入延时函数
 */

#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Delay.h"
#include "Key.h"

int main(void)
{

	LED_Init();
	LED_TurnOn();
	Key_Init();
	while (1)
	{
		if(Key_IfPress() == 1)
		{
			LED_Reversal();
		}
	}
}
