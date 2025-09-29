/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2025 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
void display7SEG(int num);
void update7SEG(int index);
void updateClockBuffer(void);
/* USER CODE BEGIN PFP */
void display7SEG(int num)
{
    const uint8_t mixi[10] = {0b1000000, 0b1111001, 0b0100100, 0b0110000,
                              0b0011001, 0b0010010, 0b0000010, 0b1111000, 0b0000000, 0b0010000};

    // Ensure num is between 0 and 9
    if (num < 0 || num > 9)
        return;

    // Write each bit of the pattern to the corresponding GPIO pin (PB0 to PB6)
    HAL_GPIO_WritePin(GPIOB, SEG0_Pin, (mixi[num] & (1 << 0)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, SEG1_Pin, (mixi[num] & (1 << 1)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, SEG2_Pin, (mixi[num] & (1 << 2)) ? GPIO_PIN_SET : GPIO_PIN_RESET); // Segment C (PB2)
    HAL_GPIO_WritePin(GPIOB, SEG3_Pin, (mixi[num] & (1 << 3)) ? GPIO_PIN_SET : GPIO_PIN_RESET); // Segment D (PB3)
    HAL_GPIO_WritePin(GPIOB, SEG4_Pin, (mixi[num] & (1 << 4)) ? GPIO_PIN_SET : GPIO_PIN_RESET); // Segment E (PB4)
    HAL_GPIO_WritePin(GPIOB, SEG5_Pin, (mixi[num] & (1 << 5)) ? GPIO_PIN_SET : GPIO_PIN_RESET); // Segment F (PB5)
    HAL_GPIO_WritePin(GPIOB, SEG6_Pin, (mixi[num] & (1 << 6)) ? GPIO_PIN_SET : GPIO_PIN_RESET); // Segment G (PB6)
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int timer0_counter = 0;
int timer0_flag = 0;
int TIMER_CYCLE = 10;
void setTimer0(int duration)
{
    timer0_counter = duration / TIMER_CYCLE;
    timer0_flag = 0;
}
void timer_run()
{
    if (timer0_counter > 0)
    {
        timer0_counter--;
        if (timer0_counter == 0)
            timer0_flag = 1;
    }
}

int timer1_counter = 0;
int timer1_flag = 0;
void setTimer1(int duration)
{
    timer1_counter = duration / TIMER_CYCLE;
    timer1_flag = 0;
}
void timer_run1()
{
    if (timer1_counter > 0)
    {
        timer1_counter--;
        if (timer1_counter == 0)
            timer1_flag = 1;
    }
}

int timer2_counter = 0;
int timer2_flag = 0;
void setTimer2(int duration)
{
    timer2_counter = duration / TIMER_CYCLE;
    timer2_flag = 0;
}
void timer_run2()
{
    if (timer2_counter > 0)
    {
        timer2_counter--;
        if (timer2_counter == 0)
            timer2_flag = 1;
    }
}

int timer3_counter = 0;
int timer3_flag = 0;
void setTimer3(int duration)
{
    timer3_counter = duration / TIMER_CYCLE;
    timer3_flag = 0;
}
void timer_run3()
{
    if (timer3_counter > 0)
    {
        timer3_counter--;
        if (timer3_counter == 0)
            timer3_flag = 1;
    }
}
const int MAX_LED = 4;
int index_led = 0;
int led_buffer[4] = {1, 5, 0, 8};
int hour = 15, minute = 8, second = 58;

void update7SEG(int index)
{
    HAL_GPIO_WritePin(GPIOA, EN0_Pin | EN1_Pin | EN2_Pin | EN3_Pin, GPIO_PIN_SET);
    switch (index)
    {
    case 0:
        HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_RESET);
        display7SEG(led_buffer[0]);
        break;
    case 1:
        HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_RESET);
        display7SEG(led_buffer[1]);
        break;
    case 2:
        HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_RESET);
        display7SEG(led_buffer[2]);
        break;
    case 3:
        HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_RESET);
        display7SEG(led_buffer[3]);
        break;
    default:
        break;
    }
}

/*-----------------------------------Exercise 5-----------------------------*/
void updateClockBuffer(void)
{
    int minChuc = minute / 10;
    int minDonVi = minute % 10;
    int hourChuc = hour / 10;
    int hourDonVi = hour % 10;

    led_buffer[0] = hourChuc;
    led_buffer[1] = hourDonVi;
    led_buffer[2] = minChuc;
    led_buffer[3] = minDonVi;
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
    MX_TIM2_Init();
    /* USER CODE BEGIN 2 */
    HAL_TIM_Base_Start_IT(&htim2);
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    setTimer0(1000);
    setTimer1(1000);
    setTimer2(250);
    setTimer3(500);
    while (1)
    {
        /* USER CODE END WHILE */
        /*----------------------------Exercise 5------------------------------*/
        //	    second++;
        //	    if (second >= 60){
        //	        second = 0;
        //	        minute++;
        //	    }
        //	    if(minute >= 60){
        //	        minute = 0;
        //	        hour++;
        //	    }
        //	    if(hour >=24){
        //	        hour = 0;
        //	    }
        //	    updateClockBuffer();
        //	    HAL_Delay(1000);

        /*---------------------------Exercise 7----------------------------*/
        if (timer3_flag == 1)
        {
            HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
            setTimer3(500);
        }
        if (timer0_flag == 1)
        {
            second++;
            if (second >= 60)
            {
                second = 0;
                minute++;
            }
            if (minute >= 60)
            {
                minute = 0;
                hour++;
            }
            if (hour >= 24)
            {
                hour = 0;
            }
            /* USER CODE BEGIN 3 */
            updateClockBuffer();
            setTimer0(1000);
        }
        if (timer1_flag == 1)
        {
            HAL_GPIO_TogglePin(GPIOA, DOT_Pin);
            setTimer1(1000);
        }
\*---------------------------------Exercise 8----------------------------------*\
        if (timer2_flag == 1)
        {
            update7SEG(index_led);
            index_led++;
            if (index_led >= MAX_LED)
            {
                index_led = 0;
            }
            setTimer2(250);
        }
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

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief TIM2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM2_Init(void)
{

    /* USER CODE BEGIN TIM2_Init 0 */

    /* USER CODE END TIM2_Init 0 */

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    /* USER CODE BEGIN TIM2_Init 1 */

    /* USER CODE END TIM2_Init 1 */
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 7999;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 9;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM2_Init 2 */

    /* USER CODE END TIM2_Init 2 */
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, DOT_Pin | LED_RED_Pin | EN0_Pin | EN1_Pin | EN2_Pin | EN3_Pin, GPIO_PIN_SET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin | SEG4_Pin | SEG5_Pin | SEG6_Pin, GPIO_PIN_SET);

    /*Configure GPIO pins : DOT_Pin LED_RED_Pin EN0_Pin EN1_Pin
                             EN2_Pin EN3_Pin */
    GPIO_InitStruct.Pin = DOT_Pin | LED_RED_Pin | EN0_Pin | EN1_Pin | EN2_Pin | EN3_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : SEG0_Pin SEG1_Pin SEG2_Pin SEG3_Pin
                             SEG4_Pin SEG5_Pin SEG6_Pin */
    GPIO_InitStruct.Pin = SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin | SEG4_Pin | SEG5_Pin | SEG6_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/* USER CODE BEGIN 4 */
// int counter = 100;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    timer_run();
    timer_run1();
    timer_run2();
    timer_run3();
    /*-------------------------Exercise 1----------------------*/
    //	if(htim->Instance == TIM2){
    //		static uint16_t counter = 0;
    //		static uint8_t state = 0;
    //		static uint16_t dot_toggle = 0;
    //		counter++;
    //
    //		if(counter >= 50){
    //			counter = 0 ;
    //			if(state == 0 ){
    //			HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_RESET);
    //			HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_SET);
    //
    //			display7SEG(1);
    //			state = 1;
    //			}
    //			else{
    //				HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_SET);
    //				HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_RESET);
    //
    //				display7SEG(2);
    //				state = 0;
    //			}
    //		}
    //	if(counter1 >= 100){
    //		counter1 = 0;
    //		HAL_GPIO_TogglePin(GPIOA,LED_RED_Pin);
    //		counter1++;
    //	 }
    //   }
    /*------------------------Exercise 2--------------------------*/
    //	if(htim->Instance == TIM2){
    //		static uint16_t counter = 0;
    //		static uint16_t dot_counter = 0;
    //		static uint8_t state = 0;
    //		counter++;
    //		dot_counter++;
    //
    //		if(dot_counter >= 100){
    //			HAL_GPIO_TogglePin(GPIOA, DOT_Pin);
    //			HAL_GPIO_TogglePin(GPIOA,LED_RED_Pin);
    //			dot_counter = 0;
    //		}
    //
    //		if(counter >= 50){
    //			counter = 0;
    //			HAL_GPIO_WritePin(GPIOA, EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin, GPIO_PIN_SET);
    //
    //			switch(state){
    //			case 0:
    //				HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_RESET);
    //				display7SEG(1);
    //				break;
    //
    //			case 1:
    //				HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_RESET);
    //				display7SEG(2);
    //				break;
    //
    //			case 2:
    //				HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_RESET);
    //				display7SEG(3);
    //				break;
    //
    //			case 3:
    //				HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_RESET);
    //				display7SEG(0);
    //				break;
    //			}
    //			state = (state + 1) % 4; //switch to the next 7seg
    //		}
    //	}
    /*-----------------------------Exercise 3---------------------------*/
    //	if(htim->Instance == TIM2){
    //		static uint16_t dot_counter = 0;
    //		update7SEG(index_led);
    //		index_led++;
    //		if(index_led >= MAX_LED){
    //			index_led = 0;1
    //		}
    //
    //		dot_counter++;
    //		if(dot_counter >= 100){
    //			HAL_GPIO_TogglePin(GPIOA, DOT_Pin);
    //			HAL_GPIO_TogglePin(GPIOA,LED_RED_Pin);
    //			dot_counter = 0;
    //		}
    //	}
    /*----------------------------Exercise 4-----------------------------*/
    //	if (htim->Instance == TIM2){
    //	    static uint16_t dot_counter = 0;
    //	    static uint16_t led_counter = 0;
    //
    //	    led_counter++;
    //	    if (led_counter >= 25){
    //	        update7SEG(index_led++);
    //	        if (index_led >= MAX_LED){
    //	            index_led = 0;
    //	        }
    //	        led_counter = 0;
    //	    }
    //
    //	    dot_counter++;
    //	    if (dot_counter >= 100){
    //	        HAL_GPIO_TogglePin(GPIOA, DOT_Pin);
    //	    	HAL_GPIO_TogglePin(GPIOA, LED_RED_Pin);
    //	        dot_counter = 0;
    //	    }
    //	}
    /*----------------------------------------------------------------------*/

    //	if(htim->Instance == TIM2){
    //		static uint16_t counter = 0;
    //		counter++;
    //		if(counter >= 100){
    //			HAL_GPIO_TogglePin(GPIOA, LED_RED_Pin);
    //			counter = 0;
    //		}
    //	}
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
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
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
