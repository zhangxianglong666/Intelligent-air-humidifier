#include "stm32f10x.h"                  // Device header
#include "Delay.h"

#define DHT_RCC_PORT RCC_APB2Periph_GPIOB
#define DHT_GPIO_PORT GPIOB
#define DHT_GPIO_PIN GPIO_Pin_13

uint8_t buffer[5];
/**
  * @brief  DHT11_GPIO初始化函数
  * @param  Mode：指定输入或输出模式
  * @return None
  */
void DHT_GPIO_Init(GPIOMode_TypeDef Mode)
{
	
	RCC_APB2PeriphClockCmd(DHT_RCC_PORT,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = Mode;
	GPIO_InitStructure.GPIO_Pin = DHT_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(DHT_GPIO_PORT,&GPIO_InitStructure);
	
	GPIO_SetBits(DHT_GPIO_PORT,DHT_GPIO_PIN);
}

/**
  * @brief  DHT11模块起始信号函数
  * @param  None
  * @return 1或0，标志起动信号成功与否
  */
uint8_t DHT_Start()
{
	DHT_GPIO_Init(GPIO_Mode_Out_PP);							//输出模式
	
	GPIO_ResetBits(DHT_GPIO_PORT,DHT_GPIO_PIN);		//输出20ms低电平后拉高
	Delay_ms(20);
	GPIO_SetBits(DHT_GPIO_PORT,DHT_GPIO_PIN);
	
	DHT_GPIO_Init(GPIO_Mode_IPU);					//输入模式
	Delay_us(20);
	
	if(!GPIO_ReadInputDataBit(DHT_GPIO_PORT,DHT_GPIO_PIN))
	{
		while(!GPIO_ReadInputDataBit(DHT_GPIO_PORT,DHT_GPIO_PIN));
		while(GPIO_ReadInputDataBit(DHT_GPIO_PORT,DHT_GPIO_PIN));
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
  * @brief  接收DHT11发送来8位的数据
  * @param  None
  * @return 返回接收到的8位数据
  */
uint8_t DHT_Get_Byte_Data()
{
	uint8_t temp=0;
	for(int i = 0; i < 8; i++)
	{
		//temp <<= 1;
		while(!GPIO_ReadInputDataBit(DHT_GPIO_PORT,DHT_GPIO_PIN));
		Delay_us(30);
		if(GPIO_ReadInputDataBit(DHT_GPIO_PORT,DHT_GPIO_PIN)){temp |= (0x80>>i);} 
		while(GPIO_ReadInputDataBit(DHT_GPIO_PORT,DHT_GPIO_PIN));
	}
	return temp;
}

/**
  * @brief  获取DHT11的温度湿度数据
  * @param  buffer[]：需要传入一个存储数据的数组
  * @return 返回数据校验是否正确 1：正确 0：失败
  */
uint8_t DHT_Get_Temp_Humi_Data()
{
	uint8_t i;
	if(DHT_Start())
	{
//		for(i=0;i<5;i++)
//		{
			buffer[0] = DHT_Get_Byte_Data();
			buffer[1] = DHT_Get_Byte_Data();
			buffer[2] = DHT_Get_Byte_Data();
			buffer[3] = DHT_Get_Byte_Data();
			buffer[4] = DHT_Get_Byte_Data();
//		}
		
		Delay_us(50);
	}
	if(buffer[0]+buffer[1]+buffer[2]+buffer[3] == buffer[4]) 
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

uint8_t DHT_Humi_Data1()
{
	if(DHT_Get_Temp_Humi_Data())
	{
		return buffer[0];
	}
}

uint8_t DHT_Humi_Data2()
{
	if(DHT_Get_Temp_Humi_Data())
	{
		return buffer[1];
	}
}

uint8_t DHT_Temp_Data1()
{
	if(DHT_Get_Temp_Humi_Data())
	{
		return buffer[2];
	}
}

uint8_t DHT_Temp_Data2()
{
	if(DHT_Get_Temp_Humi_Data())
	{
		return buffer[3];
	}
}
