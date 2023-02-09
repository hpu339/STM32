/*
 * @Author: Yang Lixin
 * @Date: 2023-02-07 16:19:34
 * @LastEditors: [you name]
 * @LastEditTime: 2023-02-07 21:14:27
 * @Description: 
 */
#include "stm32f10x.h"

void IC_TIM3Init()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    /******************时基单元配置*******************************/
    TIM_TimeBaseInitTypeDef TIM_InitStructure;
    TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //不分频 72
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up; //计数模式
    TIM_InitStructure.TIM_Period = 65536-1;   
    TIM_InitStructure.TIM_Prescaler = 72-1; //标准频率就是72M/72
    TIM_InitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3,&TIM_InitStructure);

    //TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    TIM_InternalClockConfig(TIM3);//内部时钟中断配置

    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter = 0;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    //TIM_ICInit(TIM3,&TIM_ICInitStructure);
    TIM_PWMIConfig(TIM3,&TIM_ICInitStructure);//pwmi模式

    TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);
    TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);

    TIM_Cmd(TIM3,ENABLE);

}
uint32_t IC_FreqGet()
{
    return (1000000 / (TIM_GetCapture1(TIM3) + 1));
    //标准频率除以N，
}
uint32_t IC_DutyGet()
{
    return (100 * (TIM_GetCapture2(TIM3) + 1) / (TIM_GetCapture1(TIM3) + 1));
}


// void TIM2_IRQHandler()
// {
//     if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
//     {
//         TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//     }
// }


