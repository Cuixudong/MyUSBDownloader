/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DIDIR_Pin GPIO_PIN_0
#define DIDIR_GPIO_Port GPIOC
#define SWDIR_Pin GPIO_PIN_1
#define SWDIR_GPIO_Port GPIOC
#define JTDI_Pin GPIO_PIN_2
#define JTDI_GPIO_Port GPIOC
#define SWDIO_Pin GPIO_PIN_3
#define SWDIO_GPIO_Port GPIOC
#define ETX_V_Pin GPIO_PIN_0
#define ETX_V_GPIO_Port GPIOA
#define USB_V_Pin GPIO_PIN_1
#define USB_V_GPIO_Port GPIOA
#define T_TX_Pin GPIO_PIN_5
#define T_TX_GPIO_Port GPIOA
#define T_RX_Pin GPIO_PIN_6
#define T_RX_GPIO_Port GPIOA
#define DCDCEN_Pin GPIO_PIN_4
#define DCDCEN_GPIO_Port GPIOC
#define CON5V_Pin GPIO_PIN_0
#define CON5V_GPIO_Port GPIOB
#define CON1833V_Pin GPIO_PIN_1
#define CON1833V_GPIO_Port GPIOB
#define LED1_Pin GPIO_PIN_10
#define LED1_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_11
#define LED2_GPIO_Port GPIOB
#define SDA_Pin GPIO_PIN_7
#define SDA_GPIO_Port GPIOC
#define SCL_Pin GPIO_PIN_8
#define SCL_GPIO_Port GPIOC
#define T_CS_Pin GPIO_PIN_9
#define T_CS_GPIO_Port GPIOC
#define SWCLK_Pin GPIO_PIN_12
#define SWCLK_GPIO_Port GPIOC
#define JTDO_Pin GPIO_PIN_2
#define JTDO_GPIO_Port GPIOD
#define T_O2_Pin GPIO_PIN_7
#define T_O2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
