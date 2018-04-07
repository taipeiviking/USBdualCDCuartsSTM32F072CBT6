/*
    DMA-accelerated multi-UART USB CDC for STM32F072 microcontroller

    Copyright (C) 2015,2016 Peter Lawrence

    Permission is hereby granted, free of charge, to any person obtaining a 
    copy of this software and associated documentation files (the "Software"), 
    to deal in the Software without restriction, including without limitation 
    the rights to use, copy, modify, merge, publish, distribute, sublicense, 
    and/or sell copies of the Software, and to permit persons to whom the 
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in 
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
    DEALINGS IN THE SOFTWARE.
*/

#include "stm32f0xx_hal.h"
#include "usbd_desc.h"
#include "usbd_composite.h" 
#include "usbd_cdc.h"
#include "main.h"

USBD_HandleTypeDef USBD_Device;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

ushort usLEDact=0;	//LED activity countdown
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void MX_GPIO_Init(void);

int main(void)
{
  /*
  With code compiled outside Rowley, I'm seeing the USB ISR fire between USBD_Init() and USBD_RegisterClass().
  Interrupts are enabled at reset, and ST's (mis)decision is to start enabling NVIC interrupts in USBD_Init().
  By disabling interrupts here, and enabling later when everything is ready, we avoid this race condition.
  */
  __disable_irq();

  /* STM32F0xx HAL library initialization */
  HAL_Init();
  
  /* configure the system clock to get correspondent USB clock source */
  SystemClock_Config();
	
	/* Initialize all configured peripherals */
  MX_GPIO_Init();
  
  //MX_USART1_UART_Init();

  //MX_USART3_UART_Init();
	
	
	//LED test
	LED_DIAG_OFF;	
	LED_FW_OFF;
	LED_ACT_OFF;
  
	//while(1);
	
	if(1)	//enable USB
	{
	
  /* Initialize Device Library */
  USBD_Init(&USBD_Device, &USBD_Desc, 0);
  
  /* to work within ST's drivers, I've written a special USBD_Composite class that then invokes several classes */
  USBD_RegisterClass(&USBD_Device, &USBD_Composite);

  /* Start Device Process */
  USBD_Start(&USBD_Device);
		
	}

  /* OK, only *now* it is OK for the USB interrupts to fire */
  __enable_irq();
  uchar ucLEDfw=0xf0; //FW-LED blinking pattern
  uchar ucLEDfwMask=0; //FW-LED blinking pattern mask
  uint usLEDfwTimer=0;
	

  LEDACT;	//trigger ACT LED once
	

  while (1)
  {
  //LED Service
		if(++usLEDfwTimer>=0x30000) 
		{
			//FW LED
			usLEDfwTimer=0;
			if(0==(ucLEDfwMask*=2))ucLEDfwMask=0x01;
			if(ucLEDfwMask&ucLEDfw)LED_FW_ON; else LED_FW_OFF;
			
			if(0)
			{
				static uint8_t c[]="$";
						
				HAL_UART_Transmit_DMA(huart[0], &c[0], 1);
				HAL_UART_Transmit_DMA(huart[1], &c[0], 1);
			}
			
		}
		
		//Activity LED
		if(usLEDact)
		{
			if(!--usLEDact)LED_ACT_OFF;
			else LED_ACT_ON;
		}	
  
    //__WFI();	//Wait for Interrupt
  }
}

static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct;
  static RCC_CRSInitTypeDef RCC_CRSInitStruct;

  /* Enable HSI48 Oscillator to be used as system clock source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
  HAL_RCC_OscConfig(&RCC_OscInitStruct); 
  
  /* Select HSI48 as USB clock source */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
  
  /* Select HSI48 as system clock source and configure the HCLK and PCLK1 clock dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI48;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;  
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);
  
  /*Configure the clock recovery system (CRS)**********************************/
  
  /*Enable CRS Clock*/
  __CRS_CLK_ENABLE(); 
  
  /* Default Synchro Signal division factor (not divided) */
  RCC_CRSInitStruct.Prescaler = RCC_CRS_SYNC_DIV1;
  
  /* Set the SYNCSRC[1:0] bits according to CRS_Source value */
  RCC_CRSInitStruct.Source = RCC_CRS_SYNC_SOURCE_USB;
  
  /* HSI48 is synchronized with USB SOF at 1KHz rate */
  RCC_CRSInitStruct.ReloadValue =  __HAL_RCC_CRS_CALCULATE_RELOADVALUE(48000000, 1000);
  RCC_CRSInitStruct.ErrorLimitValue = RCC_CRS_ERRORLIMIT_DEFAULT;
  
  /* Set the TRIM[5:0] to the default value*/
  RCC_CRSInitStruct.HSI48CalibrationValue = 0x20; 
  
  /* Start automatic synchronization */ 
  HAL_RCCEx_CRSConfig (&RCC_CRSInitStruct);
}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
	
	__GPIOC_CLK_ENABLE();	//__HAL_RCC_GPIOC_CLK_ENABLE();
  __GPIOF_CLK_ENABLE();	//__HAL_RCC_GPIOF_CLK_ENABLE();
  __GPIOA_CLK_ENABLE();	//__HAL_RCC_GPIOA_CLK_ENABLE();
  __GPIOB_CLK_ENABLE();	//__HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_DIAG_GPIO_Port, LED_DIAG_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, PCI_RST_Pin|PCI_WAKE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, LED_FW_Pin|LED_ACT_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(VAL_RST_GPIO_Port, VAL_RST_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : LED_DIAG_Pin PCI_RST_Pin PCI_WAKE_Pin */
  GPIO_InitStruct.Pin = LED_DIAG_Pin|PCI_RST_Pin|PCI_WAKE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;//GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_FW_Pin LED_ACT_Pin */
  GPIO_InitStruct.Pin = LED_FW_Pin|LED_ACT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;//GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : REM_PWR_BTN_Pin SYS_PWR_Pin */
  GPIO_InitStruct.Pin = REM_PWR_BTN_Pin|SYS_PWR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : USB_VBUS_Pin HDMI_PWR_Pin LEDIN_HDMI_Pin LEDIN_LINK_Pin 
                           FAN_TACH_Pin PWR_PULSE_Pin */
  GPIO_InitStruct.Pin = USB_VBUS_Pin|HDMI_PWR_Pin|LEDIN_HDMI_Pin|LEDIN_LINK_Pin 
                          |FAN_TACH_Pin|PWR_PULSE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : VAL_RST_Pin */
  GPIO_InitStruct.Pin = VAL_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;//GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(VAL_RST_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;//GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF1_USART2;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;//GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF0_IR;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}



