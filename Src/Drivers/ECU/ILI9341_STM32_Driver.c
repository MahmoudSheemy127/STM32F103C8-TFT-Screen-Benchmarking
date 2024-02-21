
//	MIT License
//
//	Copyright (c) 2017 Matej Artnak
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in all
//	copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//	SOFTWARE.
//
//
//
//-----------------------------------
//	ILI9341 Driver library for STM32
//-----------------------------------
//
//	While there are other libraries for ILI9341 they mostly require either interrupts, DMA or both for fast drawing
//	The intent of this library is to offer a simple yet still reasonably fast alternatives for those that
//	do not wish to use interrupts or DMA in their projects.
//
//	Library is written for STM32 HAL library and supports STM32CUBEMX. To use the library with Cube software
//	you need to tick the box that generates peripheral initialization code in their own respective .c and .h file
//
//
//-----------------------------------
//	Performance
//-----------------------------------
//	Settings:	
//	--SPI @ 50MHz 
//	--STM32F746ZG Nucleo board
//	--Redraw entire screen
//
//	++		Theoretical maximum FPS with 50Mhz SPI calculated to be 40.69 FPS
//	++		320*240 = 76800 pixels, each pixel contains 16bit colour information (2x8)
//	++		Theoretical Max FPS: 1/((320*240*16)/50000000)
//
//	With ART Accelerator, instruction prefetch, CPI ICACHE and CPU DCACHE enabled:
//
//	-FPS:									39.62
//	-SPI utilization:			97.37%
//	-MB/Second:						6.09
//
//	With ART Accelerator, instruction prefetch, CPI ICACHE and CPU DCACHE disabled:
//
//	-FPS:									35.45
//	-SPI utilization:			87.12%
//	-MB/Second:						5.44
//	
//	ART Accelerator, instruction prefetch, CPI ICACHE and CPU DCACHE settings found in MXCUBE under "System-> CORTEX M7 button"
//
//
//
//-----------------------------------
//	How to use this library
//-----------------------------------
//
//	-generate SPI peripheral and 3 GPIO_SPEED_FREQ_VERY_HIGH GPIO outputs
//	 		++Library reinitializes GPIOs and SPIs generated by gpio.c/.h and spi.c/.h using MX_X_Init(); calls
//			++reinitialization will not clash with previous initialization so generated initializations can be laft as they are
//	-If using MCUs other than STM32F7 you will have to change the #include "stm32f7xx_hal.h" in the ILI9341_STM32_Driver.h to your respective .h file
//	-define your HSPI_INSTANCE in ILI9341_STM32_Driver.h
//	-define your CS, DC and RST outputs in ILI9341_STM32_Driver.h
//	-check if ILI9341_SCREEN_HEIGHT and ILI9341_SCREEN_WIDTH match your LCD size
//			++Library was written and tested for 320x240 screen size. Other sizes might have issues**
//	-in your main program initialize LCD with ILI9341_Init();
//	-library is now ready to be used. Driver library has only basic functions, for more advanced functions see ILI9341_GFX library	
//
//-----------------------------------

/* Includes ------------------------------------------------------------------*/
#include "Drivers/SPI/SPI.h"
#include "Drivers/GPIO/GPIO.h"
#include "Drivers/DMA/DMA.h"
#include "CortexM3/SYSTICK_M3.h"
#include "Drivers/TIM/TIM.h"
// #include "spi.h"
// #include "gpio.h"
#include "ILI9341_STM32_Driver.h"

/* Global Variables ------------------------------------------------------------------*/
volatile uint16_t LCD_HEIGHT = ILI9341_SCREEN_HEIGHT;
volatile uint16_t LCD_WIDTH	 = ILI9341_SCREEN_WIDTH;
uint8_t Color_buffer[500];
uint32_t Color_bufferSize = 0;
uint32_t Color_burstCounter = 0;
uint32_t TotalSize = 0;
uint32_t Color_burstSize = 0;
uint32_t ILI9341_CurrentTimeElapsedMs = 0;
float ILI9341_OverallTimeElapsedMs = 0;
TIM_HandleTypeDef TIM2;

/* Initialize SPI */
void ILI9341_SPI_Init(void)
{
	/* Init SPI */
	hspi1.Instance = SPI1;
	hspi1.Mode = SPI_MODE_MASTER;
	hspi1.DataSize = SPI_DATASIZE_8BIT;
	hspi1.CPOL = SPI_CPOL_LOW;
	hspi1.CPHA = SPI_CPHA_1EDGE;
	hspi1.BaudRate = SPI_BAUDRATE_DIV2;
	hspi1.NSS = SPI_NSS_DISABLE;
	hspi1.BiDir = SPI_BIDIR_DISABLE;
	hspi1.CRC = SPI_CRC_DISABLE;
	hspi1.FirstBit = SPI_LSB_FIRST;
	hspi1.CRCPolynomial = SPI_CRC_POLYNOMIAL_7BIT;
	hspi1.CRCDir = SPI_CRC_TX;
	hspi1.SpiTxDma = SPI_TX_DMA_ENABLE;
	hspi1.SpiRxDma = SPI_RX_DMA_DISABLE;

	/* Init GPIOs*/
	/* Init MOSI */
	SDA.GPIO_TypeDef = PORT_SPI1;
	SDA.GPIO_Pin = MOSI_SPI1;
	SDA.GPIO_Mode = GPIO_MODE_OUTPUT_2MHZ;
	SDA.GPIO_CNF = GPIO_CNF_OUTPUT_ALTFN_PUSH_PULL;
	GPIO_Init(&SDA);

	/* Init SCK */
	SCK.GPIO_TypeDef = PORT_SPI1;
	SCK.GPIO_Pin = SCK_SPI1;
	SCK.GPIO_Mode = GPIO_MODE_OUTPUT_2MHZ;
	SCK.GPIO_CNF = GPIO_CNF_OUTPUT_ALTFN_PUSH_PULL;
	GPIO_Init(&SCK);

	/* Init CS */
	CS.GPIO_TypeDef = PORT_SPI1;
	CS.GPIO_Pin = GPIO_PIN_3;
	CS.GPIO_Mode = GPIO_MODE_OUTPUT_2MHZ;
	CS.GPIO_CNF = GPIO_CNF_OUTPUT_PUSH_PULL;
	GPIO_Init(&CS);

	/* Init DC */
	DC.GPIO_TypeDef = PORT_SPI1;
	DC.GPIO_Pin = GPIO_PIN_2;
	DC.GPIO_Mode = GPIO_MODE_OUTPUT_2MHZ;
	DC.GPIO_CNF = GPIO_CNF_OUTPUT_PUSH_PULL;
	GPIO_Init(&DC);


	RST.GPIO_TypeDef = PORT_SPI1;
	RST.GPIO_Pin = GPIO_PIN_8;
	RST.GPIO_Mode = GPIO_MODE_OUTPUT_2MHZ;
	RST.GPIO_CNF = GPIO_CNF_OUTPUT_PUSH_PULL;
	GPIO_Init(&RST);

	/*Init DMA channels */
	spiTxdma.dma_TypeDef = DMA1_3;
	spiTxdma.dma_StatusTypedef = DMA1;
	spiTxdma.dma_Mem2Mem = DMA_MEM2MEM_DISABLE;
	spiTxdma.dma_Mode = DMA_NON_CIRCULAR_MODE;
	spiTxdma.dma_Direction = DMA_READ_FROM_MEMORY;
	spiTxdma.dma_MemSize = DMA_MEM_SIZE_8_BITS;
	spiTxdma.dma_PeriphSize = DMA_PERIPH_SIZE_8_BITS;
	spiTxdma.dma_MemIncMode = DMA_MEM_INC_ENABLE;
	spiTxdma.dma_PeriphIncMode = DMA_PERIPH_INC_DISABLE;
	spiTxdma.dma_Interrupt = DMA_INTERRUPT_ENABLE;

	hspi1.txdma = &spiTxdma;

	DMA_Init(hspi1.txdma);
	DMA_SetCallBackFn(hspi1.txdma,ILI9341_SPI_DMACallbackFn);

	/* Init SPI */
	SPI_Init(&hspi1);


	/* Init Timer for benchmarking */
	TIM2.Instance = TIM_2_BASE;
	TIM2.Interrupt = TIM_INTERRUPT_ENABLE;
	TIM2.NumberOfMilliseconds = 1;
	TIM2.Prescaler = TIM_PRESCALAR_VALUE_DIV_8;

	/* Set Callback function for timer */
	TIM_SetCallBackFn(&TIM2,ILI9341_TimerCallbackFn);
	/* Init */
	TIM_Init(&TIM2);	
	GPIO_WritePin(&CS, GPIO_PIN_RESET);

// MX_SPI5_Init();																							//SPI INIT
// MX_GPIO_Init();																							//GPIO INIT
// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);	//CS OFF
}

int ILI9341_Return_BenchmarkSize()
{
	int size = TotalSize;
	TotalSize = 0;
	return size;
}

void ILI9341_StartBenchmark()
{
	/* Reset Timer Elapsed counter */
	ILI9341_CurrentTimeElapsedMs = 0;
	/* Reset Timer Counter */
	TIM2.Instance->CNT = 0;
	/* Start Timer */
	TIM_Start(&TIM2);
}

void ILI9341_StopBenchmark()
{
	/* Stop Timer */
	TIM_Stop(&TIM2);
	/* Calculate TimeElapsed and add it to overallTimeElapsed */
	ILI9341_OverallTimeElapsedMs += ILI9341_CurrentTimeElapsedMs + (float)((TIM2.Instance->CNT) * 0.001);
}

void ILI9341_TimerCallbackFn()
{	
	ILI9341_CurrentTimeElapsedMs++;
}


void ILI9341_SPI_DMACallbackFn()
{

	DMA_Stop(hspi1.txdma);
	//DMA_InterruptDisable(hspi1.txdma);
	DMA_ClearInterruptFlag(hspi1.txdma);
	if(Color_burstCounter < Color_burstSize)
	{
		SPI_TransmitDMA(&hspi1, (unsigned char *)Color_buffer, Color_bufferSize);
		Color_burstCounter++;
	}
	else
	{
		Color_burstCounter = 0;
		GPIO_WritePin(&CS, GPIO_PIN_SET);
		/* STOP benchmarking */
		#if BENCHMARK_ENABLE
		ILI9341_StopBenchmark();
		#endif
	}
}

float ILI9341_Return_TimeElapsed()
{
	float buff = ILI9341_OverallTimeElapsedMs;
	ILI9341_OverallTimeElapsedMs = 0;
	ILI9341_CurrentTimeElapsedMs = 0;
	return buff;
} 

/*Send data (char) to LCD*/
void ILI9341_SPI_Send(uint8_t SPI_Data)
{
//HAL_SPI_Transmit(HSPI_INSTANCE, &SPI_Data, 1, 1);
SPI_Transmit(&hspi1, &SPI_Data, 1);
}

/* Send command (char) to LCD */
void ILI9341_Write_Command(uint8_t Command)
{
	//HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	//HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);
	GPIO_WritePin(&CS, GPIO_PIN_RESET);
	GPIO_WritePin(&DC, GPIO_PIN_RESET);
	ILI9341_SPI_Send(Command);
	GPIO_WritePin(&CS, GPIO_PIN_SET);
	//HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);		
}

/* Send Data (char) to LCD */
void ILI9341_Write_Data(uint8_t Data)
{
	GPIO_WritePin(&CS, GPIO_PIN_RESET);
	GPIO_WritePin(&DC, GPIO_PIN_SET);
	ILI9341_SPI_Send(Data);
	GPIO_WritePin(&CS, GPIO_PIN_SET);

// HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);	
// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
// ILI9341_SPI_Send(Data);	
// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}

/* Set Address - Location block - to draw into */
void ILI9341_Set_Address(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2)
{
ILI9341_Write_Command(0x2A);
ILI9341_Write_Data(X1>>8);
ILI9341_Write_Data(X1);
ILI9341_Write_Data(X2>>8);
ILI9341_Write_Data(X2);

ILI9341_Write_Command(0x2B);
ILI9341_Write_Data(Y1>>8);
ILI9341_Write_Data(Y1);
ILI9341_Write_Data(Y2>>8);
ILI9341_Write_Data(Y2);

ILI9341_Write_Command(0x2C);
}

/*HARDWARE RESET*/
void ILI9341_Reset(void)
{
	GPIO_WritePin(&RST, GPIO_PIN_RESET);
	SYSTICK_DelayMs(200);
	GPIO_WritePin(&CS, GPIO_PIN_RESET);
	SYSTICK_DelayMs(200);
	GPIO_WritePin(&RST, GPIO_PIN_SET);

	// HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_RESET);
	// HAL_Delay(200);
	// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	// HAL_Delay(200);
	// HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);	
}

/*Ser rotation of the screen - changes x0 and y0*/
void ILI9341_Set_Rotation(uint8_t Rotation) 
{
	
uint8_t screen_rotation = Rotation;

ILI9341_Write_Command(0x36);
SYSTICK_DelayMs(1);
	
switch(screen_rotation) 
	{
		case SCREEN_VERTICAL_1:
			ILI9341_Write_Data(0x40|0x08);
			LCD_WIDTH = 240;
			LCD_HEIGHT = 320;
			break;
		case SCREEN_HORIZONTAL_1:
			ILI9341_Write_Data(0x20|0x08);
			LCD_WIDTH  = 320;
			LCD_HEIGHT = 240;
			break;
		case SCREEN_VERTICAL_2:
			ILI9341_Write_Data(0x80|0x08);
			LCD_WIDTH  = 240;
			LCD_HEIGHT = 320;
			break;
		case SCREEN_HORIZONTAL_2:
			ILI9341_Write_Data(0x40|0x80|0x20|0x08);
			LCD_WIDTH  = 320;
			LCD_HEIGHT = 240;
			break;
		default:
			//EXIT IF SCREEN ROTATION NOT VALID!
			break;
	}
}

/*Enable LCD display*/
void ILI9341_Enable(void)
{
// HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);
	GPIO_WritePin(&RST, GPIO_PIN_SET);

}

/*Initialize LCD display*/
void ILI9341_Init(void)
{

ILI9341_SPI_Init();
ILI9341_Enable();
ILI9341_Reset();

//SOFTWARE RESET
ILI9341_Write_Command(0x01);
SYSTICK_DelayMs(1000);
	
//POWER CONTROL A
ILI9341_Write_Command(0xCB);
ILI9341_Write_Data(0x39);
ILI9341_Write_Data(0x2C);
ILI9341_Write_Data(0x00);
ILI9341_Write_Data(0x34);
ILI9341_Write_Data(0x02);

//POWER CONTROL B
ILI9341_Write_Command(0xCF);
ILI9341_Write_Data(0x00);
ILI9341_Write_Data(0xC1);
ILI9341_Write_Data(0x30);

//DRIVER TIMING CONTROL A
ILI9341_Write_Command(0xE8);
ILI9341_Write_Data(0x85);
ILI9341_Write_Data(0x00);
ILI9341_Write_Data(0x78);

//DRIVER TIMING CONTROL B
ILI9341_Write_Command(0xEA);
ILI9341_Write_Data(0x00);
ILI9341_Write_Data(0x00);

//POWER ON SEQUENCE CONTROL
ILI9341_Write_Command(0xED);
ILI9341_Write_Data(0x64);
ILI9341_Write_Data(0x03);
ILI9341_Write_Data(0x12);
ILI9341_Write_Data(0x81);

//PUMP RATIO CONTROL
ILI9341_Write_Command(0xF7);
ILI9341_Write_Data(0x20);

//POWER CONTROL,VRH[5:0]
ILI9341_Write_Command(0xC0);
ILI9341_Write_Data(0x23);

//POWER CONTROL,SAP[2:0];BT[3:0]
ILI9341_Write_Command(0xC1);
ILI9341_Write_Data(0x10);

//VCM CONTROL
ILI9341_Write_Command(0xC5);
ILI9341_Write_Data(0x3E);
ILI9341_Write_Data(0x28);

//VCM CONTROL 2
ILI9341_Write_Command(0xC7);
ILI9341_Write_Data(0x86);

//MEMORY ACCESS CONTROL
ILI9341_Write_Command(0x36);
ILI9341_Write_Data(0x48);

//PIXEL FORMAT
ILI9341_Write_Command(0x3A);
ILI9341_Write_Data(0x55);

//FRAME RATIO CONTROL, STANDARD RGB COLOR
ILI9341_Write_Command(0xB1);
ILI9341_Write_Data(0x00);
ILI9341_Write_Data(0x18);

//DISPLAY FUNCTION CONTROL
ILI9341_Write_Command(0xB6);
ILI9341_Write_Data(0x08);
ILI9341_Write_Data(0x82);
ILI9341_Write_Data(0x27);

//3GAMMA FUNCTION DISABLE
ILI9341_Write_Command(0xF2);
ILI9341_Write_Data(0x00);

//GAMMA CURVE SELECTED
ILI9341_Write_Command(0x26);
ILI9341_Write_Data(0x01);

//POSITIVE GAMMA CORRECTION
ILI9341_Write_Command(0xE0);
ILI9341_Write_Data(0x0F);
ILI9341_Write_Data(0x31);
ILI9341_Write_Data(0x2B);
ILI9341_Write_Data(0x0C);
ILI9341_Write_Data(0x0E);
ILI9341_Write_Data(0x08);
ILI9341_Write_Data(0x4E);
ILI9341_Write_Data(0xF1);
ILI9341_Write_Data(0x37);
ILI9341_Write_Data(0x07);
ILI9341_Write_Data(0x10);
ILI9341_Write_Data(0x03);
ILI9341_Write_Data(0x0E);
ILI9341_Write_Data(0x09);
ILI9341_Write_Data(0x00);

//NEGATIVE GAMMA CORRECTION
ILI9341_Write_Command(0xE1);
ILI9341_Write_Data(0x00);
ILI9341_Write_Data(0x0E);
ILI9341_Write_Data(0x14);
ILI9341_Write_Data(0x03);
ILI9341_Write_Data(0x11);
ILI9341_Write_Data(0x07);
ILI9341_Write_Data(0x31);
ILI9341_Write_Data(0xC1);
ILI9341_Write_Data(0x48);
ILI9341_Write_Data(0x08);
ILI9341_Write_Data(0x0F);
ILI9341_Write_Data(0x0C);
ILI9341_Write_Data(0x31);
ILI9341_Write_Data(0x36);
ILI9341_Write_Data(0x0F);

//EXIT SLEEP
ILI9341_Write_Command(0x11);
SYSTICK_DelayMs(120);

//TURN ON DISPLAY
ILI9341_Write_Command(0x29);

//STARTING ROTATION
ILI9341_Set_Rotation(SCREEN_VERTICAL_1);
}


//INTERNAL FUNCTION OF LIBRARY, USAGE NOT RECOMENDED, USE Draw_Pixel INSTEAD
/*Sends single pixel colour information to LCD*/
void ILI9341_Draw_Colour(uint16_t Colour)
{
//SENDS COLOUR
unsigned char TempBuffer[2] = {Colour>>8, Colour};	
GPIO_WritePin(&DC, GPIO_PIN_SET);
GPIO_WritePin(&CS, GPIO_PIN_RESET);
SPI_Transmit(&hspi1, TempBuffer, 2);
GPIO_WritePin(&CS, GPIO_PIN_SET);
	
// HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
// HAL_SPI_Transmit(HSPI_INSTANCE, TempBuffer, 2, 1);	
// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}

//INTERNAL FUNCTION OF LIBRARY
/*Sends block colour information to LCD*/
void ILI9341_Draw_Colour_Burst(uint16_t Colour, uint32_t Size)
{
//SENDS COLOUR
	
GPIO_WritePin(&DC, GPIO_PIN_SET);
GPIO_WritePin(&CS, GPIO_PIN_RESET);
if((Size*2) < BURST_MAX_SIZE)
{
	Color_bufferSize = Size;
}
else
{
	Color_bufferSize = BURST_MAX_SIZE;
}

unsigned char shifted = 	Colour>>8;;
for(uint32_t j = 0; j < Color_bufferSize; j+=2)
{
	Color_buffer[j] = 	shifted;
	Color_buffer[j+1] = Colour;
}
uint32_t Sending_Size = Size*2;
Color_burstSize = Sending_Size/Color_bufferSize;
uint32_t Remainder_from_block = Sending_Size%Color_bufferSize;

#if BENCHMARK_ENABLE
TotalSize += Sending_Size;
ILI9341_StartBenchmark();
#endif

#if TRANSMIT_MODE == DMA_MODE
if(Color_burstSize)
{
	SPI_TransmitDMA(&hspi1, (unsigned char *)Color_buffer, Color_bufferSize);
}

#else
if(Color_burstSize != 0)
{
	for(uint32_t j = 0; j < (Color_burstSize); j++)
		{
		SPI_Transmit(&hspi1, (unsigned char *)Color_buffer, Color_bufferSize);
		//HAL_SPI_Transmit(HSPI_INSTANCE, (unsigned char *)burst_buffer, Buffer_Size, 10);	
		}
}

#if BENCHMARK_ENABLE
/* Stop Benchmark */
ILI9341_StopBenchmark();
#endif

/* Transmit Remainder if exists */
SPI_Transmit(&hspi1, (unsigned char *)Color_buffer, Remainder_from_block);
GPIO_WritePin(&CS, GPIO_PIN_SET);

#endif

}

//FILL THE ENTIRE SCREEN WITH SELECTED COLOUR (either #define-d ones or custom 16bit)
/*Sets address (entire screen) and Sends Height*Width ammount of colour information to LCD*/
void ILI9341_Fill_Screen(uint16_t Colour)
{
ILI9341_Set_Address(0,0,LCD_WIDTH-1,LCD_HEIGHT-1);	
ILI9341_Draw_Colour_Burst(Colour, LCD_WIDTH*LCD_HEIGHT);	
}

//DRAW PIXEL AT XY POSITION WITH SELECTED COLOUR
//
//Location is dependant on screen orientation. x0 and y0 locations change with orientations.
//Using pixels to draw big simple structures is not recommended as it is really slow
//Try using either rectangles or lines if possible
//
void ILI9341_Draw_Pixel(uint16_t X,uint16_t Y,uint16_t Colour) 
{
if((X >=LCD_WIDTH) || (Y >=LCD_HEIGHT)) return;	//OUT OF BOUNDS!
	
//ADDRESS
GPIO_WritePin(&DC, GPIO_PIN_RESET);
GPIO_WritePin(&CS, GPIO_PIN_RESET);
ILI9341_SPI_Send(0x2A);
GPIO_WritePin(&DC, GPIO_PIN_SET);
GPIO_WritePin(&CS, GPIO_PIN_SET);

// HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);	
// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
// ILI9341_SPI_Send(0x2A);
// HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);	
// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);		

//XDATA
GPIO_WritePin(&CS, GPIO_PIN_RESET);
unsigned char Temp_Buffer[4] = {X>>8,X, (X+1)>>8, (X+1)};
SPI_Transmit(&hspi1, Temp_Buffer, 4);
GPIO_WritePin(&CS, GPIO_PIN_SET);

// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);	
// unsigned char Temp_Buffer[4] = {X>>8,X, (X+1)>>8, (X+1)};
// HAL_SPI_Transmit(HSPI_INSTANCE, Temp_Buffer, 4, 1);
// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);

//ADDRESS
GPIO_WritePin(&DC, GPIO_PIN_RESET);
GPIO_WritePin(&CS, GPIO_PIN_RESET);
ILI9341_SPI_Send(0x2B);
GPIO_WritePin(&DC, GPIO_PIN_SET);
GPIO_WritePin(&CS, GPIO_PIN_SET);

// HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);	
// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);	
// ILI9341_SPI_Send(0x2B);
// HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);			
// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);			

//YDATA
GPIO_WritePin(&CS, GPIO_PIN_RESET);
unsigned char Temp_Buffer1[4] = {Y>>8,Y, (Y+1)>>8, (Y+1)};
SPI_Transmit(&hspi1, Temp_Buffer1, 4);
GPIO_WritePin(&CS, GPIO_PIN_SET);

// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
// unsigned char Temp_Buffer1[4] = {Y>>8,Y, (Y+1)>>8, (Y+1)};
// HAL_SPI_Transmit(HSPI_INSTANCE, Temp_Buffer1, 4, 1);
// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);

//ADDRESS	
GPIO_WritePin(&DC, GPIO_PIN_RESET);
GPIO_WritePin(&CS, GPIO_PIN_RESET);
ILI9341_SPI_Send(0x2C);
GPIO_WritePin(&DC, GPIO_PIN_SET);
GPIO_WritePin(&CS, GPIO_PIN_SET);

// HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);	
// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);	
// ILI9341_SPI_Send(0x2C);
// HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);			
// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);			

//COLOUR	
GPIO_WritePin(&CS, GPIO_PIN_RESET);
unsigned char Temp_Buffer2[2] = {Colour>>8, Colour};
SPI_Transmit(&hspi1, Temp_Buffer2, 2);
GPIO_WritePin(&CS, GPIO_PIN_SET);

// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
// unsigned char Temp_Buffer2[2] = {Colour>>8, Colour};
// HAL_SPI_Transmit(HSPI_INSTANCE, Temp_Buffer2, 2, 1);
// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
	
}

//DRAW RECTANGLE OF SET SIZE AND HEIGTH AT X and Y POSITION WITH CUSTOM COLOUR
//
//Rectangle is hollow. X and Y positions mark the upper left corner of rectangle
//As with all other draw calls x0 and y0 locations dependant on screen orientation
//

void ILI9341_Draw_Rectangle(uint16_t X, uint16_t Y, uint16_t Width, uint16_t Height, uint16_t Colour)
{
if((X >=LCD_WIDTH) || (Y >=LCD_HEIGHT)) return;
if((X+Width-1)>=LCD_WIDTH)
	{
		Width=LCD_WIDTH-X;
	}
if((Y+Height-1)>=LCD_HEIGHT)
	{
		Height=LCD_HEIGHT-Y;
	}
ILI9341_Set_Address(X, Y, X+Width-1, Y+Height-1);
ILI9341_Draw_Colour_Burst(Colour, Height*Width);
}

//DRAW LINE FROM X,Y LOCATION to X+Width,Y LOCATION
void ILI9341_Draw_Horizontal_Line(uint16_t X, uint16_t Y, uint16_t Width, uint16_t Colour)
{
if((X >=LCD_WIDTH) || (Y >=LCD_HEIGHT)) return;
if((X+Width-1)>=LCD_WIDTH)
	{
		Width=LCD_WIDTH-X;
	}
ILI9341_Set_Address(X, Y, X+Width-1, Y);
ILI9341_Draw_Colour_Burst(Colour, Width);
}

//DRAW LINE FROM X,Y LOCATION to X,Y+Height LOCATION
void ILI9341_Draw_Vertical_Line(uint16_t X, uint16_t Y, uint16_t Height, uint16_t Colour)
{
if((X >=LCD_WIDTH) || (Y >=LCD_HEIGHT)) return;
if((Y+Height-1)>=LCD_HEIGHT)
	{
		Height=LCD_HEIGHT-Y;
	}
ILI9341_Set_Address(X, Y, X, Y+Height-1);
ILI9341_Draw_Colour_Burst(Colour, Height);
}

