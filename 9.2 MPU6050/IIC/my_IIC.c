/*
 * @Author: Yang Lixin
 * @Date: 2023-03-17 10:29:32
 * @LastEditors: [you name]
 * @LastEditTime: 2023-03-21 15:40:03
 * @Description: 
 */
#include "stm32f10x.h"
#include "Delay.h"
#include "my_IIC.h"

#define SCL GPIO_Pin_6
#define SDA GPIO_Pin_7
#define IIC_Port GPIOB

/**
 * @Author: Yang Lixin
 * @description: up or down SCL/SDA
 * @param {BitAction} value
 * @return {*}
 */
void IIC_W_SCL(uint8_t value)
{
    GPIO_WriteBit(IIC_Port,SCL,(BitAction)value);
    Delay_us(10);
}
void IIC_W_SDA(uint8_t value)
{
    GPIO_WriteBit(IIC_Port,SDA,(BitAction)value);
    Delay_us(10);
}
uint8_t IIC_R_SCL(void)
{
    uint8_t SCL_Value;
    SCL_Value = GPIO_ReadInputDataBit(IIC_Port,SCL);
    Delay_us(10);
    return SCL_Value;
}
uint8_t IIC_R_SDA(void)
{
    uint8_t SDA_Value;
    SDA_Value = GPIO_ReadInputDataBit(IIC_Port,SDA);
    Delay_us(10);
    return SDA_Value;
}


void IIC_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Pin = SCL | SDA;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    GPIO_SetBits(GPIOB, SCL | SDA);
}
/**
 * @Author: Yang Lixin
 * @description: SCL每次默认以低电平结束
 *
 */
void IIC_Start()
{
    IIC_W_SCL(1);
    IIC_W_SDA(1);
    IIC_W_SDA(0);//下降沿触发
    IIC_W_SCL(0);
}
void IIC_Stop()
{
    IIC_W_SDA(0);
    IIC_W_SCL(1);
    IIC_W_SDA(1);
}

void IIC_SendByte(uint8_t date)
{
    for(uint8_t i=0;i<8;i++)
    {
        IIC_W_SDA(date & (0x80>>i));//写入最高位
        IIC_W_SCL(1);//拉低SCL
        IIC_W_SCL(0);//拉低SCL
    }

}
uint8_t IIC_ReceiveByte(void)
{
    uint8_t date=0x00;
    IIC_W_SDA(1);//主机在接收数据之前，要先释放
    for(uint8_t i=0;i<8;i++)//只需要找到哪个位是1
    {
        IIC_W_SCL(1);//高电平读取
        if(IIC_R_SDA() == 1) 
        {
            date |= (0x80>>i);
        }
        IIC_W_SCL(0);//走过一个周期
    }
    return date;
}

void IIC_SendACK(uint8_t ACKBit)
{
    IIC_W_SDA(ACKBit);
    IIC_W_SCL(1);
    IIC_W_SCL(0);
}
uint8_t IIC_ReceiveACK(void)
{
    uint8_t ACKBit;
    IIC_W_SDA(1);//释放SDA
    IIC_W_SCL(1);//高电平读取
    ACKBit = IIC_R_SDA();
    IIC_W_SCL(0);
    return ACKBit;
}
