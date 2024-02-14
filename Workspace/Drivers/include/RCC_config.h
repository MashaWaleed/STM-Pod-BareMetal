/****************************************************************/
/******* Author    : Mohamed Waleed Elsayed     *****************/
/******* Date      : 4 Sep 2023                 *****************/
/******* Version   : 0.2                        *****************/
/******* File Name : RCC_config.h               *****************/
/****************************************************************/


#ifndef RCC_CONFIG_H_
#define RCC_CONFIG_H_

/**
 * @defgroup RCC_System_Clock_Config RCC System Clock Configuration Macros
 * @brief Macros for configuring the RCC system clock source and type.
 * @{
 */

/**
 * @brief Select the system clock source.
 * @note Choose one of the available options:
 *       - RCC_HSI: High-Speed Internal Clock Source (HSI).
 *                  This option uses the internal high-speed oscillator as the system clock source.
 *                  The HSI provides a stable and accurate clock source, suitable for most applications.
 *       - RCC_HSE: High-Speed External Clock Source (HSE).
 *                  This option uses an external crystal oscillator as the system clock source.
 *                  The HSE provides a higher level of accuracy and stability compared to HSI.
 *                  It is recommended for applications requiring precise timing.
 *       - RCC_PLL: Phase-Locked Loop Clock Source (PLL).
 *                  This option uses the PLL as the system clock source, which multiplies
 *                  the frequency of an input clock source (e.g., HSI or HSE) to generate
 *                  a higher frequency output. PLL provides flexibility in tuning the clock frequency,
 *                  making it suitable for applications with specific performance requirements.
 */
#define RCC_SYSCLK            RCC_PLL

/**
 * @brief Select the PLL clock source and Multiplier value.
 * @note Choose one of the available options:
 *       - RCC_HSI: High-Speed Internal Clock Source (HSI).
 *                  This option uses the internal high-speed oscillator as the system clock source.
 *                  The HSI provides a stable and accurate clock source, suitable for most applications.
 *       - RCC_HSE: High-Speed External Clock Source (HSE).
 *                  This option uses an external crystal oscillator as the system clock source.
 *                  The HSE provides a higher level of accuracy and stability compared to HSI.
 *                  It is recommended for applications requiring precise timing.
 */

#define RCC_PLL_SRC           RCC_HSE

#if RCC_PLL_SRC == RCC_HSE
	#define RCC_PLL_INPUT_VAL     HSE_VAL
#else
	#define RCC_PLL_INPUT_VAL     (HSI_VAL / 2)
#endif

#define RCC_PLL_MUL          MUL2
//#define Is_72MHZ


/**
 * @brief Define values for XTAL and internal crystal.
 * @note Change either of these according to the specs of your SOC or your external clock choice:
 *       HSI_VAL
 *       HSE_VAL
 */

#define HSI_VAL              (uint32_t)8000000
#define HSE_VAL              (uint32_t)8000000              //range is 4 --> 16 MHZ

/**
 * @brief Configure the clock type for RCC_SYSCLK when using RCC_HSE.
 * @note Choose one of the available options:
 *       RCC_RC_CLK_       - RC oscillator will be the source of the clock system.
 *       RCC_CRYSTAL_CLK_  - Crystal oscillator will be the source of the clock system.
 */
#if RCC_SYSCLK == RCC_HSE

#define RCC_CLK_BYPASS        RCC_CRYSTAL_CLK_
                                
#endif /**< RCC_SYSCLK */

/** @} */ // end of RCC_System_Clock_Config


/**
 * @brief Configure the Presacaler for each bus according to predefined macros
 */

/* Options : AHB_PRESCALE_NOT_DIV
			 AHB_PRESCALE_2
			 AHB_PRESCALE_4
			 AHB_PRESCALE_8
			 AHB_PRESCALE_16
			 AHB_PRESCALE_64
			 AHB_PRESCALE_128
			 AHB_PRESCALE_256
			 AHB_PRESCALE_512
 	 	 	 	 	 	 	 	 */
#define AHB_PRESCALE 			AHB_PRESCALE_NOT_DIV

/* Options : APB2_PRESCALE_NOT_DIV
			 APB2_PRESCALE_2
			 APB2_PRESCALE_4
			 APB2_PRESCALE_8
			 APB2_PRESCALE_16
 	 	 	 	 	 	 	 	 */
#define APB2_PRESCALE			APB2_PRESCALE_NOT_DIV

/* Options : APB1_PRESCALE_NOT_DIV
			 APB1_PRESCALE_2
			 APB1_PRESCALE_4
			 APB1_PRESCALE_8
			 APB1_PRESCALE_16
 	 	 	 	 	 	 	 	 */
#define APB1_PRESCALE			APB1_PRESCALE_NOT_DIV

/* Options : ADC_PRESCALE_NOT_DIV
			 ADC_PRESCALE_2
			 ADC_PRESCALE_4
			 ADC_PRESCALE_8
								*/
#define ADC_PRESCALE          	ADC_PRESCALE_2

/** @} */ // end of RCC_System_Clock_Config


#endif /**< RCC_CONFIG_H_ */
