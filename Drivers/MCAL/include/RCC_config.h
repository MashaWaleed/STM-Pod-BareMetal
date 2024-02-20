/****************************************************************/
/******* Author    : Mohamed Waleed Elsayed     *****************/
/******* Date      : 4 Sep 2023                 *****************/
/******* Version   : 0.2                        *****************/
/******* File Name : RCC_config.h               *****************/
/****************************************************************/


#ifndef RCC_CONFIG_H_
#define RCC_CONFIG_H_


#define RCC_SYSCLK            RCC_PLL


#define RCC_PLL_SRC           RCC_HSE

#if RCC_PLL_SRC == RCC_HSE
	#define RCC_PLL_INPUT_VAL     HSE_VAL
#else
	#define RCC_PLL_INPUT_VAL     (HSI_VAL / 2)
#endif

#define RCC_PLL_MUL          MUL2
//#define Is_72MHZ


#define HSI_VAL              (uint32_t)8000000
#define HSE_VAL              (uint32_t)8000000              //range is 4 --> 16 MHZ

#if RCC_SYSCLK == RCC_HSE

#define RCC_CLK_BYPASS        RCC_CRYSTAL_CLK_
                                
#endif

#define AHB_PRESCALE 			AHB_PRESCALE_NOT_DIV


#define APB2_PRESCALE			APB2_PRESCALE_NOT_DIV


#define APB1_PRESCALE			APB1_PRESCALE_NOT_DIV


#define ADC_PRESCALE          	ADC_PRESCALE_2


#endif
