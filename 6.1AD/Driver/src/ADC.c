/*
 * @Author: Yang Lixin
 * @Date: 2023-02-09 00:22:27
 * @LastEditors: [you name]
 * @LastEditTime: 2023-02-09 10:43:06
 * @Description: 
 */
#include "stm32f10x.h"


void AD_Init()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //模拟输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//单通道
    ADC_InitStructure.ADC_NbrOfChannel = 1;//通道数目个数
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;//扫描模式
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//连续转换
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//数据对齐
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//外部触发---内部
    ADC_Init(ADC1,&ADC_InitStructure);

    ADC_Cmd(ADC1,ENABLE);

    ADC_ResetCalibration(ADC1);//复位校准寄存器
    while(ADC_GetResetCalibrationStatus(ADC1));//检测是复位完毕(复位完硬件清0)
    ADC_StartCalibration(ADC1);//开启校准
    while(ADC_GetCalibrationStatus(ADC1));//检测是否校准完毕(校准完硬件清0)

}

uint16_t AD_GetValue()
{
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);//启动转换
    while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);//检测EOC标志位是被清01
    return ADC_GetConversionValue(ADC1);

}