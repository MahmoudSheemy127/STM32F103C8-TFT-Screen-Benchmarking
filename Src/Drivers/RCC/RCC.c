/*
 * RCC.c
 *
 *  Created on: Nov 20, 2023
 *      Author: mahmo
 */

#include "Drivers/RCC/RCC.h"

HAL_Status RCC_Init(RCC_HandleTypedef *rcc_handle)
{
	HAL_Status status = HAL_OKAY;
	if(NULL == rcc_handle)
	{
		status = HAL_ERROR;
	}
	else
	{
		/* Configure RCC type */
		if(RCC_CONFIG_TYPE_HSE == rcc_handle->RCC_OscillatorType)
		{
			/* Clear HSI */
			CLR_BIT(RCC->RCC_CR,RCC_CR_HSI_ON_MSK_BIT_POS);
//			CLR_BIT(RCC->RCC_CR,RCC_CR_HSI_RDY_MSK_BIT_POS);
			if(RCC_CLOCK_ON == rcc_handle->RCC_HseState)
			{

				/* Set HSE bit on */
				SET_BIT(RCC->RCC_CR,RCC_CR_HSE_ON_MSK_BIT_POS);
				SET_BIT(RCC->RCC_CR,RCC_CR_HSE_BYP_MSK_BIT_POS);
			}

			else
			{
				CLR_BIT(RCC->RCC_CR,RCC_CR_HSE_ON_MSK_BIT_POS);
			}

		}
		else if(RCC_CONFIG_TYPE_HSI == rcc_handle->RCC_OscillatorType)
		{

		}

		/* Config RCC clock prescalar */
		/* SET AHB PRESCALAR */
		MODIFY_REG(RCC->RCC_CFGR,(0x0F << RCC_CFGR_HPRE_BIT_POS),rcc_handle->RCC_AHB_PRE << RCC_CFGR_HPRE_BIT_POS);
		/* SET APB1 PRESCALAR */
		MODIFY_REG(RCC->RCC_CFGR,(0x07 << RCC_CFGR_PPRE1_BIT_POS),rcc_handle->RCC_ABP1_PRE << RCC_CFGR_PPRE1_BIT_POS);

		/* SET APB2 PRESCALAR */
		MODIFY_REG(RCC->RCC_CFGR,(0x07 << RCC_CFGR_PPRE2_BIT_POS),rcc_handle->RCC_ABP2_PRE << RCC_CFGR_PPRE2_BIT_POS);

	}


	return status;
}
