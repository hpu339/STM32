/*
 * @Author: Yang Lixin
 * @Date: 2023-02-06 22:55:23
 * @LastEditors: [you name]
 * @LastEditTime: 2023-02-06 23:37:36
 * @Description: 
 */

#include "stm32f10x.h"


void PWM_TIM2Init()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    
    TIM_TimeBaseInitTypeDef TIM_InitStructure;
    TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //不分频 72
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up; //计数模式
    TIM_InitStructure.TIM_Period = 100-1;   //1khz
    TIM_InitStructure.TIM_Prescaler = 720-1;
    TIM_InitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2,&TIM_InitStructure);

    //TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    TIM_InternalClockConfig(TIM2);//内部时钟中断配置

    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0; //CCR
    TIM_OC1Init(TIM2,&TIM_OCInitStructure);

    TIM_Cmd(TIM2,ENABLE);

}
void PWM_Set(uint16_t ccr)
{
    TIM_SetCompare1(TIM2,ccr);
}

// void TIM2_IRQHandler()
// {
//     if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
//     {
//         TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//     }
// }


