/*
 * RCC.h
 *
 *  Created on: Nov 20, 2023
 *      Author: mahmo
 */

#ifndef RCC_H_
#define RCC_H_

/*-------------------INCLUDES START------------------------*/
#include "Std_Types.h"
#include "Drivers/Common/Common.h"
/*-------------------INCLUDES END------------------------*/


/*-------------------MACROS START------------------------*/
#define RCC_BASE						(AHB_BASE+0x9000UL)
#define RCC								((RCC_Typedef*)(RCC_BASE))
/*----------------BIT POSITIONS------------------*/
#define RCC_GPIOA_MSK_BIT_POS			(0x00000002UL)
#define RCC_GPIOB_MSK_BIT_POS			(0x00000003UL)
#define RCC_GPIOC_MSK_BIT_POS			(0x00000004UL)
#define RCC_GPIOD_MSK_BIT_POS			(0x00000005UL)
#define RCC_DMA1_MSK_BIT_POS			(0x00000000UL)

#define RCC_CR_HSE_ON_MSK_BIT_POS		(0x000000016UL)
#define RCC_CR_HSE_RDY_MSK_BIT_POS		(0x000000017UL)
#define RCC_CR_HSE_BYP_MSK_BIT_POS		(0x000000018UL)
#define RCC_CR_HSI_ON_MSK_BIT_POS		(0x000000000UL)
#define RCC_CR_HSI_RDY_MSK_BIT_POS		(0x000000001UL)

#define RCC_CFGR_HPRE_BIT_POS			(0x000000004UL)
#define RCC_CFGR_PPRE1_BIT_POS			(0x000000008UL)
#define RCC_CFGR_PPRE2_BIT_POS			(0x00000000CUL)


/*-------------Diff Clock TYPES-------------*/
#define RCC_CONFIG_TYPE_HSE				(0x00000000UL)
#define RCC_CONFIG_TYPE_LSE				(0x00000001UL)
#define RCC_CONFIG_TYPE_HSI				(0x00000002UL)
#define RCC_CONFIG_TYPE_LSI				(0x00000003UL)

/*-------------Diff Clock states-------------*/
#define RCC_CLOCK_ON				(0x00000001UL)
#define RCC_CLOCK_OFF				(0x00000000UL)

/*------------RCC CLOCK PRESCALER VALUES----------*/
#define RCC_PPRE1_DIV_1				(0x00)
#define RCC_PPRE1_DIV_2				(0x04)
#define RCC_PPRE1_DIV_4				(0x05)
#define RCC_PPRE1_DIV_8				(0x06)
#define RCC_PPRE1_DIV_16			(0x07)

#define RCC_PPRE2_DIV_1				(0x00)
#define RCC_PPRE2_DIV_2				(0x04)
#define RCC_PPRE2_DIV_4				(0x05)
#define RCC_PPRE2_DIV_8				(0x06)
#define RCC_PPRE2_DIV_16			(0x07)

#define RCC_HPRE_DIV_1				(0x00)
#define RCC_HPRE_DIV_2				(0x08)
#define RCC_HPRE_DIV_4				(0x09)
#define RCC_HPRE_DIV_8				(0x0A)
#define RCC_HPRE_DIV_16				(0x0B)
#define RCC_HPRE_DIV_64				(0x0C)
#define RCC_HPRE_DIV_128			(0x0D)
#define RCC_HPRE_DIV_256			(0x0E)
#define RCC_HPRE_DIV_512			(0x0F)

/*------------RCC CLOCK USER PRESCALER VALUES----------*/
#define RCC_AHB_DIV1				RCC_HPRE_DIV_1
#define RCC_AHB_DIV2				RCC_HPRE_DIV_2
#define RCC_AHB_DIV4				RCC_HPRE_DIV_4
#define RCC_AHB_DIV8				RCC_HPRE_DIV_8
#define RCC_AHB_DIV16				RCC_HPRE_DIV_16
#define RCC_AHB_DIV64				RCC_HPRE_DIV_64
#define RCC_AHB_DIV128				RCC_HPRE_DIV_128
#define RCC_AHB_DIV256				RCC_HPRE_DIV_256
#define RCC_AHB_DIV512				RCC_HPRE_DIV_512

#define RCC_APB1_DIV1				RCC_PPRE1_DIV_1
#define RCC_APB1_DIV2				RCC_PPRE1_DIV_2
#define RCC_APB1_DIV4				RCC_PPRE1_DIV_4
#define RCC_APB1_DIV8				RCC_PPRE1_DIV_8
#define RCC_APB1_DIV16				RCC_PPRE1_DIV_16

#define RCC_APB2_DIV1				RCC_PPRE2_DIV_1
#define RCC_APB2_DIV2				RCC_PPRE2_DIV_2
#define RCC_APB2_DIV4				RCC_PPRE2_DIV_4
#define RCC_APB2_DIV8				RCC_PPRE2_DIV_8
#define RCC_APB2_DIV16				RCC_PPRE2_DIV_16


/*-------------------MACROS END------------------------*/

/*-------------------FUNCTION LIKE MACROS TYPES START------------------------*/
#define _RCC_GPIOA_ENABLE()			(SET_BIT(RCC->RCC_APB2ENR,RCC_GPIOA_MSK_BIT_POS))
#define _RCC_GPIOB_ENABLE()			(SET_BIT(RCC->RCC_APB2ENR,RCC_GPIOB_MSK_BIT_POS))
#define _RCC_GPIOC_ENABLE()			(SET_BIT(RCC->RCC_APB2ENR,RCC_GPIOC_MSK_BIT_POS))
#define _RCC_GPIOD_ENABLE()			(SET_BIT(RCC->RCC_APB2ENR,RCC_GPIOD_MSK_BIT_POS))
#define _RCC_DMA1_ENABLE()			(SET_BIT(RCC->RCC_AHBENR,RCC_DMA1_MSK_BIT_POS))
/*-------------------FUNCTION LIKE MACROS END------------------------*/

/*-------------------DATATYPES START------------------------*/
typedef struct{
	volatile uint32_t RCC_CR;
	volatile uint32_t RCC_CFGR;
	volatile uint32_t RCC_CIR;
	volatile uint32_t RCC_APB2RSTR;
	volatile uint32_t RCC_APB1RSTR;
	volatile uint32_t RCC_AHBENR;
	volatile uint32_t RCC_APB2ENR;
	volatile uint32_t RCC_APB1ENR;
	volatile uint32_t RCC_BDCR;
	volatile uint32_t RCC_CSR;
}RCC_Typedef;


typedef struct{
	uint32_t RCC_OscillatorType;
	uint32_t RCC_HseState;
	uint32_t RCC_HsiState;
	uint32_t RCC_LseState;
	uint32_t RCC_LsiState;
	uint32_t RCC_AHB_PRE;
	uint32_t RCC_ABP1_PRE;
	uint32_t RCC_ABP2_PRE;

}RCC_HandleTypedef;

/*-------------------DATATYPES END------------------------*/

/*-------------------FUNCTIONS START------------------------*/
//Start HSE clock function
HAL_Status RCC_Init(RCC_HandleTypedef *rcc_handle);

//Set clock speed function (using PLL)


/*-------------------FUNCTIONS END------------------------*/









#endif /* RCC_H_ */
