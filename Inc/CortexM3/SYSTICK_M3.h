/*
 * SYSTICK_M3.h
 *
 *  Created on: Dec 5, 2023
 *      Author: mahmo
 */

#ifndef CORTEXM3_SYSTICK_M3_H_
#define CORTEXM3_SYSTICK_M3_H_


/*----------START INCLUDES----------*/
#include "Std_Types.h"
/*----------END INCLUDES----------*/

/*----------START MACROS----------*/
/* Config Macros*/
#define SYSTICK_CLK_SRC_PRESCALER_1										0
#define SYSTICK_CLK_SRC_PRESCALER_8										1
#define SYSTICK_CLK_SRC_PRESCALER										SYSTICK_CLK_SRC_PRESCALER_1
#define SYSTICK_MAX_PRE_COUNT											(16777216UL)

/* Bit Positions */
#define SYSTICK_CONTROL_STATUS_REGISTER_CLKSOURCE_BIT_POS				2
#define SYSTICK_CONTROL_STATUS_REGISTER_TICKINT_BIT_POS					1
#define SYSTICK_CONTROL_STATUS_REGISTER_ENABLE_BIT_POS					0
#define SYSTICK_CONTROL_STATUS_REGISTER_COUNTFLAG_BIT_POS				16
/* Register handle */
#define SYSTICK													((SYSTICK_TypeDef*)(0xE000E010))
/*----------END MACROS----------*/

/*----------START MACRO-LIKE FUNCTIONS----------*/
/*----------END MACRO-LIKE FUNCTIONS----------*/


/*----------START DATATYPES----------*/

/* Systick callback function */
void(*SYSTICK_CallBackFunction)();

/* Systick Handle register struct*/
typedef struct{
	uint32_t SYSCSR;
	uint32_t SYSRVR;
	uint32_t SYSCVR;
	uint32_t SYSCAVR;
}SYSTICK_TypeDef;

/*----------END DATATYPES----------*/


/*----------START FUNCTIONS----------*/

/* Systick disable interrupt */
void SYSTICK_DisableInterrupt();

/**
 * @brief Init Systick by setting number of ticks, enabling interrupt and clock source
 * 
 * @param copy_u32SystickNumOfTicks 
 * @return * Systick 
 */
void SYSTICK_Init(uint32_t copy_u32SystickNumOfTicks);

/**
 * @brief Denit Systick by clearing number of ticks and disabling interrupt
 * 
 */
void SYSTICK_DeInit();

/* Systick start */
/**
 * @brief Function to start the Systick with a callback function to fire every interval
 * 
 */
void SYSTICK_Start(uint32_t copy_u32SystickNumOfTicks, void(*copy_SystickCallBackFun));

/**
 * @brief Function to blocking wait for a number of ticks
 * 
 * @param copy_u32SystickNumOfTicks 
 */
void SYSTICK_BlockWait(uint32_t copy_u32SystickNumOfTicks);


/**
 * @brief Function to stop Systick functionality
 * 
 * @return  
 */
void SYSTICK_Stop();


static void SYSTICK_SetNumOfTicks(uint32_t copy_u32SystickNumOfTicks);



/*----------END FUNCTIONS----------*/



#endif /* CORTEXM3_SYSTICK_M3_H_ */
