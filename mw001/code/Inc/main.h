/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

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
#define BUZZ_Pin GPIO_PIN_0
#define BUZZ_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_1
#define LED1_GPIO_Port GPIOC
#define LED2_Pin GPIO_PIN_2
#define LED2_GPIO_Port GPIOC
#define LED3_Pin GPIO_PIN_3
#define LED3_GPIO_Port GPIOC
#define J1_EN_Pin GPIO_PIN_0
#define J1_EN_GPIO_Port GPIOA
#define J2_EN_Pin GPIO_PIN_1
#define J2_EN_GPIO_Port GPIOA
#define J2_T_Pin GPIO_PIN_2
#define J2_T_GPIO_Port GPIOA
#define J1_T_Pin GPIO_PIN_3
#define J1_T_GPIO_Port GPIOA
#define IIC_SDA_Pin GPIO_PIN_4
#define IIC_SDA_GPIO_Port GPIOA
#define IIC_SCK_Pin GPIO_PIN_5
#define IIC_SCK_GPIO_Port GPIOA
#define NTC_ADC_Pin GPIO_PIN_6
#define NTC_ADC_GPIO_Port GPIOA
#define BAT_ADC_Pin GPIO_PIN_7
#define BAT_ADC_GPIO_Port GPIOA
#define OTA_EN_Pin GPIO_PIN_12
#define OTA_EN_GPIO_Port GPIOB
#define UVA_EN_Pin GPIO_PIN_13
#define UVA_EN_GPIO_Port GPIOB
#define OVA_EN_Pin GPIO_PIN_14
#define OVA_EN_GPIO_Port GPIOB
#define ST1_Pin GPIO_PIN_11
#define ST1_GPIO_Port GPIOC
#define ST2_Pin GPIO_PIN_12
#define ST2_GPIO_Port GPIOC
#define ST3_Pin GPIO_PIN_2
#define ST3_GPIO_Port GPIOD
#define LCD_RS_Pin GPIO_PIN_3
#define LCD_RS_GPIO_Port GPIOB
#define LCD_SCK_Pin GPIO_PIN_4
#define LCD_SCK_GPIO_Port GPIOB
#define LCD_SDA_Pin GPIO_PIN_5
#define LCD_SDA_GPIO_Port GPIOB
#define LCD_RES_Pin GPIO_PIN_6
#define LCD_RES_GPIO_Port GPIOB
#define LCD_CS_Pin GPIO_PIN_7
#define LCD_CS_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
