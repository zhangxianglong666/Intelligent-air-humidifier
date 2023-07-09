#include "stm32f10x.h"                  // Device header

void Timer_Init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_InternalClockConfig(TIM4);
	
	TIM_TimeBaseInitTypeDef TIM_TimBaseInitStructure;
	TIM_TimBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimBaseInitStructure.TIM_Period = 1000-1;
	TIM_TimBaseInitStructure.TIM_Prescaler = 72-1;
	TIM_TimBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimBaseInitStructure);

	TIM_ClearFlag(TIM4,TIM_FLAG_Update);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
	
//	TIM_Cmd(TIM4,ENABLE);
}

/*
void TIM4_IRQHandler()
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET)
	{
	
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	}
	
}
*/
