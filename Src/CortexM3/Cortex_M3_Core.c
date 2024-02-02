/*
 * Cortex_M3_Core.c
 *
 *  Created on: Nov 19, 2023
 *      Author: mahmo
 */

#include "CortexM3/Cortex_M3_Core.h"

/**
 * @brief Enable interrupt for a given irq
 * 
 * @param copy_enumIRQ irq number for interrupt 
 */
void NVIC_SetEnableInterrupt(NVIC_IRQ copy_enumIRQ)
{
    NVIC->ISER[(copy_enumIRQ >> 5)] |= (1 << (copy_enumIRQ & 0x1F));
    
}

/**
 * @brief Clear interrupt for a given irq 
 * 
 * @param copy_enumIRQ irq number for interrupt
 */
void NVIC_ClearEnableInterrupt(NVIC_IRQ copy_enumIRQ)
{
    NVIC->ICER[(copy_enumIRQ >> 5)] |= (1 << (copy_enumIRQ & 0x1F));
}

/**
 * @brief Enable interrupt for a given irq
 * 
 * @param copy_enumIRQ irq number for interrupt 
 */
void NVIC_SetPendingInterrupt(NVIC_IRQ copy_enumIRQ)
{
    NVIC->ISPR[(copy_enumIRQ >> 5)] |= (1 << (copy_enumIRQ & 0x1F));
}

/**
 * @brief Clear interrupt for a given irq 
 * 
 * @param copy_enumIRQ irq number for interrupt
 */
void NVIC_ClearPendingInterrupt(NVIC_IRQ copy_enumIRQ)
{
    NVIC->ICPR[(copy_enumIRQ >> 5)] |= (1 << (copy_enumIRQ & 0x1F));
}

/**
 * @brief Return Active status for an interrupt
 * 
 * @param copy_enumIRQ irq number for interrupt
 * @return Active status 
 */
uint32_t NVIC_IsActiveInterrupt(NVIC_IRQ copy_enumIRQ)
{
    return  (NVIC->ISER[(copy_enumIRQ >> 5)] >> ((copy_enumIRQ & 0x1F)) & (uint32_t)1);
}

/**
 * @brief Set priority for an interrupt
 * 
 * @param copy_u8Priority Priority value for the interrupt
 * @param copy_enumIRQ irq number for interrupt
 */
void NVIC_SetPriority(uint8_t copy_u8Priority, NVIC_IRQ copy_enumIRQ)
{
    NVIC->IPR[copy_enumIRQ] = copy_u8Priority;
}


