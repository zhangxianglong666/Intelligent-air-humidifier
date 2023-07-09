#ifndef __DHT_11_H__
#define __DHT_11_H__

void DHT_GPIO_Init(GPIOMode_TypeDef Mode);
uint8_t DHT_Start();
uint8_t DHT_Get_Byte_Data();
uint8_t DHT_Get_Temp_Humi_Data();
uint8_t DHT_Humi_Data1();
uint8_t DHT_Humi_Data2();
uint8_t DHT_Temp_Data1();
uint8_t DHT_Temp_Data2();

#endif