
/*
 * @Author: Yang Lixin
 * @Date: 2023-01-30 16:00:00
 * @LastEditors: [you name]
 * @LastEditTime: 2023-02-04 10:31:29
 * @Description: 对射式红外传感器
 */

#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "interrupt.h"
#include "OLED.h"

int main(void)
{
	OLED_Init();
	Counter_Init();
	OLED_ShowString(1,1,"count:");
	while (1)
	{
		OLED_ShowNum(1,7,Counter_Get(),3);
	}
}
