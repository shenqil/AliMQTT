/**
  ******************************************************************************
  * File Name          : USART.h
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __usart_H
#define __usart_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include <stddef.h>


#define U1ReciLen    1024
#define MAX_TIMER_COUNTER  120
typedef struct{
	uint16_t TimeCounter;      // 超时时间
	bool     ReciDispose;      // 是否已经处理
	uint16_t MessageLen;       // 消息长度
	uint8_t ReciBuf[U1ReciLen+1];
}ReciMessage_Typ;
extern ReciMessage_Typ U1ReciMessage;
/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);

/* USER CODE BEGIN Prototypes */
void USARTInit(void);
void UART1_TestRecTimeOut(void);
void UART_SendFrame(uint8_t *pData, uint16_t Size);
void MQTTsendPacketBuffer(uint8_t *pData, uint16_t Size);
int MQTTgetData(unsigned char *buf , int bufLen,uint32_t timeout_ms);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
