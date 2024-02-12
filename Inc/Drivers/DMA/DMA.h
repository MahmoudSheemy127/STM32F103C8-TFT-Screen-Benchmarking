/*
 * DMA.h
 *
 *  Created on: Dec 16, 2023
 *      Author: Mahmoud Elsheemy
 */

#ifndef DRIVERS_DMA_DMA_H_
#define DRIVERS_DMA_DMA_H_

/************************** INCLUDES *************************/
//#include "Common/Common"
#include "Drivers/Common/Common.h"
#include  "Std_Types.h"

/************************** MACROS *************************/

/* DMA periph base */
#define DMA1_BASE			(AHB_BASE+(uint32_t)0x8000)
#define DMA1				(DMA_GTypeDef*)(DMA1_BASE)
#define DMA1_1				(DMA_TypeDef*)(DMA1_BASE+0x008)
#define DMA1_2				(DMA_TypeDef*)(DMA1_BASE+0x01C)
#define DMA1_3				(DMA_TypeDef*)(DMA1_BASE+0x030)
#define DMA1_4				(DMA_TypeDef*)(DMA1_BASE+0x044)
#define DMA1_5				(DMA_TypeDef*)(DMA1_BASE+0x058)
#define DMA1_6				(DMA_TypeDef*)(DMA1_BASE+0x06C)
#define DMA1_7				(DMA_TypeDef*)(DMA1_BASE+0x080)

/* REGISTER BIT POS MACROS */
#define DMA_CCR_MEM2MEM_Pos    14
#define DMA_CCR_PL_Pos         12
#define DMA_CCR_MSIZE_Pos      10
#define DMA_CCR_PSIZE_Pos      8
#define DMA_CCR_MINC_Pos       7	
#define DMA_CCR_PINC_Pos       6
#define DMA_CCR_CIRC_Pos       5
#define DMA_CCR_DIR_Pos        4
#define DMA_CCR_TEIE_Pos       3
#define DMA_CCR_HTIE_Pos       2
#define DMA_CCR_TCIE_Pos       1
#define DMA_CCR_EN_Pos         0

/************************** DATA TYPES *************************/

typedef void (*DMA_CallbackFn)(void);
DMA_CallbackFn	DMA1_1_CallbackFnPtr;
DMA_CallbackFn	DMA1_2_CallbackFnPtr;
DMA_CallbackFn	DMA1_3_CallbackFnPtr;
DMA_CallbackFn	DMA1_4_CallbackFnPtr;
DMA_CallbackFn	DMA1_5_CallbackFnPtr;
DMA_CallbackFn	DMA1_6_CallbackFnPtr;
DMA_CallbackFn	DMA1_7_CallbackFnPtr;


typedef enum{
	DMA_CIRCULAR_MODE,
	DMA_NON_CIRCULAR_MODE
}DMA_MODE;

typedef enum{
	DMA_READ_FROM_PERIPHERAL,
	DMA_READ_FROM_MEMORY
}DMA_TRANSFER_DIRECTION;

typedef enum{
	DMA_MEM_SIZE_8_BITS,
	DMA_MEM_SIZE_16_BITS,
	DMA_MEM_SIZE_32_BITS
}DMA_MEM_SIZE;

typedef enum{
	DMA_PERIPH_SIZE_8_BITS,
	DMA_PERIPH_SIZE_16_BITS,
	DMA_PERIPH_SIZE_32_BITS
}DMA_PERIPH_SIZE;

typedef enum{
	DMA_MEM2MEM_ENABLE,
	DMA_MEM2MEM_DISABLE
}DMA_MEM2MEM;

typedef enum{
	DMA_MEM_INC_ENABLE,
	DMA_MEM_INC_DISABLE,
}DMA_MEM_INC_MODE;

typedef enum{
	DMA_PERIPH_INC_ENABLE,
	DMA_PERIPH_INC_DISABLE,
}DMA_PERIPH_INC_MODE;

typedef enum{
	DMA_INTERRUPT_ENABLE,
	DMA_INTERRUPT_DISABLE
}DMA_INTERRUPT;


typedef struct{
	uint32_t ISR;
	uint32_t IFCR;
}DMA_GTypeDef;

typedef struct{
	uint32_t CCR;
	uint32_t CNTDR;
	uint32_t CPAR;
	uint32_t CMAR;
}DMA_TypeDef;

typedef struct{
	DMA_TypeDef* dma_TypeDef;
	DMA_GTypeDef* dma_StatusTypedef;
    DMA_MODE dma_Mode;
    DMA_TRANSFER_DIRECTION dma_Direction;
    DMA_MEM_SIZE dma_MemSize;
    DMA_PERIPH_SIZE dma_PeriphSize;
    DMA_MEM2MEM dma_Mem2Mem;
    DMA_MEM_INC_MODE dma_MemIncMode;
    DMA_PERIPH_INC_MODE dma_PeriphIncMode;
	DMA_INTERRUPT dma_Interrupt;
}DMA_HandleTypeDef;


/************************** FUNCTIONS *************************/
HAL_Status DMA_Init(DMA_HandleTypeDef *copy_dmaHandle);
HAL_Status DMA_SetPeriphAddress(DMA_HandleTypeDef *copy_dmaHandle,uint8_t *copy_u32PeriphAddress);
HAL_Status DMA_SetMemoryAddress(DMA_HandleTypeDef *copy_dmaHandle ,uint8_t *copy_u32MemAddress);
HAL_Status DMA_Start(DMA_HandleTypeDef *hdma);
HAL_Status DMA_SetDataCounter(DMA_HandleTypeDef *hdma, uint32_t copy_u32DataLength);
HAL_Status DMA_Stop(DMA_HandleTypeDef *hdma);
HAL_Status DMA_Transfer(DMA_HandleTypeDef *hdma, uint8_t *srcData, uint8_t *destData, uint32_t dataLength);
HAL_Status DMA_SetCallBackFn(DMA_HandleTypeDef *hdma, DMA_CallbackFn callbackFn);
HAL_Status DMA_InterruptEnable(DMA_HandleTypeDef *hdma);
HAL_Status DMA_InterruptDisable(DMA_HandleTypeDef *hdma);
HAL_Status DMA_ClearInterruptFlag(DMA_HandleTypeDef *hdma);

#endif /* DRIVERS_DMA_DMA_H_ */
