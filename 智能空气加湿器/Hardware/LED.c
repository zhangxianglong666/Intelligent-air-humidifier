#include "stm32f10x.h"                  // Device header
/**
  * @brief  LED初始化
  * @param  无
  * @retval  无
  */
void LED_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2);
}

/**
  * @brief  PA1口LED亮
  * @param  无
  * @retval  无
  */
void LED1_ON()
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
}

/**
  * @brief  PA1口LED灭
  * @param  无
  * @retval  无
  */
void LED1_OFF()
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
}

/**
  * @brief  PA1口LED亮灭交替
  * @param  无
  * @retval  无
  */
void LED1_Turn()
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1) == 1)
	{
		LED1_ON();
	}
	else if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1) == 0)
	{
		LED1_OFF();
	}
}

/**
  * @brief  PA2口LED亮
  * @param  无
  * @retval  无
  */
void LED2_ON()
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}

/**
  * @brief  PA2口LED灭
  * @param  无
  * @retval  无
  */
void LED2_OFF()
{
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
}

/**
  * @brief  PA2口LED亮灭交替
  * @param  无
  * @retval  无
  */
void LED2_Turn()
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2) == 1)
	{
		LED2_ON();
	}
	else if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2) == 0)
	{
		LED2_OFF();
	}
}
