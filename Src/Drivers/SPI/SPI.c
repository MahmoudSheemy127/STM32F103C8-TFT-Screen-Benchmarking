#include "SPI/SPI.h"


HAL_Status SPI_Init(SPI_HandleTypeDef* hspi)
{
    HAL_Status status = HAL_OK;

    if(NULL == hspi)
    {
        status = HAL_ERROR;
    }
    else
    {
        /* Enable SPI */
        SET_BIT(hspi->Instance->CR1, SPI_CR1_SPE);
        /* Set SPI mode */
        if(hspi->SPI_Mode == SPI_MODE_MASTER)
        {
            SET_BIT(hspi->Instance->CR1, SPI_CR1_MSTR);
        }
        else if(hspi->SPI_Mode == SPI_MODE_SLAVE)
        {
            CLR_BIT(hspi->Instance->CR1, SPI_CR1_MSTR);
        }
        else
        {
            status = HAL_ERROR;
        }
        /* Set SPI Data Size */
        if(hspi->SPI_DataSize == SPI_DATASIZE_8BIT)
        {
            CLR_BIT(hspi->Instance->CR1, SPI_CR1_DFF);
        }
        else if(hspi->SPI_DataSize == SPI_DATASIZE_16BIT)
        {
            SET_BIT(hspi->Instance->CR1, SPI_CR1_DFF);
        }
        else
        {
            status = HAL_ERROR;
        }
        /* Set SPI Clock Polarity */
        if(hspi->SPI_ClockPolarity == SPI_CPOL_LOW)
        {
            CLR_BIT(hspi->Instance->CR1, SPI_CR1_CPOL);
        }
        else if(hspi->SPI_ClockPolarity == SPI_CPOL_HIGH)
        {
            SET_BIT(hspi->Instance->CR1, SPI_CR1_CPOL);
        }
        else
        {
           status = HAL_ERROR;
        }
        /* Set SPI Clock Phase */
        if(hspi->SPI_ClockPhase == SPI_CPHA_1EDGE)
        {
            CLR_BIT(hspi->Instance->CR1, SPI_CR1_CPHA);
        }
        else if(hspi->SPI_ClockPhase == SPI_CPHA_2EDGE)
        {
            SET_BIT(hspi->Instance->CR1, SPI_CR1_CPHA);
        }
        else
        {
            status = HAL_ERROR;
        }
        /* Set SPI Slave Select */
        if(hspi->SPI_SlaveSelect == SPI_NSS_HARD)
        {
            CLR_BIT(hspi->Instance->CR1, SPI_CR1_SSM);
        }
        else if(hspi->SPI_SlaveSelect == SPI_NSS_SOFT)
        {
            SET_BIT(hspi->Instance->CR1, SPI_CR1_SSM);
        }
        else
        {
            status = HAL_ERROR;
        }
        /* Set SPI Baud Rate */
        switch(hspi->SPI_BaudRate)
        {
            case SPI_BAUDRATE_DIV2:
                // Code for SPI_BAUD_RATE_DIV2
                MODIFY_REG(hspi->Instance->CR1, SPI_CR1_BR, SPI_BAUD_RATE_DIV2 << SPI_CR1_BR_Pos);
                break;
            // Add more cases for other baud rates
            case SPI_BAUDRATE_DIV4:
                // Code for SPI_BAUDRATE_DIV4
                MODIFY_REG(hspi->Instance->CR1, SPI_CR1_BR, SPI_BAUD_RATE_DIV4 << SPI_CR1_BR_Pos);

                break;
            case SPI_BAUDRATE_DIV8:
                // Code for SPI_BAUDRATE_DIV8
                MODIFY_REG(hspi->Instance->CR1, SPI_CR1_BR, SPI_BAUD_RATE_DIV8 << SPI_CR1_BR_Pos);
                break;
            case SPI_BAUDRATE_DIV16:
                // Code for SPI_BAUDRATE_DIV16
                MODIFY_REG(hspi->Instance->CR1, SPI_CR1_BR, SPI_BAUD_RATE_DIV16 << SPI_CR1_BR_Pos);
                break;  
            case SPI_BAUDRATE_DIV32:
                // Code for SPI_BAUDRATE_DIV32
                MODIFY_REG(hspi->Instance->CR1, SPI_CR1_BR, SPI_BAUD_RATE_DIV32 << SPI_CR1_BR_Pos);
                break;
            case SPI_BAUDRATE_DIV64:
                // Code for SPI_BAUDRATE_DIV64
                MODIFY_REG(hspi->Instance->CR1, SPI_CR1_BR, SPI_BAUD_RATE_DIV64 << SPI_CR1_BR_Pos);
                break;
            case SPI_BAUDRATE_DIV128:
                // Code for SPI_BAUDRATE_DIV128
                MODIFY_REG(hspi->Instance->CR1, SPI_CR1_BR, SPI_BAUD_RATE_DIV128 << SPI_CR1_BR_Pos);
                break;
            case SPI_BAUDRATE_DIV256:
                // Code for SPI_BAUDRATE_DIV256
                MODIFY_REG(hspi->Instance->CR1, SPI_CR1_BR, SPI_BAUD_RATE_DIV256 << SPI_CR1_BR_Pos);
                break;
            default:
                /*------ Take some action ---- */
                status = HAL_ERROR;
                break;
        }

    }
    return status;
}