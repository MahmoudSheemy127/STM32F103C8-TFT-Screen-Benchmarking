#include "Drivers/SPI/SPI.h"


HAL_Status SPI_Init(SPI_HandleTypeDef* hspi)
{
    HAL_Status status = HAL_OKAY;

    if(NULL == hspi)
    {
        status = HAL_ERROR;
    }
    else
    {
        
        /* Enable SPI */
        SET_BIT(hspi->Instance->CR1, SPI_CR1_SPE);
        /* Set SPI mode */
        if(hspi->Mode == SPI_MODE_MASTER)
        {
            SET_BIT(hspi->Instance->CR1, SPI_CR1_MSTR);
        }
        else if(hspi->Mode == SPI_MODE_SLAVE)
        {
            CLR_BIT(hspi->Instance->CR1, SPI_CR1_MSTR);
        }
        else
        {
            status = HAL_ERROR;
        }
        /* Set SPI Data Size */
        if(hspi->DataSize == SPI_DATASIZE_8BIT)
        {
            CLR_BIT(hspi->Instance->CR1, SPI_CR1_DFF);
        }
        else if(hspi->DataSize == SPI_DATASIZE_16BIT)
        {
            SET_BIT(hspi->Instance->CR1, SPI_CR1_DFF);
        }
        else
        {
            status = HAL_ERROR;
        }
        /* Set SPI Clock Polarity */
        if(hspi->CPOL == SPI_CPOL_LOW)
        {
            CLR_BIT(hspi->Instance->CR1, SPI_CR1_CPOL);
        }
        else if(hspi->CPOL == SPI_CPOL_HIGH)
        {
            SET_BIT(hspi->Instance->CR1, SPI_CR1_CPOL);
        }
        else
        {
           status = HAL_ERROR;
        }
        /* Set SPI Clock Phase */
        if(hspi->CPHA == SPI_CPHA_1EDGE)
        {
            CLR_BIT(hspi->Instance->CR1, SPI_CR1_CPHA);
        }
        else if(hspi->CPHA == SPI_CPHA_2EDGE)
        {
            SET_BIT(hspi->Instance->CR1, SPI_CR1_CPHA);
        }
        else
        {
            status = HAL_ERROR;
        }
        /* Set SPI Slave Select */
        if(hspi->NSS == SPI_NSS_HARD)
        {
            CLR_BIT(hspi->Instance->CR1, SPI_CR1_SSM);
        }
        else if(hspi->NSS == SPI_NSS_SOFT)
        {
            SET_BIT(hspi->Instance->CR1, SPI_CR1_SSM);
        }
        else
        {
            status = HAL_ERROR;
        }
        /* Set SPI Baud Rate */
        switch(hspi->BaudRate)
        {
            case SPI_BAUDRATE_DIV2:
                // Code for SPI_BAUD_RATE_DIV
                MODIFY_REG(hspi->Instance->CR1, SPI_BR_MSK , SPI_BAUDRATE_DIV2 << SPI_CR1_BR);
                break;
            // Add more cases for other baud rates
            case SPI_BAUDRATE_DIV4:
                // Code for SPI_BAUDRATE_DIV4
                MODIFY_REG(hspi->Instance->CR1, SPI_BR_MSK, SPI_BAUDRATE_DIV4 << SPI_CR1_BR);
                break;
            case SPI_BAUDRATE_DIV8:
                // Code for SPI_BAUDRATE_DIV8
                MODIFY_REG(hspi->Instance->CR1, SPI_BR_MSK, SPI_BAUDRATE_DIV8 << SPI_CR1_BR);
                break;
            case SPI_BAUDRATE_DIV16:
                // Code for SPI_BAUDRATE_DIV16
                MODIFY_REG(hspi->Instance->CR1, SPI_BR_MSK, SPI_BAUDRATE_DIV16 << SPI_CR1_BR);
                break;  
            case SPI_BAUDRATE_DIV32:
                // Code for SPI_BAUDRATE_DIV32
                MODIFY_REG(hspi->Instance->CR1, SPI_BR_MSK, SPI_BAUDRATE_DIV32 << SPI_CR1_BR);
                break;
            case SPI_BAUDRATE_DIV64:
                // Code for SPI_BAUDRATE_DIV64
                MODIFY_REG(hspi->Instance->CR1, SPI_BR_MSK, SPI_BAUDRATE_DIV64 << SPI_CR1_BR);
                break;
            case SPI_BAUDRATE_DIV128:
                // Code for SPI_BAUDRATE_DIV128
                MODIFY_REG(hspi->Instance->CR1, SPI_BR_MSK, SPI_BAUDRATE_DIV128 << SPI_CR1_BR);
                break;
            case SPI_BAUDRATE_DIV256:
                // Code for SPI_BAUDRATE_DIV256
                MODIFY_REG(hspi->Instance->CR1, SPI_BR_MSK, SPI_BAUDRATE_DIV256 << SPI_CR1_BR);
                break;
            default:
                /*------ Take some action ---- */
                status = HAL_ERROR;
                break;
        }

    }
    return status;
}

/**
 * @brief SPI (Master or slave) transmit function using pooling 
 * 
 * @param hspi 
 * @param pData 
 * @param Size 
 * @param Timeout 
 * @return HAL_Status 
 */

HAL_Status SPI_Transmit(SPI_HandleTypeDef* hspi, uint8_t* pData, uint32_t Size, uint32_t Timeout)
{
    HAL_Status status = HAL_OKAY;
    if((NULL == hspi) || (NULL == pData))
    {
        status = HAL_ERROR;
    }
    else
    {
           /* Init TX counter */
           uint32_t counter = 0;
           /* Check size */
           if(hspi->DataSize == SPI_DATASIZE_8BIT)
           {
            /* 8-bit DataSize */
            while(counter < Size)
            {
                /* Check TXE flag (Polling mode) */
                while(!GET_BIT(hspi->Instance->SR,SPI_SR_TXE));
                hspi->Instance->DR = (uint8_t)pData[counter];
                counter++;
            }
           }
           else
            {
            /* 16-bit DataSize */
            while(counter < Size)
            {
                /* Check TXE flag (Polling mode) */
                while(!GET_BIT(hspi->Instance->SR,SPI_SR_TXE));
                hspi->Instance->DR = (uint16_t)pData[counter];
                counter++;
            }           
            }
    }
    return status;
}


/**
 * @brief SPI (Master or slave) receive function using pooling
 * 
 * @param hspi 
 * @param pData 
 * @param Size 
 * @param Timeout 
 * @return HAL_Status 
 **/

HAL_Status SPI_Receive(SPI_HandleTypeDef* hspi, uint8_t* pData, uint32_t Size, uint32_t Timeout)
{
    HAL_Status status = HAL_OKAY;
    if((NULL == hspi) || (NULL == pData))
    {
        status = HAL_ERROR;
    }
    else
    {
           /* Init TX counter */
           uint32_t counter = 0;
           /* Check size */
           if(hspi->DataSize == SPI_DATASIZE_8BIT)
           {
            /* 8-bit DataSize */
            while(counter < Size)
            {
                /* Check RXNE flag (Polling mode) */
                while(!GET_BIT(hspi->Instance->SR,SPI_SR_RXNE));
                pData[counter] = (uint8_t)hspi->Instance->DR;
                counter++;
            }
           }
           else
            {
            /* 16-bit DataSize */
            while(counter < Size)
            {
                /* Check RXNE flag (Polling mode) */
                while(!GET_BIT(hspi->Instance->SR,SPI_SR_RXNE));
                pData[counter] = (uint16_t)hspi->Instance->DR;
                counter++;
            }           
            }
    }
    return status;    
}