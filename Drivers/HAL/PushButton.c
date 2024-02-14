/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 16 Sep 2023                *****************/
/******* Version   : 0.1                        *****************/
/******* File Name : PushButton_program.c       *****************/
/****************************************************************/

/*****************************< LIB *****************************/
#include <stdbool.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/*****************************< MCAL *****************************/
#include "GPIO.h"
#include "STK_interface.h"
/*****************************< HAL *****************************/
#include "PushButton.h"
/*****************************< Function Implementations *****************************/
/**
 * @defgroup Public_Functions LED Driver
 * @{
 */

Std_ReturnType HAL_PushButton_Init(PushButton_Port_t Copy_ButtonPortId, PushButton_Pin_t Copy_ButtonPinId, PushButton_State_t Copy_ActiveLevel)
{
	if (Copy_ActiveLevel != ACTIVE_HIGH && Copy_ActiveLevel != ACTIVE_LOW && Copy_ActiveLevel != FLOATING)
	{
		return E_NOT_OK; /**< Invalid pull-up/down configuration */
	}
	else
	{
		GPIO_PinConfig_t cfg;
		cfg.GPIO_PinNumber = Copy_ButtonPinId;
		cfg.GPIO_Output_Speed = GPIO_SPEED_2M;

		/**< Initialize Push Button to be input with pull-up or pull-down */
		if(Copy_ActiveLevel == ACTIVE_LOW)
		{
			cfg.GPIO_MODE = GPIO_MODE_INPUT_PU;
			MCAL_GPIO_Init(Copy_ButtonPortId, &cfg);
			return E_OK;

		}

		else if(Copy_ActiveLevel == ACTIVE_HIGH)
		{
			cfg.GPIO_MODE = GPIO_MODE_INPUT_PD;
			MCAL_GPIO_Init(Copy_ButtonPortId, &cfg);
			return E_OK;
		}


		else if(Copy_ActiveLevel == FLOATING)
		{
			cfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(Copy_ButtonPortId, &cfg);
			return E_OK;
		}
		else
		{
			return E_NOT_OK;
		}

	}
}

u8 HAL_PushButton_Read(PushButton_Port_t Copy_ButtonPortId, PushButton_Pin_t Copy_ButtonPinId, u32 numIterations)
{
	u8 Copy_ButtonState;
	/**< Start the SysTick timer */
	STK_Init(SYSTICK_RELOAD_VALUE); /**< Initialize SysTick with a suitable reload value. */
	STK_Start();

	/**< Variables to store button state */
	bool currentButtonState;
	bool lastButtonState;

	/**< Variables to track time for debounce */
	static u32 lastDebounceTime = 0;

	u32 stableCount = 0; /**< Count of stable readings */

	/**< Repeat the reading and debouncing for the specified number of iterations */
	for (u32 i = 0; i < numIterations; i++)
	{
		/**< Read the current button state */
		currentButtonState = MCAL_GPIO_ReadPin(Copy_ButtonPortId, Copy_ButtonPinId);


		u32 currentMillis = STK_GetElapsedCounts(); // Get the current time in milliseconds

		/**< Check if the button state has changed and is stable for the debounce delay */
		if (currentButtonState != lastButtonState)
		{
			/**< Update the last button state */
			lastButtonState = currentButtonState;

			/**< Update the last debounce time */
			lastDebounceTime = currentMillis;
		}

		/**< Check if the button state has been stable for the debounce delay */
		if ((currentMillis - lastDebounceTime) >= DEBOUNCE_DELAY_MS)
		{
			/**< Increment the stable count */
			stableCount++;

			/**< If the button state has been stable for a sufficient number of times, consider it stable */
			if (stableCount >= (numIterations-2))
			{
				/**< Assign the debounced button state to the output parameter */
				Copy_ButtonState = currentButtonState;
				return Copy_ButtonState;
			}
		}

		/**< Button state is not stable yet, return the previous state */
		Copy_ButtonState = lastButtonState;
	}

	return UNSTABLE_READ; /**< Button state not stable after the specified number of iterations */
}

/**
 * @} (End of Public_Functions) 
 */
