/*
 * @Author: Yang Lixin
 * @Date: 2023-01-31 09:16:22
 * @LastEditors: [you name]
 * @LastEditTime: 2023-02-04 09:45:24
 * @Description: 用灰度传感器作红外传感器计数，采取外部中断
 */

#include "stm32f10x.h"
#include "Delay.h"

#define sensor GPIO_Pin_6
uint16_t count = 0;
void Counter_Init()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = sensor;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line6;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM2,ENABLE);

}

uint16_t Counter_Get()
{
    return count;
}

void EXTI9_5_IRQHandler()
{

    if(EXTI_GetITStatus(EXTI_Line6) == SET)
    {
        Delay_ms(10);
        if(GPIO_ReadInputDataBit(GPIOA,sensor) == 1)
        {
            count++;
            
        }     
        EXTI_ClearITPendingBit(EXTI_Line6);                                                                                            
    }
}
