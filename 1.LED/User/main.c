/*
 * @Author: Yang Lixin
 * @Date: 2023-01-30 14:58:21
 * @LastEditors: [you name]
 * @LastEditTime: 2023-02-12 16:59:09
 * @Description: 
 */
#include "stm32f10x.h"                  // Device header
#include "LED.h"

int main(void)
{

	LED_Init();
	LED_TurnOn();
	while (1)
	{
		
	}
}
