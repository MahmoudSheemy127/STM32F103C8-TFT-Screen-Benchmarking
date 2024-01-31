/*
 * DMA.c
 *
 *  Created on: Dec 16, 2023
 *      Author: mahmo
 */


#include "Drivers/DMA/DMA.h"

/*
 * Function: DMA_Init
 * ------------------------
 * Initializes the DMA peripheral based on the provided DMA handle configuration.
 * 
 * Parameters:
 *   copy_dmaHandle: Pointer to the DMA handle structure containing the configuration.
 * 
 * Returns:
 *   HAL_Status: HAL_OKAY if initialization is successful, HAL_ERROR otherwise.
 */
HAL_Status DMA_Init(DMA_HandleTypeDef *copy_dmaHandle){

    HAL_Status hal_Status = HAL_OKAY;
    if(NULL == copy_dmaHandle)
    {
        hal_Status = HAL_ERROR;
    }
    else
    {
    switch(copy_dmaHandle->dma_Direction)
    {
        case DMA_READ_FROM_PERIPHERAL:
            CLR_BIT(copy_dmaHandle->dma_TypeDef->CCR, DMA_CCR_DIR_Pos);
            break;
        case DMA_READ_FROM_MEMORY:
            SET_BIT(copy_dmaHandle->dma_TypeDef->CCR, DMA_CCR_DIR_Pos);
            copy_dmaHandle->dma_TypeDef->CCR = 1<<4;
            break;
    }
    switch(copy_dmaHandle->dma_Mem2Mem)
    {
        case DMA_MEM2MEM_ENABLE:
            SET_BIT(copy_dmaHandle->dma_TypeDef->CCR, DMA_CCR_MEM2MEM_Pos);
            break;
        case DMA_MEM2MEM_DISABLE:
            CLR_BIT(copy_dmaHandle->dma_TypeDef->CCR, DMA_CCR_MEM2MEM_Pos);
            break;
    }
    switch(copy_dmaHandle->dma_Mode)
    {
        case DMA_NON_CIRCULAR_MODE:
            if(copy_dmaHandle->dma_Mem2Mem != DMA_MEM2MEM_ENABLE )
            {
                CLR_BIT(copy_dmaHandle->dma_TypeDef->CCR, DMA_CCR_CIRC_Pos);

            }
            break;
        case DMA_CIRCULAR_MODE:
            SET_BIT(copy_dmaHandle->dma_TypeDef->CCR, DMA_CCR_CIRC_Pos);
            break;
    }
    switch(copy_dmaHandle->dma_MemIncMode)
    {
        case DMA_MEM_INC_ENABLE:
            SET_BIT(copy_dmaHandle->dma_TypeDef->CCR, DMA_CCR_MINC_Pos);
            break;
        case DMA_MEM_INC_DISABLE:
            CLR_BIT(copy_dmaHandle->dma_TypeDef->CCR, DMA_CCR_MINC_Pos);
            break;
    }
    switch(copy_dmaHandle->dma_PeriphIncMode)
    {
        case DMA_PERIPH_INC_ENABLE:
            SET_BIT(copy_dmaHandle->dma_TypeDef->CCR, DMA_CCR_PINC_Pos);
            break;
        case DMA_PERIPH_INC_DISABLE:
            CLR_BIT(copy_dmaHandle->dma_TypeDef->CCR, DMA_CCR_PINC_Pos);
            break;
    }
    }
    return hal_Status;
}

/*
 * Function: DMA_AddPeriphAddress
 * ------------------------
 * Sets the peripheral address for DMA transfer.
 * 
 * Parameters:
 *   copy_dmaHandle: Pointer to the DMA handle structure.
 *   copy_u32PeriphAddress: Pointer to the peripheral address.
 * 
 * Returns:
 *   HAL_Status: HAL_OKAY if setting the address is successful, HAL_ERROR otherwise.
 */
HAL_Status DMA_SetPeriphAddress(DMA_HandleTypeDef *copy_dmaHandle,uint32_t *copy_u32PeriphAddress){
    HAL_Status hal_Status = HAL_OKAY;
    if(NULL == copy_u32PeriphAddress || NULL == copy_dmaHandle )
    {
        hal_Status = HAL_ERROR;
    }
    else
    {
        copy_dmaHandle->dma_TypeDef->CPAR = copy_u32PeriphAddress;
    }
    return hal_Status;
}

/*
 * Function: DMA_SetMemoryAddress
 * ------------------------
 * Sets the memory address for DMA transfer.
 * 
 * Parameters:
 *   copy_dmaHandle: Pointer to the DMA handle structure.
 *   copy_u32MemAddress: Pointer to the memory address.
 * 
 * Returns:
 *   HAL_Status: HAL_OKAY if setting the address is successful, HAL_ERROR otherwise.
 */
HAL_Status DMA_SetMemoryAddress(DMA_HandleTypeDef *copy_dmaHandle ,uint32_t *copy_u32MemAddress){
    HAL_Status hal_Status = HAL_OKAY;
    if(NULL == copy_u32MemAddress || NULL == copy_dmaHandle )
    {
        hal_Status = HAL_ERROR;
    }
    else
    {
        copy_dmaHandle->dma_TypeDef->CMAR = copy_u32MemAddress;
    }
    return hal_Status;
}

/*
 * Function: DMA_Start
 * ------------------------
 * Starts the DMA transfer.
 * 
 * Parameters:
 *   hdma: Pointer to the DMA handle structure.
 * 
 * Returns:
 *   HAL_Status: HAL_OKAY if starting the transfer is successful, HAL_ERROR otherwise.
 */
HAL_Status DMA_Start(DMA_HandleTypeDef *hdma){
    HAL_Status hal_Status = HAL_OKAY;
    if(NULL == hdma )
    {
        hal_Status = HAL_ERROR;
    }
    else
    {
        SET_BIT(hdma->dma_TypeDef->CCR, DMA_CCR_EN_Pos);
    }
    return hal_Status;
}

/**
 * @brief Stops the DMA transfer on the specified DMA channel.
 *
 * @param hdma: Pointer to a DMA_HandleTypeDef structure that contains the configuration information for the specified DMA channel.
 *
 * @return HAL_Status: HAL_OKAY if the operation was successful, HAL_ERROR if there was an error or if the input parameters are invalid.
 */
HAL_Status DMA_Stop(DMA_HandleTypeDef *hdma){
    HAL_Status hal_Status = HAL_OKAY;
    if(NULL == hdma )
    {
        hal_Status = HAL_ERROR;
    }
    else
    {
        CLR_BIT(hdma->dma_TypeDef->CCR, DMA_CCR_EN_Pos);
    }
    return hal_Status;
}

/**
 * @brief Sets the data transfer counter for the specified DMA channel.
 *
 * @param hdma: Pointer to a DMA_HandleTypeDef structure that contains the configuration information for the specified DMA channel.
 * @param copy_u32DataLength: The number of data items to be transferred by the DMA channel.
 *
 * @return HAL_Status: HAL_OKAY if the operation was successful, HAL_ERROR if there was an error or if the input parameters are invalid.
 */
HAL_Status DMA_SetDataCounter(DMA_HandleTypeDef *hdma, uint32_t copy_u32DataLength)
{
    HAL_Status hal_Status = HAL_OKAY;
    if(NULL == hdma )
    {
        hal_Status = HAL_ERROR;
    }
    else
    {
        hdma->dma_TypeDef->CNTDR = copy_u32DataLength;
        // SET_BIT(hdma->dma_TypeDef->CCR, DMA_CCR_EN_Pos);
    }
    return hal_Status;

}
