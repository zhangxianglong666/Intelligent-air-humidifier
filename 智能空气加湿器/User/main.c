#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "DHT11.h"
#include "Humidifier.h"
#include "Serial.h"
#include "AD.h"
#include "Encoder.h"
#include "Servo.h"
#include "Voice.h"

uint8_t VoiceValue;
uint8_t BuletoothValue;
uint8_t Encoder_Count;
uint8_t KeyNum;
uint16_t WaterValue;

void USART1_IRQHandler(void)  
{  
     if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)      //检查指定的 USART1 中断发生与否
      { 
			USART_ClearITPendingBit(USART1, USART_IT_RXNE);   //清除 USART1 的中断待处理位
			//GPIO_ResetBits(GPIOC,GPIO_Pin_6); 		  
			
			BuletoothValue=USART_ReceiveData(USART1);                    //返回 USART1 最近接收到的数据
	}
}

int main(void)
{
	Voice_Init();
	Servo_Init();
	Encoder_Init();
	AD_Init();
	Serial_Init();
	Humi_Init();
	OLED_Init();
	OLED_ShowString(1,1,"Humi:");
	OLED_ShowString(2,1,"Temp:");
	OLED_ShowString(3,1,"T_Value:");
	OLED_ShowChar(1,10,'%');
	OLED_ShowChar(3,12,'%');
	//OLED_ShowChar(2,10,'');

	while(1)
	{
		while(KeyNum==0)
		{
			WaterValue=AD_Getvalue();
			if(WaterValue<500)
			{
				Humi_OFF();
				Servo_SetAngle(90);
				
			}
			else if(WaterValue>1500)
			{
				if(DHT_Humi_Data1()<Encoder_Count)
				{	
					Humi_ON();
				}
				else
				{
					Humi_OFF();
				}
				Servo_SetAngle(0);
			}
			else if(WaterValue>=500 && WaterValue<=1500)
			{
				if(DHT_Humi_Data1()<Encoder_Count)
				{	
					Humi_ON();
				}
				else
				{
					Humi_OFF();
				}
			}
			OLED_ShowNum(1,7,DHT_Humi_Data1(),3);
			OLED_ShowNum(2,7,DHT_Temp_Data1(),3);
			OLED_ShowNum(3,9,Encoder_Count,3);
			OLED_ShowString(4,1,"Auto ");
			OLED_ShowNum(4,11,WaterValue,4);
		}
		while(KeyNum==1)
		{
			VoiceValue=Voice_GetRxData();
			WaterValue=AD_Getvalue();
			if(WaterValue<500)
			{
				Humi_OFF();
				Servo_SetAngle(90);
				
			}
			else if(WaterValue>1400)
			{
				if(VoiceValue==0x01)
				{
					Humi_ON();
				}
				else if(VoiceValue==0x4F)
				{
					Humi_OFF();
				}
				Servo_SetAngle(0);
			}
			else if(WaterValue>=500 && WaterValue<=1400)
			{
				if(VoiceValue==0x01)
				{
					Humi_ON();
				}
				else if(VoiceValue==0x4F)
				{
					Humi_OFF();
				}
			}
			
			OLED_ShowNum(1,7,DHT_Humi_Data1(),3);
			OLED_ShowNum(2,7,DHT_Temp_Data1(),3);
			OLED_ShowNum(3,9,Encoder_Count,3);
			//OLED_ShowHexNum(4,7,VoiceValue,2);
			OLED_ShowString(4,1,"Voice");
			OLED_ShowNum(4,11,WaterValue,4);
		}
		while(KeyNum==2)
		{
			WaterValue=AD_Getvalue();
			if(WaterValue<500)
			{
				Humi_OFF();
				Servo_SetAngle(90);
				if(BuletoothValue=='3')
				{
					Serial_SendByte(DHT_Humi_Data1());
				}
				
			}
			else if(WaterValue>1400)
			{
				if(BuletoothValue=='1')
				{
					Humi_ON();
				}
				else if(BuletoothValue=='2')
				{
					Humi_OFF();
				}
				else if(BuletoothValue=='3')
				{
					Serial_SendByte(DHT_Humi_Data1());
				}
				Servo_SetAngle(0);
			}
			else if(WaterValue>=500 && WaterValue<=1400)
			{
				if(BuletoothValue=='1')
				{
					Humi_ON();
				}
				else if(BuletoothValue=='2')
				{
					Humi_OFF();
				}
				else if(BuletoothValue=='3')
				{
					Serial_SendByte(DHT_Humi_Data1());
				}
			}
			
			OLED_ShowNum(1,7,DHT_Humi_Data1(),3);
			OLED_ShowNum(2,7,DHT_Temp_Data1(),3);
			OLED_ShowNum(3,9,Encoder_Count,3);
			OLED_ShowString(4,1,"Blue ");
			OLED_ShowNum(4,11,WaterValue,4);
		}
		
	}
}



void EXTI0_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
		{
			if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
			{
				Encoder_Count ++ ;
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void EXTI1_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line1) == SET)
	{
		
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
		{
			if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
			{
				Encoder_Count --;
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

void EXTI15_10_IRQHandler()
{
	if (EXTI_GetITStatus(EXTI_Line10) == SET)
	{
		
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10) == 0)
		{
			TIM_Cmd(TIM4,ENABLE);
			
		}
		EXTI_ClearITPendingBit(EXTI_Line10);
	}
}

void TIM4_IRQHandler()
{
	uint8_t ms;
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET)
	{
		ms++;
		if(ms==20)
		{
			
			TIM_Cmd(TIM4,DISABLE);
			
			KeyNum++;
			KeyNum%=3;
			
			
		}
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	}
	
}
