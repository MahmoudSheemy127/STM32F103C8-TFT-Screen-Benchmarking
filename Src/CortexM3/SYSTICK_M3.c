/*
 * SYSTICK_M3.c
 *
 *  Created on: Dec 5, 2023
 *      Author: Mahmoud Elsheemy
 */


#include "CortexM3/SYSTICK_M3.h"


void SYSTICK_Init(uint32_t copy_u32SystickNumOfTicks)
{
	/* Enable Interrupt*/
	SET_BIT(SYSTICK->SYSCSR,SYSTICK_CONTROL_STATUS_REGISTER_TICKINT_BIT_POS);
	/* Set Prescaler of the Systick*/
	if(SYSTICK_CLK_SRC_PRESCALER == SYSTICK_CLK_SRC_PRESCALER_1)
	{
		SET_BIT(SYSTICK->SYSCSR,SYSTICK_CONTROL_STATUS_REGISTER_CLKSOURCE_BIT_POS);
	}	
	/* Set Number of ticks*/
	SYSTICK_SetNumOfTicks(copy_u32SystickNumOfTicks);

	/* Disable SYSTICK */
	CLR_BIT(SYSTICK->SYSCSR,SYSTICK_CONTROL_STATUS_REGISTER_ENABLE_BIT_POS);


}

static void SYSTICK_SetNumOfTicks(uint32_t copy_u32SystickNumOfTicks)
{
	/* Set Number of ticks*/
	if(copy_u32SystickNumOfTicks > SYSTICK_MAX_PRE_COUNT)
	{
			SYSTICK->SYSRVR	= SYSTICK_MAX_PRE_COUNT;
	}
	else
	{
			SYSTICK->SYSRVR = copy_u32SystickNumOfTicks;
	}
}

void SYSTICK_DeInit()
{
	/* Clear Counter */
	SYSTICK->SYSRVR = (uint32_t)0;
	/* Disable interrupt */
	CLR_BIT(SYSTICK->SYSCSR,SYSTICK_CONTROL_STATUS_REGISTER_TICKINT_BIT_POS);
	/* Disable Systick*/
	CLR_BIT(SYSTICK->SYSCSR,SYSTICK_CONTROL_STATUS_REGISTER_ENABLE_BIT_POS);
}


void SYSTICK_DisableInterrupt()
{
	CLR_BIT(SYSTICK->SYSCSR,SYSTICK_CONTROL_STATUS_REGISTER_TICKINT_BIT_POS);
}

void SYSTICK_Start(uint32_t copy_u32SystickNumOfTicks, void(*copy_SystickCallBackFun))
{
	/* Set number of ticks */
	SYSTICK_SetNumOfTicks(copy_u32SystickNumOfTicks);
	/* Set Callback function */
	SYSTICK_CallBackFunction = copy_SystickCallBackFun;
	/* Start SYSTICK */	
	SET_BIT(SYSTICK->SYSCSR,SYSTICK_CONTROL_STATUS_REGISTER_ENABLE_BIT_POS);
}

void SYSTICK_Stop()
{
	/* Disable systick */
	CLR_BIT(SYSTICK->SYSCSR,SYSTICK_CONTROL_STATUS_REGISTER_ENABLE_BIT_POS);
}


void NVIC_IRQ_SysTick_Handler()
{
	SYSTICK_CallBackFunction();
}