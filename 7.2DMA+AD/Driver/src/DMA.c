/*
 * @Author: Yang Lixin
 * @Date: 2023-02-10 00:33:46
 * @LastEditors: [you name]
 * @LastEditTime: 2023-02-10 17:39:52
 * @Description: 
 */
#include "stm32f10x.h"

uint16_t DMA_Size;
void DMA1_Init(uint32_t addrA,uint32_t addrB,uint32_t size)
{
    DMA_Size = size;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);//c8t6只有DMA1

    DMA_InitTypeDef DMA_InitStructure;   
    DMA_InitStructure.DMA_PeripheralBaseAddr = addrA;
    DMA_InitStructure.DMA_PeripheralDataSize =DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
    DMA_InitStructure.DMA_MemoryBaseAddr = addrB;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_BufferSize = size;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//
    DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;//是否内存到内存
    DMA_InitStructure.DMA_Mode =DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//优先级
    DMA_Init(DMA1_Channel1,&DMA_InitStructure);
    DMA_Cmd(DMA1_Channel1,DISABLE);//内存到内存，不需要外设，哪个通道都行

}
/**
 * @Author: Yang Lixin
 * @description: 数据传输函数
 * @return {*}
 */
void DMA1_Tranfer()
{
    DMA_Cmd(DMA1_Channel1,DISABLE);//先关闭才能传输
    DMA_SetCurrDataCounter(DMA1_Channel1,DMA_Size);
    DMA_Cmd(DMA1_Channel1,ENABLE);
    while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);//等待传输完成，完成为SET

    DMA_ClearFlag(DMA1_FLAG_TC1);
}


