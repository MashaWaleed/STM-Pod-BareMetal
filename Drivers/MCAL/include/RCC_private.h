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



#define RCC_CR                  (*((volatile u32 *)0x40021000))
#define RCC_CFGR                (*((volatile u32 *)0x40021004))
#define RCC_CIR                 (*((volatile u32 *)0x40021008))
#define RCC_APB2RSTR            (*((volatile u32 *)0x4002100C))
#define RCC_APB1RSTR            (*((volatile u32 *)0x40021010))
#define RCC_AHBENR              (*((volatile u32 *)0x40021014))
#define RCC_APB1ENR             (*((volatile u32 *)0x4002101C))
#define RCC_APB2ENR             (*((volatile u32 *)0x40021018))
#define RCC_BDCR                (*((volatile u32 *)0x40021020))
#define RCC_CSR                 (*((volatile u32 *)0x40021024))


#define RCC_CR_HSION        0
#define RCC_CR_HSIRDY       1
#define RCC_CR_HSICAL       8
#define RCC_CR_HSEON        16
#define RCC_CR_HSERDY       17
#define RCC_CR_HSEBYP       18
// #define RCC_CR_HSEPRE       19
#define RCC_CR_CSSON        19
#define RCC_CR_PLLON        24
#define RCC_CR_PLLRDY       25


#define RCC_CFGR_SW            0
#define RCC_CFGR_PLLSRC        16
#define RCC_CFGR_PLLMUL        18



#define RCC_HSI             0
#define RCC_HSE             1
#define RCC_PLL             2


#define RCC_CRYSTAL_CLK_    0
#define RCC_RC_CLK_         1

#define MUL2             0x0
#define MUL3             0x1
#define MUL4             0x2
#define MUL5             0x3
#define MUL6             0x4
#define MUL7             0x5
#define MUL8             0x6
#define MUL9             0x7
#define MUL6P5           0xD



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


#define SYSCLK_SAFE_LIMIT          (uint32_t)72000000
//#define SYSCLK_SAFE_LIMIT          72
//#define SYSCLK_SAFE_LIMIT          72
//#define SYSCLK_SAFE_LIMIT          72
//#define SYSCLK_SAFE_LIMIT          72
//#define SYSCLK_SAFE_LIMIT          72


#endif /* RCC_PRIVATE_H_ */
