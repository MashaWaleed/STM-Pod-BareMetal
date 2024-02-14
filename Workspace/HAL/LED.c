/*****************************< LIB *****************************/
#include "stm32f103x8.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/*****************************< MCAL *****************************/
#include "GPIO.h"
#include "STK_interface.h"
/*****************************< HAL *****************************/
#include "LED.h"
/*****************************< Function Implementations *****************************/
/**
 * @defgroup Public_Functions LED Driver
 * @{
 */

void HAL_LED_Init(LED_Port_t Copy_LedPortId, LED_Pin_t Copy_LedPinId)
{
    /**< Init LED to be output */
	GPIO_PinConfig_t cfg;
	cfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	cfg.GPIO_Output_Speed = GPIO_SPEED_2M;
	cfg.GPIO_PinNumber = Copy_LedPinId;
    MCAL_GPIO_Init(Copy_LedPortId, &cfg);
}

void HAL_LED_On(LED_Port_t Copy_LedPortId, LED_Pin_t Copy_LedPinId)
{
    MCAL_GPIO_WritePin(Copy_LedPortId, Copy_LedPinId, GPIO_PIN_SET);
}

void HAL_LED_Off(LED_Port_t Copy_LedPortId, LED_Pin_t Copy_LedPinId)
{
	MCAL_GPIO_WritePin(Copy_LedPortId, Copy_LedPinId, GPIO_PIN_RESET);
}

void HAL_LED_Toggle(LED_Port_t Copy_LedPortId, LED_Pin_t Copy_LedPinId)
{
	MCAL_GPIO_TogglePin(Copy_LedPortId, Copy_LedPinId);
}

//void HAL_LED_BlinkOnce(LED_Port_t Copy_LedPortId, LED_Pin_t Copy_LedPinId, LED_Delay_ms_t Copy_BlinkTime)
//{
//    if(MCAL_GPIO_SetPinValue(Copy_LedPortId, Copy_LedPinId, GPIO_HIGH) == E_NOT_OK)
//    {
//        E_NOT_OK;
//    }
//
//    if(MCAL_STK_SetDelay_ms(Copy_BlinkTime) == E_NOT_OK)
//    {
//        E_NOT_OK;
//    }
//
//    if(MCAL_GPIO_SetPinValue(Copy_LedPortId, Copy_LedPinId, GPIO_LOW) == E_NOT_OK)
//    {
//        E_NOT_OK;
//    }
//
//    E_OK;
//}
//
//void HAL_LED_BlinkTwice(LED_Port_t Copy_LedPortId, LED_Pin_t Copy_LedPinId, LED_Delay_ms_t Copy_BlinkTime)
//{
//    if(HAL_LED_BlinkOnce(Copy_LedPortId, Copy_LedPinId, Copy_BlinkTime) == E_NOT_OK)
//    {
//        E_NOT_OK;
//    }
//
//    MCAL_STK_SetDelay_ms(Copy_BlinkTime);
//
//    HAL_LED_BlinkOnce(Copy_LedPortId, Copy_LedPinId, Copy_BlinkTime);
//
//    E_OK;
//}

/**
 * @} // End of Public_Functions
 */
