/****************************************************************/
/******* Author    : Mohamed Waleed Elsayed     *****************/
/******* Date      : 4 Sep 2023                 *****************/
/******* Version   : 0.2                        *****************/
/******* File Name : RCC_private.h              *****************/
/****************************************************************/

#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_


#define FLASH 0x40022000
#define FLASH_ACR (*((volatile uint32_t *)(FLASH + 0x00)))


/**
 * @defgroup RCC_Registers
 * @brief Reset and Clock Control (RCC) Registers
 *
 * This module provides definitions for the RCC (Reset and Clock Control) registers
 * for configuring and controlling system clocks and resets in the microcontroller.
 *
 * @{
 */

/**
 * @brief RCC Control Register (CR)
 *
 * This register provides control over the main and PLL (Phase-Locked Loop) system clocks.
 */
#define RCC_CR                  (*((volatile u32 *)0x40021000))

/**
 * @brief RCC Configuration Register (CFGR)
 *
 * This register configures the system clock sources, prescalers, and peripherals clocks.
 */
#define RCC_CFGR                (*((volatile u32 *)0x40021004))

/**
 * @brief RCC Clock Interrupt Register (CIR)
 *
 * This register manages clock interrupts and flags.
 */
#define RCC_CIR                 (*((volatile u32 *)0x40021008))

/**
 * @brief RCC APB2 Peripheral Reset Register (APB2RSTR)
 *
 * This register controls the reset state of peripherals connected to APB2 bus.
 */
#define RCC_APB2RSTR            (*((volatile u32 *)0x4002100C))

/**
 * @brief RCC APB1 Peripheral Reset Register (APB1RSTR)
 *
 * This register controls the reset state of peripherals connected to APB1 bus.
 */
#define RCC_APB1RSTR            (*((volatile u32 *)0x40021010))

/**
 * @brief RCC AHB Peripheral Clock Enable Register (AHBENR)
 *
 * This register enables clock access for peripherals connected to AHB bus.
 */
#define RCC_AHBENR              (*((volatile u32 *)0x40021014))

/**
 * @brief RCC APB1 Peripheral Clock Enable Register (APB1ENR)
 *
 * This register enables clock access for peripherals connected to APB1 bus.
 */
#define RCC_APB1ENR             (*((volatile u32 *)0x4002101C))

/**
 * @brief RCC APB2 Peripheral Clock Enable Register (APB2ENR)
 *
 * This register enables clock access for peripherals connected to APB2 bus.
 */
#define RCC_APB2ENR             (*((volatile u32 *)0x40021018))

/**
 * @brief RCC Backup Domain Control Register (BDCR)
 *
 * This register provides control over backup domain and RTC (Real-Time Clock).
 */
#define RCC_BDCR                (*((volatile u32 *)0x40021020))

/**
 * @brief RCC Control and Status Register (CSR)
 *
 * This register provides various control and status flags.
 */
#define RCC_CSR                 (*((volatile u32 *)0x40021024))

/** @} */ // end of RCC Control Register (CR)





/**
 * @defgroup RCC_CR_Bit_Definitions RCC Control Register (RCC_CR) Bit Definitions
 * @{
 */

#define RCC_CR_HSION        0   /**< Internal High-Speed Clock Enable */
#define RCC_CR_HSIRDY       1   /**< Internal High-Speed Clock Ready */
#define RCC_CR_HSICAL       8   /**< Internal High-Speed Clock Calibration */
#define RCC_CR_HSEON        16  /**< External High-Speed Clock Enable */
#define RCC_CR_HSERDY       17  /**< External High-Speed Clock Ready */
#define RCC_CR_HSEBYP       18  /**< External High-Speed Clock Bypass */
// #define RCC_CR_HSEPRE       19  /**< External High-Speed Clock Prescaler */
#define RCC_CR_CSSON        19  /**< Clock Security System Enable */
#define RCC_CR_PLLON        24  /**< PLL Enable */
#define RCC_CR_PLLRDY       25  /**< PLL Ready */

/** @} */ // end of RCC_CR_Bit_Definitions


/**
 * @defgroup RCC_CFGR_Bit_Definitions RCC Control Register (RCC_CR) Bit Definitions
 * @{
 */
#define RCC_CFGR_SW            0    /**< Bit for choosing SYSCLK src */
#define RCC_CFGR_PLLSRC        16   /**< Bit for choosing pll src */
#define RCC_CFGR_PLLMUL        18   /**< 4bit field to choose PLLMUL*/


/** @} */ // end of RCC_CFGR_Bit_Definitions

/**
 * @defgroup RCC_Clock_Source RCC Clock Source Macros
 * @{
 */

#define RCC_HSI             0   /**< High-Speed Internal Clock Source (HSI) */
#define RCC_HSE             1   /**< High-Speed External Clock Source (HSE) */
#define RCC_PLL             2   /**< Phase-Locked Loop Clock Source (PLL) */

/** @} */ // end of RCC_Clock_Source

/**
 * @defgroup RCC_Clock_Type RCC Clock Type Macros
 * @{
 */

#define RCC_CRYSTAL_CLK_    0   /**< Crystal Oscillator Clock Type */
#define RCC_RC_CLK_         1   /**< RC Oscillator Clock Type */

/** @} */ // end of RCC_Clock_Type


/**
 * @defgroup PLL_MULL  Macros
 * @{
 */
#define MUL2             0x0
#define MUL3             0x1
#define MUL4             0x2
#define MUL5             0x3
#define MUL6             0x4
#define MUL7             0x5
#define MUL8             0x6
#define MUL9             0x7
#define MUL6P5           0xD


/** @} */ // end of PLL_MULL

/**
 * @defgroup BUS_PRESCALER  Macros
 * @{
 */


/* Options for AHB Prescale */
#define AHB_PRESCALE_NOT_DIV     0b0000
#define AHB_PRESCALE_2      	 0b1000
#define AHB_PRESCALE_4      	 0b1001
#define AHB_PRESCALE_8      	 0b1010
#define AHB_PRESCALE_16     	 0b1011
#define AHB_PRESCALE_64     	 0b1100
#define AHB_PRESCALE_128    	 0b1101
#define AHB_PRESCALE_256         0b1110
#define AHB_PRESCALE_512    	 0b1111

/* Options for APB2 */
#define APB2_PRESCALE_NOT_DIV	 0b000
#define APB2_PRESCALE_2      	 0b100  //4
#define APB2_PRESCALE_4          0b101  //5
#define APB2_PRESCALE_8          0b110
#define APB2_PRESCALE_16     	 0b111

/* Options for APB1 */
#define APB1_PRESCALE_NOT_DIV	 0b000
#define APB1_PRESCALE_2      	 0b100
#define APB1_PRESCALE_4          0b101
#define APB1_PRESCALE_8          0b110
#define APB1_PRESCALE_16     	 0b111

/* Options for ADC */
#define ADC_PRESCALE_NOT_DIV	 0b00
#define ADC_PRESCALE_2      	 0b01
#define ADC_PRESCALE_4           0b10
#define ADC_PRESCALE_8           0b11
/** @} */ // end of BUS_PRESCALER

//----------------------Private Functions--------------

/**
 * @brief Check if multiplication is within safe limit.
 *
 * This funciton is crucial in choosing PLL and SYSCLK as using a bas MUL factor can lead to MCU damage.
 *
 *
 *
 * @return Std_ReturnType
 * @retval E_OK     Frequency in safe limit.
 * @retval E_NOT_OK Frequency not safe.
 */



#define SYSCLK_SAFE_LIMIT          (uint32_t)72000000
//#define SYSCLK_SAFE_LIMIT          72
//#define SYSCLK_SAFE_LIMIT          72
//#define SYSCLK_SAFE_LIMIT          72
//#define SYSCLK_SAFE_LIMIT          72
//#define SYSCLK_SAFE_LIMIT          72


#endif /* RCC_PRIVATE_H_ */
