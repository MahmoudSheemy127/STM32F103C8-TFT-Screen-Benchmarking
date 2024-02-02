/*
 * Cortex_M3_Core.h
 *
 *  Created on: Nov 19, 2023
 *      Author: mahmo
 */

#ifndef CORTEX_M3_CORE_H_
#define CORTEX_M3_CORE_H_

/*-------------------INCLUDES START------------------------*/
#include "Std_Types.h"
/*-------------------INCLUDES END------------------------*/

/*-------------------MACROS START------------------------*/
#define NVIC_BASE		(0xE000E100UL)
#define NVIC			((NVIC_HandleTypeDef*)(NVIC_BASE))
#define SCB
/*-------------------MACROS END------------------------*/

/*-------------------FUNCTION LIKE MACROS TYPES START------------------------*/
/*-------------------FUNCTION LIKE MACROS END------------------------*/

/*-------------------DATATYPES START------------------------*/
typedef struct{
	uint32_t ISER[7U];
	uint32_t RESERVED_1[25U];
	uint32_t ICER[7U];
	uint32_t RESERVED_2[25U];
	uint32_t ISPR[7U];
	uint32_t RESERVED_3[25U];
	uint32_t ICPR[7U];
	uint32_t RESERVED_4[25U];
	uint32_t IARR[7U];
	uint32_t RESERVED_5[57U];
	uint8_t IPR[240U];
}NVIC_HandleTypeDef;


typedef enum {
	/*--- Synchronous Settable Exceptions*/
    NVIC_IRQ_MemManage_Handler = -12,
    NVIC_IRQ_BusFault_Handler = -11,
    NVIC_IRQ_UsageFault_Handler = -10,
    NVIC_IRQ_SVC_Handler = -5 ,
    NVIC_IRQ_DebugMon_Handler = -4,
    NVIC_IRQ_PendSV_Handler = -2,
    NVIC_IRQ_SysTick_Handler = -1,
	/*--- Asynchronous Exceptions*/
	NVIC_IRQ_WWDG_IRQHandler = 0,
    NVIC_IRQ_PVD_IRQHandler,
    NVIC_IRQ_TAMPER_IRQHandler,
    NVIC_IRQ_RTC_IRQHandler,
    NVIC_IRQ_FLASH_IRQHandler,
    NVIC_IRQ_RCC_IRQHandler,
    NVIC_IRQ_EXTI0_IRQHandler,
    NVIC_IRQ_EXTI1_IRQHandler,
    NVIC_IRQ_EXTI2_IRQHandler,
    NVIC_IRQ_EXTI3_IRQHandler,
    NVIC_IRQ_EXTI4_IRQHandler,
    NVIC_IRQ_DMA1_Channel1_IRQHandler,
    NVIC_IRQ_DMA1_Channel2_IRQHandler,
    NVIC_IRQ_DMA1_Channel3_IRQHandler,
    NVIC_IRQ_DMA1_Channel4_IRQHandler,
    NVIC_IRQ_DMA1_Channel5_IRQHandler,
    NVIC_IRQ_DMA1_Channel6_IRQHandler,
    NVIC_IRQ_DMA1_Channel7_IRQHandler,
    NVIC_IRQ_ADC1_2_IRQHandler,
    NVIC_IRQ_USB_HP_CAN_TX_IRQHandler,
    NVIC_IRQ_USB_LP_CAN_RX0_IRQHandler,
    NVIC_IRQ_CAN_RX1_IRQHandler,
    NVIC_IRQ_CAN_SCE_IRQHandler,
    NVIC_IRQ_EXTI9_5_IRQHandler,
    NVIC_IRQ_TIM1_BRK_IRQHandler,
    NVIC_IRQ_TIM1_UP_IRQHandler,
    NVIC_IRQ_TIM1_TRG_COM_IRQHandler,
    NVIC_IRQ_TIM1_CC_IRQHandler,
    NVIC_IRQ_TIM2_IRQHandler,
    NVIC_IRQ_TIM3_IRQHandler,
    NVIC_IRQ_TIM4_IRQHandler,
    NVIC_IRQ_I2C1_EV_IRQHandler,
    NVIC_IRQ_I2C1_ER_IRQHandler,
    NVIC_IRQ_I2C2_EV_IRQHandler,
    NVIC_IRQ_I2C2_ER_IRQHandler,
    NVIC_IRQ_SPI1_IRQHandler,
    NVIC_IRQ_SPI2_IRQHandler,
    NVIC_IRQ_USART1_IRQHandler,
    NVIC_IRQ_USART2_IRQHandler,
    NVIC_IRQ_USART3_IRQHandler,
    NVIC_IRQ_EXTI15_10_IRQHandler,
    NVIC_IRQ_RTCAlarm_IRQHandler,
    NVIC_IRQ_Reserved,
    NVIC_IRQ_TIM8_BRK_IRQHandler,
    NVIC_IRQ_TIM8_UP_IRQHandler,
    NVIC_IRQ_TIM8_TRG_COM_IRQHandler,
    NVIC_IRQ_TIM8_CC_IRQHandler,
    NVIC_IRQ_ADC3_IRQHandler,
    NVIC_IRQ_FSMC_IRQHandler,
    NVIC_IRQ_SDIO_IRQHandler,
    NVIC_IRQ_TIM5_IRQHandler,
    NVIC_IRQ_SPI3_IRQHandler,
    NVIC_IRQ_UART4_IRQHandler,
    NVIC_IRQ_UART5_IRQHandler,
    NVIC_IRQ_TIM6_IRQHandler,
    NVIC_IRQ_TIM7_IRQHandler,
    NVIC_IRQ_DMA2_Channel1_IRQHandler,
    NVIC_IRQ_DMA2_Channel2_IRQHandler,
    NVIC_IRQ_DMA2_Channel3_IRQHandler,
    NVIC_IRQ_DMA2_Channel4_5_IRQHandler
} NVIC_IRQ;


/*-------------------DATATYPES END------------------------*/

/*-------------------FUNCTIONS START------------------------*/
/**
 * @brief Enable interrupt for a given irq
 * 
 * @param copy_enumIRQ irq number for interrupt 
 */
void NVIC_SetEnableInterrupt(NVIC_IRQ copy_enumIRQ);

/**
 * @brief Clear interrupt for a given irq 
 * 
 * @param copy_enumIRQ irq number for interrupt
 */
void NVIC_ClearEnableInterrupt(NVIC_IRQ copy_enumIRQ);

/**
 * @brief Enable interrupt for a given irq
 * 
 * @param copy_enumIRQ irq number for interrupt 
 */
void NVIC_SetPendingInterrupt(NVIC_IRQ copy_enumIRQ);

/**
 * @brief Clear interrupt for a given irq 
 * 
 * @param copy_enumIRQ irq number for interrupt
 */
void NVIC_ClearPendingInterrupt(NVIC_IRQ copy_enumIRQ);

/**
 * @brief Return Active status for an interrupt
 * 
 * @param copy_enumIRQ irq number for interrupt
 * @return Active status 
 */
uint32_t NVIC_IsActiveInterrupt(NVIC_IRQ copy_enumIRQ);

/**
 * @brief Set priority for an interrupt
 * 
 * @param copy_u8Priority Priority value for the interrupt
 * @param copy_enumIRQ irq number for interrupt
 */
void NVIC_SetPriority(uint8_t copy_u8Priority, NVIC_IRQ copy_enumIRQ);

/*-------------------FUNCTIONS END------------------------*/


#endif /* CORTEX_M3_CORE_H_ */
