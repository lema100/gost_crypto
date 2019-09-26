/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include "data_sets.h"
#include "tic33.h"
#include "magma.h"
#include "stribog.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

magma_ctx_t ctx_magma;
stribog_ctx_t ctx_stribog;

uint8_t result_enc[5][MAGMA_DATA_SIZE], result_dec[5][MAGMA_DATA_SIZE];
uint32_t local_time_enc, local_time_dec;
uint32_t local_time_mic_4, local_time_mic_2;
uint32_t local_time_hash512_63, local_time_hash256_63;
uint32_t local_time_hash512_72, local_time_hash256_72;
uint32_t local_time_hash512_32, local_time_hash256_32;
uint32_t fail;

char tic33_buf[100];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint8_t test(const uint8_t * data0, const uint8_t * data1, uint8_t len)
{
	uint8_t fail = 0;
	for (uint8_t i = 0; i < len; i++)
		if (data0[i] != data1[i])
			fail++;
	return fail;
}

uint8_t test_hash(stribog_ctx_t *ctx, const uint8_t * data)
{
	return test(ctx->h, data, ctx->size ? STRIBOG_OUTPUT_SIZE_512 : STRIBOG_OUTPUT_SIZE_256);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  LCD_Setup();
  Magma_Init(&ctx_magma, key);
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
/*
	Display overview
	local_time_enc			local_time_dec			1000 times
	local_time_mic_4		local_time_mic_2		1000 times
	local_time_hash512_63	local_time_hash256_63	100 times
	local_time_hash512_72	local_time_hash256_72	100 times
	local_time_hash512_32	local_time_hash256_32	100 times
*/

	fail = 0;
	local_time_enc = HAL_GetTick();
	for(uint16_t j = 0; j < 200; j++)
	{
		for(uint8_t i = 0; i < 5; i++)
		{
			Magma_ECB_enc(&ctx_magma, data[i]);
			memcpy(result_enc[i], ctx_magma.out, MAGMA_DATA_SIZE);
			fail += test(data_enc_test[i], ctx_magma.out, sizeof(ctx_magma.out));
		}
	}
	local_time_enc = HAL_GetTick() - local_time_enc;
	local_time_dec = HAL_GetTick();
	for(uint16_t j = 0; j < 200; j++)
	{
		for(uint8_t i = 0; i < 5; i++)
		{
			Magma_ECB_dec(&ctx_magma, result_enc[i]);
			memcpy(result_dec[i], ctx_magma.out, MAGMA_DATA_SIZE);
			fail += test(data[i], ctx_magma.out, sizeof(ctx_magma.out));
		}
	}
	local_time_dec = HAL_GetTick() - local_time_dec;

	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, fail ? GPIO_PIN_SET : GPIO_PIN_RESET);
	snprintf(tic33_buf, 10, "%ld %ld", local_time_enc, local_time_dec);
	LCD_string_TIC33(tic33_buf);

	fail = 0;
	local_time_mic_4 = HAL_GetTick();
	for(uint16_t j = 0; j < 1000; j++)
	{
		Magma_MIC(&ctx_magma, &data[1], 4, 0);
		fail += test(mic_test[0], ctx_magma.out, 4);
	}
	local_time_mic_4 = HAL_GetTick() - local_time_mic_4;

	local_time_mic_2 = HAL_GetTick();
	for(uint16_t j = 0; j < 1000; j++)
	{
		Magma_MIC(&ctx_magma, &data[1], 2, 0);
		fail += test(mic_test[1], ctx_magma.out, 4);
	}
	local_time_mic_2 = HAL_GetTick() - local_time_mic_2;

	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, fail ? GPIO_PIN_SET : GPIO_PIN_RESET);
	snprintf(tic33_buf, 10, "%ld %ld", local_time_mic_4, local_time_mic_2);
	LCD_string_TIC33(tic33_buf);

	fail = 0;
	local_time_hash512_63 = HAL_GetTick();
	for (uint8_t i = 0; i < 100; i++)
	{
		stribog_init(&ctx_stribog, STRIBOG_HASH512);
		stribog_calc(&ctx_stribog, message0, sizeof(message0));
		fail += test_hash(&ctx_stribog, message0_test[0]);
	}
	local_time_hash512_63 = HAL_GetTick() - local_time_hash512_63;

	local_time_hash256_63 = HAL_GetTick();
	for (uint8_t i = 0; i < 100; i++)
	{
		stribog_init(&ctx_stribog, STRIBOG_HASH256);
		stribog_calc(&ctx_stribog, message0, sizeof(message0));
		fail += test_hash(&ctx_stribog, message0_test[1]);
	}
	local_time_hash256_63 = HAL_GetTick() - local_time_hash256_63;

	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, fail ? GPIO_PIN_SET : GPIO_PIN_RESET);
	snprintf(tic33_buf, 10, "%ld %ld", local_time_hash512_63, local_time_hash256_63);
	LCD_string_TIC33(tic33_buf);

	fail = 0;
	local_time_hash512_72 = HAL_GetTick();
	for (uint8_t i = 0; i < 100; i++)
	{
		stribog_init(&ctx_stribog, STRIBOG_HASH512);
		stribog_calc(&ctx_stribog, message1, sizeof(message1));
		fail += test_hash(&ctx_stribog, message1_test[0]);
	}
	local_time_hash512_72 = HAL_GetTick() - local_time_hash512_72;

	local_time_hash256_72 = HAL_GetTick();
	for (uint8_t i = 0; i < 100; i++)
	{
		stribog_init(&ctx_stribog, STRIBOG_HASH256);
		stribog_calc(&ctx_stribog, message1, sizeof(message1));
		fail += test_hash(&ctx_stribog, message1_test[1]);
	}
	local_time_hash256_72 = HAL_GetTick() - local_time_hash256_72;

	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, fail ? GPIO_PIN_SET : GPIO_PIN_RESET);
	snprintf(tic33_buf, 10, "%ld %ld", local_time_hash512_72, local_time_hash256_72);
	LCD_string_TIC33(tic33_buf);


	local_time_hash512_32 = HAL_GetTick();
	for (uint8_t i = 0; i < 100; i++)
	{
		stribog_init(&ctx_stribog, STRIBOG_HASH512);
		stribog_calc(&ctx_stribog, key, sizeof(key));
	}
	local_time_hash512_32 = HAL_GetTick() - local_time_hash512_32;

	local_time_hash256_32 = HAL_GetTick();
	for (uint8_t i = 0; i < 100; i++)
	{
		stribog_init(&ctx_stribog, STRIBOG_HASH256);
		stribog_calc(&ctx_stribog, key, sizeof(key));
	}
	local_time_hash256_32 = HAL_GetTick() - local_time_hash256_32;

	snprintf(tic33_buf, 10, "%ld %ld", local_time_hash512_32, local_time_hash256_32);
	LCD_string_TIC33(tic33_buf);

	HAL_Delay(1000);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
