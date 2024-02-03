/* HEADER GUARD */
#ifndef SPI_H
#define SPI_H

/*----------START INCLUDES----------*/
#include "Drivers/Common/Common.h"
#include "Std_Types.h"
/*----------END INCLUDES------------*/

/*----------START MACROS----------*/
#define SPI1_BASE			(APB2_BASE+0x3000UL)
#define SPI2_BASE			(APB1_BASE+0x3800UL)
#define SPI1                ((SPI_TypeDef*)SPI1_BASE)
#define SPI2                ((SPI_TypeDef*)SPI2_BASE)

/* BIT POSITIONS */
#define SPI_CR1_CPHA       (0UL)
#define SPI_CR1_CPOL       (1UL)
#define SPI_CR1_MSTR       (2UL)
#define SPI_CR1_BR         (3UL)
#define SPI_CR1_SPE        (6UL)
#define SPI_CR1_LSBFIRST   (7UL)
#define SPI_CR1_SSI        (8UL)
#define SPI_CR1_SSM        (9UL)
#define SPI_CR1_RXONLY     (10UL)
#define SPI_CR1_DFF        (11UL)
#define SPI_CR1_CRCNEXT    (12UL)
#define SPI_CR1_CRCEN      (13UL)
#define SPI_CR1_BIDIOE     (14UL)
#define SPI_CR1_BIDIMODE   (15UL)
#define SPI_CR1_CRCL       (11UL)
#define SPI_CR1_CRCH       (12UL)
#define SPI_CR1_CRCPL      (13UL)
#define SPI_CR1_CRCIEN     (14UL)
#define SPI_CR1_CRCOEN     (15UL)
#define SPI_SR_TXE         (1)
#define SPI_SR_RXNE        (0)

/* SPI PINS */
#define PORT_SPI1          GPIOA
#define MOSI_SPI1          GPIO_PIN_7
#define MISO_SPI1          GPIO_PIN_6
#define SCK_SPI1           GPIO_PIN_5
#define NSS_SPI1           GPIO_PIN_4

#define PORT_SPI2          GPIOB
#define MOSI_SPI2          GPIO_PIN_15
#define MISO_SPI2          GPIO_PIN_14
#define SCK_SPI2           GPIO_PIN_13
#define NSS_SPI2           GPIO_PIN_12

#define SPI_BR_MSK         (0x7UL << SPI_CR1_BR)



/*----------END MACROS------------*/

/*----------START MACRO-LIKE FUNCTION----------*/
/*----------END MACRO-LIKE FUNCTION------------*/


/*----------START DATATYPES----------*/

/* DEFINE SOME CONFIG ENUMS */
typedef enum{
    SPI_MODE_MASTER = 0x00UL,
    SPI_MODE_SLAVE = 0x01UL
}SPI_Mode;

typedef enum{
    SPI_BAUDRATE_DIV2 = 0x00UL,
    SPI_BAUDRATE_DIV4 = 0x01UL,
    SPI_BAUDRATE_DIV8 = 0x02UL,
    SPI_BAUDRATE_DIV16 = 0x03UL,
    SPI_BAUDRATE_DIV32 = 0x04UL,
    SPI_BAUDRATE_DIV64 = 0x05UL,
    SPI_BAUDRATE_DIV128 = 0x06UL,
    SPI_BAUDRATE_DIV256 = 0x07UL
}SPI_BaudRate;

typedef enum{
    SPI_CPOL_LOW = 0x00UL,
    SPI_CPOL_HIGH = 0x01UL
}SPI_CPOL;

typedef enum{
    SPI_CPHA_1EDGE = 0x00UL,
    SPI_CPHA_2EDGE = 0x01UL
}SPI_CPHA;

typedef enum{
    SPI_MSB_FIRST = 0x00UL,
    SPI_LSB_FIRST = 0x01UL
}SPI_FirstBit;

typedef enum{
    SPI_DATASIZE_8BIT = 0x00UL,
    SPI_DATASIZE_16BIT = 0x01UL
}SPI_DataSize;

typedef enum{
    SPI_NSS_SOFT = 0x00UL,
    SPI_NSS_HARD = 0x01UL
}SPI_NSS;

typedef enum{
    SPI_BIDIR_DISABLE = 0x00UL,
    SPI_BIDIR_ENABLE = 0x01UL
}SPI_BiDir;

typedef enum{
    SPI_CRC_DISABLE = 0x00UL,
    SPI_CRC_ENABLE = 0x01UL
}SPI_CRC;

typedef enum{
    SPI_CRC_POLYNOMIAL_7BIT = 0x00UL,
    SPI_CRC_POLYNOMIAL_8BIT = 0x01UL,
    SPI_CRC_POLYNOMIAL_16BIT = 0x02UL,
    SPI_CRC_POLYNOMIAL_32BIT = 0x03UL
}SPI_CRC_Polynomial;

typedef enum{
    SPI_CRC_RX = 0x00UL,
    SPI_CRC_TX = 0x01UL
}SPI_CRC_DIR;




typedef struct{
    uint32_t CR1;		//0x00
    uint32_t CR2;		//0x04
    uint32_t SR;		//0x08
    uint32_t DR;		//0x0C
    uint32_t CRCPR;	//0x10
    uint32_t RXCRCR;	//0x14
    uint32_t TXCRCR;	//0x18
    uint32_t I2SCFGR;	//0x1C
    uint32_t I2SPR;	//0x20
}SPI_TypeDef;

typedef struct{
    SPI_TypeDef* Instance;
    SPI_Mode Mode;
    SPI_BaudRate BaudRate;
    SPI_CPOL CPOL;
    SPI_CPHA CPHA;
    SPI_FirstBit FirstBit;
    SPI_DataSize DataSize;
    SPI_NSS NSS;
    SPI_BiDir BiDir;
    SPI_CRC CRC;
    SPI_CRC_Polynomial CRCPolynomial;
    SPI_CRC_DIR CRCDir;
}SPI_HandleTypeDef;
/*----------END DATATYPES------------*/

/*----------START FUNCTION PROTOTYPES----------*/
HAL_Status SPI_Init(SPI_HandleTypeDef* hspi);
HAL_Status SPI_Transmit(SPI_HandleTypeDef* hspi, uint8_t* pData, uint32_t Size, uint32_t Timeout);
HAL_Status SPI_Receive(SPI_HandleTypeDef* hspi, uint8_t* pData, uint32_t Size, uint32_t Timeout);
HAL_Status SPI_TransmitReceive(SPI_HandleTypeDef* hspi, uint8_t* pTxData, uint8_t* pRxData, uint32_t Size, uint32_t Timeout);
HAL_Status SPI_DeInit(SPI_HandleTypeDef* hspi);
HAL_Status SPI_Transmit_IT(SPI_HandleTypeDef* hspi, uint8_t* pData, uint32_t Size);
HAL_Status SPI_Receive_IT(SPI_HandleTypeDef* hspi, uint8_t* pData, uint32_t Size);

/*----------END FUNCTION PROTOTYPES------------*/


#endif
