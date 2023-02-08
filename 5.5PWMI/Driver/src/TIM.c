/*
 * @Author: Yang Lixin
 * @Date: 2023-02-05 17:33:48
 * @LastEditors: [you name]
 * @LastEditTime: 2023-02-05 18:07:17
 * @Description: 
 */
#include "stm32f10x.h"


void TIM2_Init()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

    
    TIM_TimeBaseInitTypeDef TIM_InitStructure;
    TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //不分频 72
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_InitStructure.TIM_Period = 1000-1;   //100hZ
    TIM_InitStructure.TIM_Prescaler = 720-1;
    TIM_InitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2,&TIM_InitStructure);

    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM2,ENABLE);

}

// uint16_t TIM2_IRQHandler()
// {
//     if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
//     {
//         TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//     }
// }


