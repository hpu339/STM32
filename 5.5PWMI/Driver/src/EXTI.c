/*
 * @Author: Yang Lixin
 * @Date: 2023-02-06 11:16:27
 * @LastEditors: [you name]
 * @LastEditTime: 2023-02-06 19:05:51
 * @Description: 
 */
#include "stm32f10x.h"


void EXTI_TIM2Init()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    //选择ETR通过外部时钟模式1输入的时钟
    TIM_ETRClockMode1Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0x0f);
    
    TIM_TimeBaseInitTypeDef TIM_InitStructure;
    TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //不分频 72
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up; //计数模式
    TIM_InitStructure.TIM_Period = 10-1;   //100hZ
    TIM_InitStructure.TIM_Prescaler = 1-1;
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
uint16_t EXTI_CountGet()
{
    return TIM_GetCounter(TIM2);
}

// void TIM2_IRQHandler()
// {
//     if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
//     {
//         TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//     }
// }


