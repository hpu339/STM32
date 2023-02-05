/*
 * @Author: Yang Lixin
 * @Date: 2023-02-05 23:53:49
 * @LastEditors: [you name]
 * @LastEditTime: 2023-02-06 00:51:04
 * @Description: 
 */


#include "stm32f10x.h"

#define encoder GPIO_Pin_0 | GPIO_Pin_1
uint16_t num = 0;
void Encoder_Init()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = encoder;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    //作用于外部中断
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);


    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line1;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStructure);

    //设置优先级分组：先占优先级和从优先级
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_InitStructure);

}

uint16_t Encoder_Get()
{
    uint16_t a;
    a = num;
    num = 0;
    return a;
}

void EXTI1_IRQHandler()
{
    if(EXTI_GetITStatus(EXTI_Line1) == SET) //A触发下降沿
    {
        if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 0)
        {
            if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)
            {
                num++;//顺时针
            }
        }
        EXTI_ClearITPendingBit(EXTI_Line1);                                                                                            
    }
}

void EXTI0_IRQHandler()
{
    if(EXTI_GetITStatus(EXTI_Line0 == SET)) //A触发下降沿
    {
        if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0)
        {
            if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==0)
            {
                num--;//顺时针
            }
        }
        EXTI_ClearITPendingBit(EXTI_Line0);                                                                                            
    }
}
