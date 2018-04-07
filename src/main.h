/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include "stdbool.h"
/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/
#define uchar unsigned char
#define ushort unsigned short
#define uint unsigned int

#define LED_DIAG_Pin GPIO_PIN_13
#define LED_DIAG_GPIO_Port GPIOC
#define PCI_RST_Pin GPIO_PIN_14
#define PCI_RST_GPIO_Port GPIOC
#define PCI_WAKE_Pin GPIO_PIN_15
#define PCI_WAKE_GPIO_Port GPIOC
#define LED_FW_Pin GPIO_PIN_0
#define LED_FW_GPIO_Port GPIOF
#define LED_ACT_Pin GPIO_PIN_1
#define LED_ACT_GPIO_Port GPIOF
#define AIN12V_Pin GPIO_PIN_0
#define AIN12V_GPIO_Port GPIOA
#define AINCUR_Pin GPIO_PIN_1
#define AINCUR_GPIO_Port GPIOA
#define AIN1V8_Pin GPIO_PIN_2
#define AIN1V8_GPIO_Port GPIOA
#define AIN1V9_Pin GPIO_PIN_3
#define AIN1V9_GPIO_Port GPIOA
#define AIN1V0_Pin GPIO_PIN_4
#define AIN1V0_GPIO_Port GPIOA
#define REM_PWR_BTN_Pin GPIO_PIN_5
#define REM_PWR_BTN_GPIO_Port GPIOA
#define IR_IN_Pin GPIO_PIN_6
#define IR_IN_GPIO_Port GPIOA
#define SYS_PWR_Pin GPIO_PIN_7
#define SYS_PWR_GPIO_Port GPIOA
#define USB_VBUS_Pin GPIO_PIN_0
#define USB_VBUS_GPIO_Port GPIOB
#define HDMI_PWR_Pin GPIO_PIN_1
#define HDMI_PWR_GPIO_Port GPIOB
#define LEDIN_HDMI_Pin GPIO_PIN_2
#define LEDIN_HDMI_GPIO_Port GPIOB
#define VAL_RST_Pin GPIO_PIN_12
#define VAL_RST_GPIO_Port GPIOB
#define LEDIN_LINK_Pin GPIO_PIN_3
#define LEDIN_LINK_GPIO_Port GPIOB
#define FAN_TACH_Pin GPIO_PIN_4
#define FAN_TACH_GPIO_Port GPIOB
#define PWR_PULSE_Pin GPIO_PIN_5
#define PWR_PULSE_GPIO_Port GPIOB

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

#define LED_DIAG_ON HAL_GPIO_WritePin(LED_DIAG_GPIO_Port, LED_DIAG_Pin, GPIO_PIN_SET)
#define LED_DIAG_OFF HAL_GPIO_WritePin(LED_DIAG_GPIO_Port, LED_DIAG_Pin, GPIO_PIN_RESET)

#define LED_FW_ON HAL_GPIO_WritePin(LED_FW_GPIO_Port, LED_FW_Pin, GPIO_PIN_SET)
#define LED_FW_OFF HAL_GPIO_WritePin(LED_FW_GPIO_Port, LED_FW_Pin, GPIO_PIN_RESET)

#define LED_ACT_ON HAL_GPIO_WritePin(LED_ACT_GPIO_Port, LED_ACT_Pin, GPIO_PIN_SET)
#define LED_ACT_OFF HAL_GPIO_WritePin(LED_ACT_GPIO_Port, LED_ACT_Pin, GPIO_PIN_RESET)

extern ushort usLEDact;	//LED activity countdown
#define LEDACT usLEDact=10000

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
	 
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
