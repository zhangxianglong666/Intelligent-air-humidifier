#include "stm32f10x.h"  // Device header


#define Humi_RCC_PORT RCC_APB2Periph_GPIOA
#define Humi_GPIO_PORT GPIOA 
#define Humi_GPIO_PIN GPIO_Pin_12


void Humi_Init()
{
	RCC_APB2PeriphClockCmd(Humi_RCC_PORT,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = Humi_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Humi_GPIO_PORT,&GPIO_InitStructure);
}

void Humi_ON()
{
	GPIO_SetBits(Humi_GPIO_PORT,Humi_GPIO_PIN);
}

void Humi_OFF()
{
	GPIO_ResetBits(Humi_GPIO_PORT,Humi_GPIO_PIN);
}
