/*
 * @Author: Yang Lixin
 * @Date: 2023-01-30 16:00:00
 * @LastEditors: [you name]
 * @LastEditTime: 2023-01-30 17:55:39
 * @Description: 
 */
/*
 * @Author: Yang Lixin
 * @Date: 2023-01-30 15:57:37
 * @LastEditors: [you name]
 * @LastEditTime: 2023-01-30 17:55:36
 * @Description: 
 */

#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Delay.h"

int main(void)
{

	LED_Init();
	LED_TurnOn();
	while (1)
	{
		Delay_s(1);
		LED_TurnOff();
		Delay_s(1);
		LED_TurnOn();
	}
}
