#include "SPI/SPI.h"


HAL_Status SPI_Init(SPI_HandleTypeDef* hspi)
{
    /* Enable SPI */
    SET_BIT(SPI1->CR1, SPI_CR1_SPE);
    /* Set SPI mode */
    if(hspi->SPI_Mode == SPI_MASTER)
    {
        SET_BIT(SPI1->CR1, SPI_CR1_MSTR);
    }
    else if(hspi->SPI_Mode == SPI_SLAVE)
    {
        CLR_BIT(SPI1->CR1, SPI_CR1_MSTR);
    }
    else
    {
        /*------ Take some action ---- */
    }
    /* Set SPI Data Size */
    if(hspi->SPI_DataSize == SPI_8BIT)
    {
        CLR_BIT(SPI1->CR1, SPI_CR1_DFF);
    }
    else if(hspi->SPI_DataSize == SPI_16BIT)
    {
        SET_BIT(SPI1->CR1, SPI_CR1_DFF);
    }
    else
    {
        /*------ Take some action ---- */
    }
    /* Set SPI Clock Polarity */
    if(hspi->SPI_ClockPolarity == SPI_CPOL_LOW)
    {
        CLR_BIT(SPI1->CR1, SPI_CR1_CPOL);
    }
    else if(hspi->SPI_ClockPolarity == SPI_CPOL_HIGH)
    {
        SET_BIT(SPI1->CR1, SPI_CR1_CPOL);
    }
    else
    {
        /*------ Take some action ---- */
    }
    /* Set SPI Clock Phase */
    if(hspi->SPI_ClockPhase == SPI_CPHA_LOW)
    {
        CLR_BIT(SPI1->CR1, SPI_CR1_CPHA);
    }
    else if(hspi->SPI_ClockPhase == SPI_CPHA_HIGH)
    {
        SET_BIT(SPI1->CR1, SPI_CR1_CPHA);
    }
    else
    {
        /*------ Take some action ---- */
    }
    /* Set SPI Slave Select */
    if(hspi->SPI_SlaveSelect == SPI_NSS_HARD)
    {
        CLR_BIT(SPI1->CR1, SPI_CR1_SSM);
    }
    else if(hspi->SPI_SlaveSelect == SPI_NSS_SOFT)
    {
        SET_BIT(SPI1->CR1, SPI_CR1_SSM);
    }
    else
    {
        /*------ Take some action ---- */
    }
    /* Set SPI Baud Rate */
    switch(hspi->SPI_BaudRate)
    {
        case SPI_BAUD_RATE_DIV2:
            // Code for SPI_BAUD_RATE_DIV2
            break;
        // Add more cases for other baud rates
        case SPI_BAUDRATE_DIV4:
            // Code for SPI_BAUDRATE_DIV4
            break;
        case SPI_BAUDRATE_DIV8:
            // Code for SPI_BAUDRATE_DIV8
            break;
        case SPI_BAUDRATE_DIV16:
            // Code for SPI_BAUDRATE_DIV16
            break;  
        case SPI_BAUDRATE_DIV32:
            // Code for SPI_BAUDRATE_DIV32
            break;
        case SPI_BAUDRATE_DIV64:
            // Code for SPI_BAUDRATE_DIV64
            break;
        case SPI_BAUDRATE_DIV128:
            // Code for SPI_BAUDRATE_DIV128
            break;
        case SPI_BAUDRATE_DIV256:
            // Code for SPI_BAUDRATE_DIV256
            break;
            

        default:
            /*------ Take some action ---- */
            break;
    }
    


}