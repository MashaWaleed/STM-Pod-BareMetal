/****************************************************************/
/******* Author    : Mohamed Waleed Elsayed     *****************/
/******* Date      : 4 Sep 2023                 *****************/
/******* Version   : 0.2                        *****************/
/******* File Name : RCC_program.c              *****************/
/****************************************************************/

/*****************************< LIB *****************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "stdint.h"
/*****************************< MCAL *****************************/
#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"

/*****************************< Global Variables *****************************/
const uint8_t AHB_PrescaleTable[16U] = {0,0,0,0,0,0,0,0,1,2,3,4,6,7,8,9};
const uint8_t APB_PrescaleTable[8U] = {0,0,0,0,1,2,3,4};
/*****************************< Private Function Implementations *****************************/

u32 PLL_MUL_Calculator(u32 Copy_u32Input_CLkValue, u8 Copy_u8MUL_Factor)
{
	//Handle the 6.5 corner case
    Copy_u8MUL_Factor = (Copy_u8MUL_Factor == 0xD) ? 4.5 : Copy_u8MUL_Factor;

    //conditional for the Frequency value
	if((Copy_u32Input_CLkValue * (Copy_u8MUL_Factor + 2)) <= SYSCLK_SAFE_LIMIT)
	{

		return (Copy_u32Input_CLkValue * (Copy_u8MUL_Factor + 2));
	}
	else{
		return E_NOT_OK;
	}
}

//Std_ReturnType Prescale_Check(u8 Copy_u8Input_CLkValue, u8 Copy_u8MUL_Factor)
//{
//	u8 Local_SysClock = PLL_MUL_Calculator(Copy_u8Input_CLkValue, Copy_u8MUL_Factor);
//	if(Local_SysClock)  //this means sysclk is safe, now lets check other peripherals
//	{
//
//	}
//}


/*****************************< API Implementations *****************************/
Std_ReturnType MCAL_RCC_InitSysClock(void)
{
    Std_ReturnType Local_FunctionStatus = E_NOT_OK;

    #if RCC_SYSCLK == RCC_HSE
        
        /**< Enable the external clock to be the source for the system clock. */
        #if RCC_CLK_BYPASS == RCC_RC_CLK_
            SET_BIT(RCC_CR, RCC_CR_HSEBYP); /**< Choose RC as a SYSCLK */
        #elif RCC_CLK_BYPASS == RCC_CRYSTAL_CLK_
            CLR_BIT(RCC_CR, RCC_CR_HSEBYP); /**< Choose CRYSTAL as a SYSCLK */
        #else 
            #error "Wrong Choice !!"
        #endif /**< RCC_CLK_BYPASS */

        /**< Enable the High-Speed External clock. */
        SET_BIT(RCC_CR, RCC_CR_HSEON);

        /**< Wait until the High-Speed External clock is stable. */
        while(!GET_BIT(RCC_CR, RCC_CR_HSERDY));

        /**< Select High-Speed External clock as the system clock source. */
        RCC_CFGR = 0x00000001;

        Local_FunctionStatus = E_OK;

        RCC_CFGR |= (AHB_PRESCALE<<4);
        RCC_CFGR |= (APB2_PRESCALE<<11);
        RCC_CFGR |= (APB1_PRESCALE<<8);
        RCC_CFGR |= (ADC_PRESCALE<<14)

    #elif RCC_SYSCLK == RCC_HSI
        
        /**< Enable the High-Speed Internal clock. */
        SET_BIT(RCC_CR, RCC_CR_HSION);

        /**< Wait until the High-Speed Internal clock is stable. */
        while(!GET_BIT(RCC_CR, RCC_CR_HSIRDY));

        /**< Select High-Speed Internal clock as the system clock source. */
        RCC_CFGR = 0x00000000;

        Local_FunctionStatus = E_OK;

        RCC_CFGR |= (AHB_PRESCALE<<4);
        RCC_CFGR |= (APB2_PRESCALE<<11);
        RCC_CFGR |= (APB1_PRESCALE<<8);
        RCC_CFGR |= (ADC_PRESCALE<<14)

    #elif RCC_SYSCLK == RCC_PLL

        /**< Specify PLL source. */
		#if RCC_PLL_SRC == RCC_HSE

        	CLR_BIT(RCC_CR, RCC_CR_HSEBYP);
        	SET_BIT(RCC_CR, RCC_CR_HSEON);

        	while (!(RCC_CR & (1 << 17)));

			#ifdef Is_72MHZ
        	FLASH_ACR |= 0x12;
			#endif

        	SET_BIT(RCC_CFGR, RCC_CFGR_PLLSRC);            //PREDIV1 SELECTED (HSE undivided reset value)
		#elif RCC_PLL_SRC == RCC_HSI
        	CLR_BIT(RCC_CFGR, RCC_CFGR_PLLSRC);            //HSI/2 SELECTED
		#endif

        /**< Check if multiplied value is within safe frequency limit. */
		if(PLL_MUL_Calculator(RCC_PLL_INPUT_VAL, RCC_PLL_MUL) != E_NOT_OK )
		{
			// PRESCALERS
			RCC_CFGR |= (AHB_PRESCALE<<4);
			RCC_CFGR |= (APB2_PRESCALE<<11);
			RCC_CFGR |= (APB1_PRESCALE<<8);
			RCC_CFGR |= (ADC_PRESCALE<<14);

			/**< Set configure PLL MUL value . */
			RCC_CFGR &= ~(0xF << RCC_CFGR_PLLMUL);
			RCC_CFGR |= (RCC_PLL_MUL << RCC_CFGR_PLLMUL);


			/**< Enable the PLL . */
			SET_BIT(RCC_CR, RCC_CR_PLLON);
			while (!(RCC_CR & (1 << 25)));
			/**< Wait until the PLL clock is stable. */
			while(!GET_BIT(RCC_CR, RCC_CR_PLLRDY));
			/**< select PLL as SYSCLK without changing remaining bits. */
			RCC_CFGR &= ~(0b11 << RCC_CFGR_SW);
			RCC_CFGR |= (0b10 << RCC_CFGR_SW);

			while (!(RCC_CFGR & (1 << 3)));


			Local_FunctionStatus = E_OK;

		}
		else
		{
			Local_FunctionStatus = E_NOT_OK;

		}

    #else
        #error "Wrong Choice !!"

    #endif /**< RCC_SYSCLK */

    return Local_FunctionStatus;
}

Std_ReturnType MCAL_RCC_EnablePeripheral(u8 Copy_BusId, u8 Copy_PeripheralId)
{
    Std_ReturnType Local_FunctionStatus = E_NOT_OK;

    switch(Copy_BusId)
    {
        /**< Enable the peripheral on the AHB bus. */
        case RCC_AHB:
            SET_BIT(RCC_AHBENR, Copy_PeripheralId);
            Local_FunctionStatus = E_OK;
            break;

        /**< Enable the peripheral on the APB1 bus. */
        case RCC_APB1:
            SET_BIT(RCC_APB1ENR, Copy_PeripheralId);
            Local_FunctionStatus = E_OK;
            break;

        /**< Enable the peripheral on the APB2 bus. */
        case RCC_APB2:
            SET_BIT(RCC_APB2ENR, Copy_PeripheralId);
            Local_FunctionStatus = E_OK;
            break;

        default:
            Local_FunctionStatus = E_NOT_OK;
            break;
    }

    return Local_FunctionStatus;
}

Std_ReturnType MCAL_RCC_DisablePeripheral(u8 Copy_BusId, u8 Copy_PeripheralId)
{
    Std_ReturnType Local_FunctionStatus = E_NOT_OK;

    switch(Copy_BusId)
    {
        /**< Disable the peripheral on the AHB bus. */
        case RCC_AHB:
            CLR_BIT(RCC_AHBENR, Copy_PeripheralId);
            Local_FunctionStatus = E_OK;
            break;

        /**< Disable the peripheral on the APB1 bus. */
        case RCC_APB1:
            CLR_BIT(RCC_APB1ENR, Copy_PeripheralId);
            Local_FunctionStatus = E_OK;
            break;

        /**< Disable the peripheral on the APB2 bus. */
        case RCC_APB2:
            CLR_BIT(RCC_APB2ENR, Copy_PeripheralId);
            Local_FunctionStatus = E_OK;
            break;

        default:
            Local_FunctionStatus = E_NOT_OK;
            break;
    }

    return Local_FunctionStatus;
}

uint32_t MCAL_RCC_GetSYSCLK(void)
{
#if RCC_SYSCLK == RCC_HSE
	return HSE_VAL;
#elif RCC_SYSCLK == RCC_HSI
	return HSI_VAL;
#elif RCC_SYSCLK == RCC_PLL
	return (PLL_MUL_Calculator(RCC_PLL_INPUT_VAL, RCC_PLL_MUL));
#else
	return E_NOT_OK;
#endif
}
uint32_t MCAL_RCC_GetHCLK(void)
{
	return (MCAL_RCC_GetSYSCLK() >> AHB_PrescaleTable[AHB_PRESCALE]);
}
uint32_t MCAL_RCC_GetPCLK1(void)
{
	return (MCAL_RCC_GetHCLK() >> APB_PrescaleTable[APB1_PRESCALE]);
}
uint32_t MCAL_RCC_GetPCLK2(void)
{
	return (MCAL_RCC_GetHCLK() >> APB_PrescaleTable[APB2_PRESCALE]);
}

/*****************************< End of Function Implementations *****************************/
