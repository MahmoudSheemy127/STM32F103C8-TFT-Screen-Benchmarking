/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mahmoud Elsheemy
 * @brief          : Main program body
 ******************************************************************************
 */

#include <stdint.h>

#include "CortexM3/Cortex_M3_Core.h"
#include "Drivers/GPIO/GPIO.h"
#include "Drivers/RCC/RCC.h"
#include "CortexM3/SYSTICK_M3.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


void blinkLed();
void Clock_Config();
//THESE ARE FOR THE ASYNCHRONOUS EXCEPTIONS
// //SET ENABLE REGISTERS
// #define NVIC_ISER0	*((volatile uint32_t*)(0xE000E100))
// #define NVIC_ISER1	*((volatile uint32_t*)(0xE000E104))
// #define NVIC_ISER2	*((volatile uint32_t*)(0xE000E108))
// #define NVIC_ISER3	*((volatile uint32_t*)(0xE000E10C))
// #define NVIC_ISER4	*((volatile uint32_t*)(0xE000E110))
// #define NVIC_ISER5	*((volatile uint32_t*)(0xE000E114))
// #define NVIC_ISER6	*((volatile uint32_t*)(0xE000E118))
// #define NVIC_ISER7	*((volatile uint32_t*)(0xE000E11C))

// //CLEAR ENABLE REGISTERS
// #define NVIC_ICER0	*((volatile uint32_t*)0xE000E180)
// #define NVIC_ICER1	*((volatile uint32_t*)0xE000E184)
// #define NVIC_ICER2	*((volatile uint32_t*)0xE000E188)
// #define NVIC_ICER3	*((volatile uint32_t*)0xE000E18C)
// #define NVIC_ICER4	*((volatile uint32_t*)0xE000E190)
// #define NVIC_ICER5	*((volatile uint32_t*)0xE000E194)
// #define NVIC_ICER6	*((volatile uint32_t*)0xE000E198)
// #define NVIC_ICER7	*((volatile uint32_t*)0xE000E19C)

// //SET PENDING REGISTERS
// #define NVIC_ISPR0	*((volatile uint32_t*)0xE000E200)
// #define NVIC_ISPR1	*((volatile uint32_t*)0xE000E204)
// #define NVIC_ISPR2	*((volatile uint32_t*)0xE000E208)
// #define NVIC_ISPR3	*((volatile uint32_t*)0xE000E20C)
// #define NVIC_ISPR4	*((volatile uint32_t*)0xE000E210)
// #define NVIC_ISPR5	*((volatile uint32_t*)0xE000E214)
// #define NVIC_ISPR6	*((volatile uint32_t*)0xE000E218)
// #define NVIC_ISPR7	*((volatile uint32_t*)0xE000E21C)

//define and init gpio led
//config pin as output

//enable rcc

int main(void)
{
	//NVIC->ISER[2] |= (1<<24);
	//select hse clock
//	RCC->RCC_CR |= (1<<16);
	//set rcc for GPIO A
	RCC->RCC_APB2ENR |= (1 << 2);
//	Clock_Config();
	GPIOA->CRL |= (1 << 0);
	GPIOA->CRL &= ~(1 << 2);
//	SYSTICK_Init(10UL);
	// NVIC_SetEnableInterrupt(NVIC_IRQ_SysTick_Handler);
//	SYSTICK_Start(10UL,blinkLed);
	//set as output
	GPIOA->ODR |= (1 << 0);

	//enable interrupt (TIM7)
	// NVIC_SetEnableInterrupt(NVIC_IRQ_WWDG_IRQHandler);
	// NVIC_SetPendingInterrupt(NVIC_IRQ_WWDG_IRQHandler);
	// NVIC_ClearEnableInterrupt(NVIC_IRQ_WWDG_IRQHandler);
	
	//	NVIC_ISER1 |= (1 << 24);
//	set pending for this interrupt
//	NVIC_ISPR1 |= (1 << 24);

    /* Loop forever */
	for(;;);

}


void Clock_Config()
{
	HAL_Status status;
	RCC_HandleTypedef rcc_handle;
	rcc_handle.RCC_OscillatorType = RCC_CONFIG_TYPE_HSE;
	rcc_handle.RCC_HseState = RCC_CLOCK_ON;
	rcc_handle.RCC_AHB_PRE = RCC_AHB_DIV1;
	rcc_handle.RCC_ABP1_PRE = RCC_APB1_DIV4;
	rcc_handle.RCC_ABP2_PRE = RCC_APB2_DIV4;

	status = RCC_Init(&rcc_handle);

	if(HAL_ERROR == status)
	{
		/*------ Take some action ---- */
	}

	//enable rcc clock
	_RCC_GPIOA_ENABLE;
	_RCC_GPIOB_ENABLE;
	_RCC_GPIOC_ENABLE;
	_RCC_GPIOD_ENABLE;

}


void blinkLed()
{
	GPIOA->ODR ^= (1<<0);
}

void WWDG_IRQHandler()
{
	GPIOA->ODR |= (1<<0);

}

//void TIM7_IRQHandler()
//{
//	GPIOA->ODR |= (1<<13);
////	while(1)
////	{
////		//This should execute
////
////	}
//}
