/*
 * SYSTICK_M3.c
 *
 *  Created on: Dec 5, 2023
 *      Author: Mahmoud Elsheemy
 */


#include "CortexM3/SYSTICK_M3.h"


void SYSTICK_Init()
{
	/* Disable SYSTICK */
	CLR_BIT(SYSTICK->SYSCSR,SYSTICK_CONTROL_STATUS_REGISTER_ENABLE_BIT_POS);
	/* Enable Interrupt*/
	SET_BIT(SYSTICK->SYSCSR,SYSTICK_CONTROL_STATUS_REGISTER_TICKINT_BIT_POS);
	/* Set Prescaler of the Systick*/
	if(SYSTICK_CLK_SRC_PRESCALER == SYSTICK_CLK_SRC_PRESCALER_1)
	{
		SET_BIT(SYSTICK->SYSCSR,SYSTICK_CONTROL_STATUS_REGISTER_CLKSOURCE_BIT_POS);
	}	
}

void SYSTICK_DelayMs(uint32_t copy_u32DelayMs)
{
	/* Disable Systick */
	CLR_BIT(SYSTICK->SYSCSR,SYSTICK_CONTROL_STATUS_REGISTER_ENABLE_BIT_POS);
	/* Set number of overflows */
	uint32_t overFlowCounter = 0;
	uint32_t totalOverFlows = copy_u32DelayMs;
	/* Set Preload register value */
	SYSTICK_SetNumOfTicks(SYSTICK_ONE_MILLISECOND_TICKS);
	/* Disable Systick Interrupt */
	CLR_BIT(SYSTICK->SYSCSR,SYSTICK_CONTROL_STATUS_REGISTER_TICKINT_BIT_POS);
	/* Enable SYSTICK */
	SET_BIT(SYSTICK->SYSCSR,SYSTICK_CONTROL_STATUS_REGISTER_ENABLE_BIT_POS);

	/* Loop over number of overflows */
	while(overFlowCounter < totalOverFlows)
	{
		/* Wait till flag is raised */
		while(0 == GET_BIT(SYSTICK->SYSCSR,SYSTICK_CONTROL_STATUS_REGISTER_COUNTFLAG_BIT_POS));
		/* Clear flag */
		SET_BIT(SYSTICK->SYSCSR,SYSTICK_CONTROL_STATUS_REGISTER_COUNTFLAG_BIT_POS);
		/* Increment overflow counter */
		overFlowCounter++;
	}
	/* Wait till flag is raised */
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

void SYSTICK_StartTimer(uint32_t copy_u32SystickNumOfMilliseconds, void(*copy_SystickCallBackFun))
{

	/* Set number of ticks */
	SYSTICK_SetNumOfTicks(copy_u32SystickNumOfMilliseconds * SYSTICK_ONE_MILLISECOND_TICKS);
	/* Set Callback function */
	SYSTICK_CallBackFunction = copy_SystickCallBackFun;
	/* Reset counter */
	SYSTICK_OverflowCounter = 0;
	/* Start SYSTICK */	
	SET_BIT(SYSTICK->SYSCSR,SYSTICK_CONTROL_STATUS_REGISTER_ENABLE_BIT_POS);
}


void SYSTICK_Stop()
{
	/* Disable systick */
	CLR_BIT(SYSTICK->SYSCSR,SYSTICK_CONTROL_STATUS_REGISTER_ENABLE_BIT_POS);
}


void SysTick_Handler()
{
	if(SYSTICK_OverflowCounter < SYSTICK_NumOfOverflows)
	{
		SYSTICK_OverflowCounter++;
	}
	else
	{
		SYSTICK_OverflowCounter = 0;
		SYSTICK_CallBackFunction();
	}
}