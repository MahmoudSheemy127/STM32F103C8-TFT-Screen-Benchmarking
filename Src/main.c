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
#include "Drivers/DMA/DMA.h"
#include "CortexM3/SYSTICK_M3.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


void blinkLed();
void Clock_Config();




/* Define Global arrays */
uint8_t sendArray[2] = {2, 3};
uint8_t receiveArray[2];

int main(void)
{

	RCC->RCC_APB2ENR |= (1 << 2);
//	Clock_Config();
	GPIOA->CRL |= (1 << 0);
	GPIOA->CRL &= ~(1 << 2);
//	SYSTICK_Init(10UL);
	// NVIC_SetEnableInterrupt(NVIC_IRQ_SysTick_Handler);
//	SYSTICK_Start(10UL,blinkLed);
	//set as output
	GPIOA->ODR |= (1 << 0);
	DMA_HandleTypeDef dma;
	dma.dma_TypeDef = DMA1_1;
	dma.dma_Direction = DMA_READ_FROM_MEMORY;
	dma.dma_Mem2Mem = DMA_MEM2MEM_ENABLE;
	dma.dma_MemIncMode = DMA_MEM_INC_ENABLE;
	dma.dma_Mode = DMA_NON_CIRCULAR_MODE;
	DMA_Init(&dma);
	
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
