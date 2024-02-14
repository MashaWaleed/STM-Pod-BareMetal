#ifndef LED_H_
#define LED_H_

/****************************************************************
 *                     Configuration Section                    *
 ****************************************************************/



/****************************************************************
 *                 End of Configuration Section                 *
 ****************************************************************/

/****************************************************************
 *                     Interface Section                        *
 ****************************************************************/

/**
 * @addtogroup LED_Parameters Interface Parameters
 * @{
 */

/**
 * @brief LED Port Enumeration
 *
 * Enumeration of available LED ports.
 */
#define LED_Port_t  GPIO_TypeDef *
#define LED_PORTA   GPIOA
#define LED_PORTB   GPIOB
#define LED_PORTC   GPIOC



/**
 * @brief LED Pin Enumeration
 *
 * Enumeration of available LED pins.
 */
#define LED_Pin_t    uint16_t
#define LED_PIN_0    GPIO_PIN_0
#define LED_PIN_1    GPIO_PIN_1
#define LED_PIN_2    GPIO_PIN_2
#define LED_PIN_3    GPIO_PIN_3
#define LED_PIN_4    GPIO_PIN_4
#define LED_PIN_5    GPIO_PIN_5
#define LED_PIN_6    GPIO_PIN_6
#define LED_PIN_7    GPIO_PIN_7
#define LED_PIN_8    GPIO_PIN_8
#define LED_PIN_9    GPIO_PIN_9
#define LED_PIN_10   GPIO_PIN_10
#define LED_PIN_11   GPIO_PIN_11
#define LED_PIN_12   GPIO_PIN_12
#define LED_PIN_13   GPIO_PIN_13
#define LED_PIN_14   GPIO_PIN_14
#define LED_PIN_15   GPIO_PIN_15


/**
 * @brief LED Delay in Milliseconds Type
 *
 * Type definition for LED delay in milliseconds.
 */
typedef u32 LED_Delay_ms_t;

/**
 * @} (LED_Parameters)
 */


/**
 * @defgroup LED_Functions LED Functions
 * @{
 */

/**
 * @brief Initialize an LED
 *
 * Initializes the specified LED pin for output.
 *
 * @param[in] Copy_LedPortId The ID of the LED port.
 * @param[in] Copy_LedPinId The ID of the LED pin.
 * @return Std_ReturnType Returns E_OK if initialization is successful, or E_NOT_OK if an error occurs.
 */
void HAL_LED_Init(LED_Port_t Copy_LedPortId, LED_Pin_t Copy_LedPinId);

/**
 * @brief Turn On an LED
 *
 * Turns on the specified LED.
 *
 * @param[in] Copy_LedPortId The ID of the LED port.
 * @param[in] Copy_LedPinId The ID of the LED pin.
 * @return Std_ReturnType Returns E_OK if the operation was successful, or E_NOT_OK if an error occurs.
 */
void HAL_LED_On(LED_Port_t Copy_LedPortId, LED_Pin_t Copy_LedPinId);

/**
 * @brief Turn Off an LED
 *
 * Turns off the specified LED.
 *
 * @param[in] Copy_LedPortId The ID of the LED port.
 * @param[in] Copy_LedPinId The ID of the LED pin.
 * @return Std_ReturnType Returns E_OK if the operation was successful, or E_NOT_OK if an error occurs.
 */
void HAL_LED_Off(LED_Port_t Copy_LedPortId, LED_Pin_t Copy_LedPinId);

/**
 * @brief Toggle an LED
 *
 * Toggles the state of the specified LED.
 *
 * @param[in] Copy_LedPortId The ID of the LED port.
 * @param[in] Copy_LedPinId The ID of the LED pin.
 * @return Std_ReturnType Returns E_OK if the operation was successful, or E_NOT_OK if an error occurs.
 */
void HAL_LED_Toggle(LED_Port_t Copy_LedPortId, LED_Pin_t Copy_LedPinId);

///**
// * @brief Blink an LED Once
// *
// * Blinks the specified LED once with a specified delay.
// *
// * @param[in] Copy_LedPortId The ID of the LED port.
// * @param[in] Copy_LedPinId The ID of the LED pin.
// * @param[in] Copy_BlinkTime The delay in milliseconds for each blink.
// * @return Std_ReturnType Returns E_OK if the operation was successful, or E_NOT_OK if an error occurs.
// */
//Std_ReturnType HAL_LED_BlinkOnce(LED_Port_t Copy_LedPortId, LED_Pin_t Copy_LedPinId, LED_Delay_ms_t Copy_BlinkTime);
//
///**
// * @brief Blink an LED Twice
// *
// * Blinks the specified LED twice with a specified delay between blinks.
// *
// * @param[in] Copy_LedPortId The ID of the LED port.
// * @param[in] Copy_LedPinId The ID of the LED pin.
// * @param[in] Copy_BlinkTime The delay in milliseconds for each blink.
// * @return Std_ReturnType Returns E_OK if the operation was successful, or E_NOT_OK if an error occurs.
// */
//Std_ReturnType HAL_LED_BlinkTwice(LED_Port_t Copy_LedPortId, LED_Pin_t Copy_LedPinId, LED_Delay_ms_t Copy_BlinkTime);

/**
 * @} (end of LED_Functions)
 */

/****************************************************************
 *                 End of Interface Section                     *
 ****************************************************************/

/****************************************************************
 *                     Private Section                          *
 ****************************************************************/




/****************************************************************
 *                 End of Private Section                       *
 ****************************************************************/


#endif /**< LED_H_ */
