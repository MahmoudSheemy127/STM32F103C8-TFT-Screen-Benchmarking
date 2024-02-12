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
#include "Drivers/SPI/SPI.h"
#include "CortexM3/SYSTICK_M3.h"
#include "Drivers/ECU/ILI9341_STM32_Driver.h"
#include "Drivers/ECU/ILI9341_GFX.h"


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif



/* Helper functions */
void blinkLed();
void Clock_Config();

/* Define Global arrays */
DMA_HandleTypeDef dma;
uint8_t sendArray[5] = {0x01, 0x02,0x03,0x04,0x05};
uint8_t receiveArray[5];
SPI_HandleTypeDef spi1;
SPI_HandleTypeDef spi2;

GPIO_HandleTypeDef mosi1;
GPIO_HandleTypeDef miso1;
GPIO_HandleTypeDef sck1;
GPIO_HandleTypeDef nss1;

GPIO_HandleTypeDef mosi2;
GPIO_HandleTypeDef miso2;
GPIO_HandleTypeDef sck2;
GPIO_HandleTypeDef nss2;

DMA_HandleTypeDef spiTxdma;
DMA_HandleTypeDef spiRxdma;


/* Define callback function */
void DMA1_1_CallbackFn();

void HAL_Init();

void transmit(uint8_t cmd);

int main(void)
{
	/* Init Systick */
//	SYSTICK_Init();
//	/* enable RCC clock */
//	_RCC_GPIOA_ENABLE();
//	_RCC_GPIOB_ENABLE();
//	_RCC_SPI1_ENABLE();
//	_RCC_DMA1_ENABLE();

	HAL_Init();
	ILI9341_Init();

	uint8_t data = 0x06;
	/* Loop forever */
	NVIC_SetEnableInterrupt(NVIC_IRQ_DMA1_Channel3_IRQHandler);
	// SPI_ReceiveDMA(&spi2, receiveArray,5);
	// SPI_TransmitDMA(&spi1, sendArray, 5);
	while(1)
	{
		// ILI9341_Fill_Screen(BLACK);
		/* Interlacing demo */
		// ILI9341_Draw_Rectangle(0,0,128,20,OLIVE);
		// SYSTICK_DelayMs(50);
		// ILI9341_Draw_Rectangle(0,40,128,20,OLIVE);
		// SYSTICK_DelayMs(50);
		// ILI9341_Draw_Rectangle(0,80,128,20,OLIVE);
		// SYSTICK_DelayMs(50);
		// ILI9341_Draw_Rectangle(0,120,128,20,OLIVE);
		// SYSTICK_DelayMs(50);
		// ILI9341_Draw_Rectangle(0,20,128,20,ORANGE);
		// SYSTICK_DelayMs(50);
		// ILI9341_Draw_Rectangle(0,60,128,20,ORANGE);
		// SYSTICK_DelayMs(50);
		// ILI9341_Draw_Rectangle(0,100,128,20,ORANGE);
		// SYSTICK_DelayMs(50);
		// ILI9341_Draw_Rectangle(0,140,128,20,ORANGE);
		// //SYSTICK_DelayMs(200);
		// SYSTICK_DelayMs(50);
		// ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
		// ILI9341_Draw_Rectangle(0,0,128,160,WHITE);
		// SYSTICK_DelayMs(50);
		// ILI9341_Draw_Text("Hello World1", 10, 10, BLACK, 1, WHITE);
		// SYSTICK_DelayMs(2000);
		// ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
		// ILI9341_Draw_Rectangle(0,0,128,160,WHITE);
		// SYSTICK_DelayMs(50);
		// ILI9341_Draw_Text("Hello World2", 10, 10, BLACK, 1, WHITE);
		// SYSTICK_DelayMs(2000);
		ILI9341_Set_Rotation(SCREEN_VERTICAL_2);
		ILI9341_Draw_Rectangle(0,0,128,160,WHITE);
		SYSTICK_DelayMs(50);
		ILI9341_Draw_Text("dLrow oLLeH", 10, 10, BLACK, 1, WHITE);
		SYSTICK_DelayMs(2000);
		// ILI9341_Set_Rotation(SCREEN_VERTICAL_2);
		// ILI9341_Draw_Rectangle(0,0,128,160,WHITE);
		// SYSTICK_DelayMs(50);
		// ILI9341_Draw_Text("Hello World4", 10, 10, BLACK, 1, WHITE);
		// SYSTICK_DelayMs(2000);

//		ILI9341_Draw_Rectangle(0,0,128,160,WHITE);
//		SYSTICK_DelayMs(200);

		// ILI9341_Fill_Screen(BLACK);
		// SYSTICK_DelayMs(200);
		// ILI9341_Fill_Screen(RED);
		// SYSTICK_DelayMs(200);
		// ILI9341_Fill_Screen(GREEN);
		// SYSTICK_DelayMs(200);
		// ILI9341_Fill_Screen(WHITE);
		// SYSTICK_DelayMs(200);

//		ILI9341_Draw_Rectangle(0,0,128,160,BLUE);
//		SYSTICK_DelayMs(200);
//		ILI9341_Draw_Rectangle(0,0,128,160,BLACK);
//		SYSTICK_DelayMs(200);
//		ILI9341_Draw_Rectangle(0,0,128,160,WHITE);
//		SYSTICK_DelayMs(200);

		// ILI9341_Fill_Screen(WHITE);
		// SYSTICK_DelayMs(2000);
		// ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
		// //ILI9341_Draw_Text("FPS TEST, 40 loop 2 screens", 10, 10, BLACK, 1, WHITE);
		// SYSTICK_DelayMs(2000);
		// ILI9341_Fill_Screen(BLACK);
		// ILI9341_Draw_Rectangle(0,0,50,50,RED);

		// SPI_Transmit(&spi1, &data, 1);
		// transmit(0xC6);
		// transmit(0x3F);
		// transmit(0xAB);
		// data++;
		//SYSTICK_DelayMs(500);

		// blinkLed();
		// SYSTICK_DelayMs(500);
	}

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
	_RCC_GPIOA_ENABLE();
	_RCC_GPIOB_ENABLE();
	_RCC_GPIOC_ENABLE();
	_RCC_GPIOD_ENABLE();

}

void HAL_Init()
{
	 /* Init Systick */
	 SYSTICK_Init();
	 /* enable RCC clock */
	 _RCC_GPIOA_ENABLE();
	 _RCC_GPIOB_ENABLE();
	 _RCC_SPI1_ENABLE();
	 _RCC_DMA1_ENABLE();

	//  /* Init SPI 1 as master */
	//  spi1.Instance = SPI1;
	//  spi1.Mode = SPI_MODE_MASTER;
	//  spi1.DataSize = SPI_DATASIZE_8BIT;
	//  spi1.CPOL = SPI_CPOL_LOW;
	//  spi1.CPHA = SPI_CPHA_1EDGE;
	//  spi1.BaudRate = SPI_BAUDRATE_DIV2;
	//  spi1.NSS = SPI_NSS_DISABLE;
	//  spi1.BiDir = SPI_BIDIR_DISABLE;
	//  spi1.CRC = SPI_CRC_DISABLE;
	//  spi1.FirstBit = SPI_LSB_FIRST;
	//  spi1.CRCPolynomial = SPI_CRC_POLYNOMIAL_7BIT;
	//  spi1.CRCDir = SPI_CRC_TX;
	//  spi1.SpiTxDma = SPI_TX_DMA_ENABLE;
	//  spi1.SpiRxDma = SPI_RX_DMA_DISABLE;


	//  /* Init MOSI,MISO,SCK,NSS pin configs */
	//  /* Init MOSI pin */
	//  mosi1.GPIO_TypeDef = PORT_SPI1;
	//  mosi1.GPIO_Pin = MOSI_SPI1;
	//  mosi1.GPIO_Mode = GPIO_MODE_OUTPUT_2MHZ;
	//  mosi1.GPIO_CNF = GPIO_CNF_OUTPUT_ALTFN_PUSH_PULL;
	//  GPIO_Init(&mosi1);

	//  /* Init MISO pin */
	//  miso1.GPIO_TypeDef = PORT_SPI1;
	//  miso1.GPIO_Pin = MISO_SPI1;
	//  miso1.GPIO_Mode = GPIO_MODE_INPUT;
	//  miso1.GPIO_CNF = GPIO_CNF_INPUT_FLOATING;
	//  GPIO_Init(&miso1);

	//  /* Init SCK pin */
	//  sck1.GPIO_TypeDef = PORT_SPI1;
	//  sck1.GPIO_Pin = SCK_SPI1;
	//  sck1.GPIO_Mode = GPIO_MODE_OUTPUT_2MHZ;
	//  sck1.GPIO_CNF = GPIO_CNF_OUTPUT_ALTFN_PUSH_PULL;
	//  GPIO_Init(&sck1);

	//  /* Init NSS pin */
	//  nss1.GPIO_TypeDef = PORT_SPI1;
	//  nss1.GPIO_Pin = NSS_SPI1;
	//  nss1.GPIO_Mode = GPIO_MODE_OUTPUT_2MHZ;
	//  nss1.GPIO_CNF = GPIO_CNF_OUTPUT_ALTFN_PUSH_PULL;
	//  GPIO_Init(&nss1);


	//  /*Init DMA channels */
	//  spiTxdma.dma_TypeDef = DMA1_3;
	//  spiTxdma.dma_Mem2Mem = DMA_MEM2MEM_DISABLE;
	//  spiTxdma.dma_Mode = DMA_NON_CIRCULAR_MODE;
	//  spiTxdma.dma_Direction = DMA_READ_FROM_MEMORY;
	//  spiTxdma.dma_MemSize = DMA_MEM_SIZE_8_BITS;
	//  spiTxdma.dma_PeriphSize = DMA_PERIPH_SIZE_8_BITS;
	//  spiTxdma.dma_MemIncMode = DMA_MEM_INC_ENABLE;
	//  spiTxdma.dma_PeriphIncMode = DMA_PERIPH_INC_DISABLE;
	//  spiTxdma.dma_Interrupt = DMA_INTERRUPT_DISABLE;

	//  spi1.txdma = &spiTxdma;

	//  DMA_Init(spi1.txdma);

	//  SPI_Init(&spi1);

	/* Init SPI 2 as slave */
	_RCC_SPI2_ENABLE();
	spi2.Instance = SPI2;
	spi2.Mode = SPI_MODE_SLAVE;
	spi2.DataSize = SPI_DATASIZE_8BIT;
	spi2.CPOL = SPI_CPOL_LOW;
	spi2.CPHA = SPI_CPHA_1EDGE;
	spi2.BaudRate = SPI_BAUDRATE_DIV2;
	spi2.NSS = SPI_NSS_HARD;
	spi2.BiDir = SPI_BIDIR_DISABLE;
	spi2.CRC = SPI_CRC_DISABLE;
	spi2.FirstBit = SPI_LSB_FIRST;
	spi2.CRCPolynomial = SPI_CRC_POLYNOMIAL_7BIT;
	spi2.CRCDir = SPI_CRC_TX;
	spi2.SpiTxDma = SPI_TX_DMA_DISABLE;
	spi2.SpiRxDma = SPI_RX_DMA_ENABLE;

	/* Init MOSI,MISO,SCK,NSS pin configs */
	/* Init MOSI pin */
	mosi2.GPIO_TypeDef = PORT_SPI2;
	mosi2.GPIO_Pin = MOSI_SPI2;
	mosi2.GPIO_Mode = GPIO_MODE_INPUT;
	mosi2.GPIO_CNF = GPIO_CNF_INPUT_FLOATING;
	GPIO_Init(&mosi2);

	/* Init MISO pin */
	miso2.GPIO_TypeDef = PORT_SPI2;
	miso2.GPIO_Pin = MISO_SPI2;
	miso2.GPIO_Mode = GPIO_MODE_OUTPUT_2MHZ;
	miso2.GPIO_CNF = GPIO_CNF_OUTPUT_ALTFN_PUSH_PULL;
	GPIO_Init(&miso2);

	/* Init SCK pin */
	sck2.GPIO_TypeDef = PORT_SPI2;
	sck2.GPIO_Pin = SCK_SPI2;
	sck2.GPIO_Mode = GPIO_MODE_INPUT;
	sck2.GPIO_CNF = GPIO_CNF_INPUT_FLOATING;
	GPIO_Init(&sck2);

	/* Init NSS pin */
	nss2.GPIO_TypeDef = PORT_SPI2;
	nss2.GPIO_Pin = NSS_SPI2;
	nss2.GPIO_Mode = GPIO_MODE_INPUT;
	nss2.GPIO_CNF = GPIO_CNF_INPUT_FLOATING;
	GPIO_Init(&nss2);
	
	/*Init DMA channels */
	spiRxdma.dma_TypeDef = DMA1_4;
	spiRxdma.dma_Mem2Mem = DMA_MEM2MEM_DISABLE;
	spiRxdma.dma_Mode = DMA_NON_CIRCULAR_MODE;
	spiRxdma.dma_Direction = DMA_READ_FROM_PERIPHERAL;
	spiRxdma.dma_MemSize = DMA_MEM_SIZE_8_BITS;
	spiRxdma.dma_PeriphSize = DMA_PERIPH_SIZE_8_BITS;
	spiRxdma.dma_MemIncMode = DMA_MEM_INC_ENABLE;
	spiRxdma.dma_PeriphIncMode = DMA_PERIPH_INC_DISABLE;
	spiRxdma.dma_Interrupt = DMA_INTERRUPT_ENABLE;

	spi2.rxdma = &spiRxdma;

	//DMA_Init(spi2.rxdma);


	SPI_Init(&spi2);


	// dma.dma_TypeDef = DMA1_1;
	// dma.dma_Direction = DMA_READ_FROM_MEMORY;
	// dma.dma_Mem2Mem = DMA_MEM2MEM_ENABLE;
	// dma.dma_MemIncMode = DMA_MEM_INC_ENABLE;
	// dma.dma_Mode = DMA_NON_CIRCULAR_MODE;
	// dma.dma_Interrupt = DMA_INTERRUPT_ENABLE;
	// DMA_Init(&dma);
	// DMA_SetCallBackFn(&dma,DMA1_1_CallbackFn);
	// DMA_Transfer(&dma, sendArray, receiveArray,2);


}

void blinkLed()
{
	GPIOA->ODR ^= (1<<0);
}

void WWDG_IRQHandler()
{
	GPIOA->ODR |= (1<<0);
}


void transmit(unsigned char cmd)
{
	SPI_Transmit(&spi1, &cmd, 1);
}

void DMA1_1_CallbackFn()
{
	if(sendArray[1] != receiveArray[1])
	{
		GPIOA->ODR |= (1 << 0);
	}
	else
	{
		// GPIOA->ODR |= ( << 0);
		//do nothing
	}
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
