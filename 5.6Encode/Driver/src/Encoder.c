/*
 * @Author: Yang Lixin
 * @Date: 2023-02-08 13:17:14
 * @LastEditors: [you name]
 * @LastEditTime: 2023-02-08 17:17:32
 * @Description: 
 */

#include "stm32f10x.h"

void Encoder_Init()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    /******************时基单元配置*******************************/
    TIM_TimeBaseInitTypeDef TIM_InitStructure;
    TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //不分频 72
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up; //计数模式
    TIM_InitStructure.TIM_Period = 65536-1;   
    TIM_InitStructure.TIM_Prescaler = 1-1; //不分频
    TIM_InitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3,&TIM_InitStructure);

    //TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    //TIM_InternalClockConfig(TIM3);//内部时钟中断配置

    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter = 0;
    //TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;后面重复
    //TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    //TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInit(TIM3,&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICFilter = 0;
    TIM_ICInit(TIM3,&TIM_ICInitStructure);
    
    TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
    //TIM_ICPolarity_Rising指的是高低电平极性不反转

    TIM_Cmd(TIM3,ENABLE);

}
int16_t Encoder_GetCount()
{
    return TIM_GetCounter(TIM3);
}
/**
 * @Author: Yang Lixin
 * @description: 每次调用一次返回脉冲个数并清理
 * @return {*}
 */
int16_t Encoder_GetSpeed()
{
    int16_t temp;
    temp = Encoder_GetCount();
    TIM_SetCounter(TIM3,0); //清零计数次数
    return temp; 
}



// void TIM2_IRQHandler()
// {
//     if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
//     {
//         TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//     }
// }


