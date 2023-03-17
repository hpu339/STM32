/*
 * @Author: Yang Lixin
 * @Date: 2023-02-10 00:33:55
 * @LastEditors: [you name]
 * @LastEditTime: 2023-02-10 14:53:39
 * @Description: 
 */
#ifndef _DMA_H
#define _DMA_H

void DMA1_Init(uint32_t addrA,uint32_t addrB,uint32_t size);
void DMA1_Tranfer();

#endif
