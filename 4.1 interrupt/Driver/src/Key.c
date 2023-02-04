/*
 * @Author: Yang Lixin
 * @Date: 2023-01-30 18:02:26
 * @LastEditors: [you name]
 * @LastEditTime: 2023-01-30 19:05:22
 * @Description: 
 */
#include "stm32f10x.h"
#include "Delay.h"

#define key GPIO_Pin_5 
void Key_Init()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = key;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

}

/**
 * @Author: Yang Lixin
 * @description: 微动按键，按下松开算一次
 * @return {*}按键是否按下
 */
uint8_t Key_IfPress()
{
    uint8_t state = 0;
    if(GPIO_ReadInputDataBit(GPIOA,key) == 0)
    {
        Delay_ms(20);
        if(GPIO_ReadInputDataBit(GPIOA,key) == 0)
        {
            state = 1;
        }
    }
    return state;
}

