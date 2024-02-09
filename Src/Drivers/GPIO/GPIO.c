/*
 * GPIO.c
 *
 *  Created on: Nov 19, 2023
 *      Author: mahmo
 */

#include "Drivers/GPIO/GPIO.h"

HAL_Status GPIO_Init(GPIO_HandleTypeDef* gpio_handle)
{
    HAL_Status status = HAL_OKAY;
    if(NULL == gpio_handle)
    {
        status = HAL_ERROR;
    }
    else
    {
        /* Check if pin number is less than 8 */
        if(gpio_handle->GPIO_Pin < GPIO_PIN_8)
        {
            /* Check Mode */
            switch(gpio_handle->GPIO_Mode)
            {
                case GPIO_MODE_INPUT:
                    gpio_handle->GPIO_TypeDef->CRL &= ~(0x0FUL << (gpio_handle->GPIO_Pin * 4));
                    gpio_handle->GPIO_TypeDef->CRL |= (0x04UL << (gpio_handle->GPIO_Pin * 4));
                    break;
                case GPIO_MODE_OUTPUT_10MHZ:
                    gpio_handle->GPIO_TypeDef->CRL &= ~(0x0FUL << (gpio_handle->GPIO_Pin * 4));
                    gpio_handle->GPIO_TypeDef->CRL |= (0x01UL << (gpio_handle->GPIO_Pin * 4));
                    break;
                case GPIO_MODE_OUTPUT_2MHZ:
                    gpio_handle->GPIO_TypeDef->CRL &= ~(0x0FUL << (gpio_handle->GPIO_Pin * 4));
                    gpio_handle->GPIO_TypeDef->CRL |= (0x02UL << (gpio_handle->GPIO_Pin * 4));
                    break;
                case GPIO_MODE_OUTPUT_50MHZ:
                    gpio_handle->GPIO_TypeDef->CRL &= ~(0x0FUL << (gpio_handle->GPIO_Pin * 4));
                    gpio_handle->GPIO_TypeDef->CRL |= (0x03UL << (gpio_handle->GPIO_Pin * 4));
                    break;
                default:
                    status = HAL_ERROR;
                    break;
            }
            /* Check Configuration */
            switch(gpio_handle->GPIO_CNF)
            {
                case GPIO_CNF_INPUT_ANALOG:
                case GPIO_CNF_OUTPUT_PUSH_PULL:
                    gpio_handle->GPIO_TypeDef->CRL &= ~(0x03UL << (gpio_handle->GPIO_Pin * 4 + 2));
                    break;
                case GPIO_CNF_INPUT_FLOATING:
                case GPIO_CNF_OUTPUT_OPEN_DRAIN:
                    gpio_handle->GPIO_TypeDef->CRL &= ~(0x03UL << (gpio_handle->GPIO_Pin * 4 + 2));
                    gpio_handle->GPIO_TypeDef->CRL |= (0x01UL << (gpio_handle->GPIO_Pin * 4 + 2));
                    break;
                case GPIO_CNF_INPUT_PULL:
                case GPIO_CNF_OUTPUT_ALTFN_PUSH_PULL:
                    gpio_handle->GPIO_TypeDef->CRL &= ~(0x03UL << (gpio_handle->GPIO_Pin * 4 + 2));
                    gpio_handle->GPIO_TypeDef->CRL |= (0x02UL << (gpio_handle->GPIO_Pin * 4 + 2));
                    break;
                case GPIO_CNF_OUTPUT_ALTFN_OPEN_DRAIN:
                    gpio_handle->GPIO_TypeDef->CRL &= ~(0x03UL << (gpio_handle->GPIO_Pin * 4 + 2));
                    gpio_handle->GPIO_TypeDef->CRL |= (0x03UL << (gpio_handle->GPIO_Pin * 4 + 2));
                    break;
                default:
                    status = HAL_ERROR;
                    break;

            }
        }
        else
        {
            /* Check Mode */
            switch(gpio_handle->GPIO_Mode)
            {
                case GPIO_MODE_INPUT:
                    gpio_handle->GPIO_TypeDef->CRH &= ~(0x0FUL << ((gpio_handle->GPIO_Pin - GPIO_PIN_8) * 4));
                    gpio_handle->GPIO_TypeDef->CRH |= (0x04UL << ((gpio_handle->GPIO_Pin - GPIO_PIN_8) * 4));
                    break;
                case GPIO_MODE_OUTPUT_10MHZ:
                    gpio_handle->GPIO_TypeDef->CRH &= ~(0x0FUL << ((gpio_handle->GPIO_Pin - GPIO_PIN_8) * 4));
                    gpio_handle->GPIO_TypeDef->CRH |= (0x01UL << ((gpio_handle->GPIO_Pin - GPIO_PIN_8) * 4));
                    break;
                case GPIO_MODE_OUTPUT_2MHZ:
                    gpio_handle->GPIO_TypeDef->CRH &= ~(0x0FUL << ((gpio_handle->GPIO_Pin - GPIO_PIN_8) * 4));
                    gpio_handle->GPIO_TypeDef->CRH |= (0x02UL << ((gpio_handle->GPIO_Pin - GPIO_PIN_8) * 4));
                    break;
                case GPIO_MODE_OUTPUT_50MHZ:
                    gpio_handle->GPIO_TypeDef->CRH &= ~(0x0FUL << ((gpio_handle->GPIO_Pin - GPIO_PIN_8) * 4));
                    gpio_handle->GPIO_TypeDef->CRH |= (0x03UL << ((gpio_handle->GPIO_Pin - GPIO_PIN_8) * 4));
                    break;
                default:
                    status = HAL_ERROR;
                    break;
            }
            /* Check Configuration */
            switch(gpio_handle->GPIO_CNF)
            {
                case GPIO_CNF_INPUT_ANALOG:
                case GPIO_CNF_OUTPUT_PUSH_PULL:
                    gpio_handle->GPIO_TypeDef->CRH &= ~(0x03UL << ((gpio_handle->GPIO_Pin - GPIO_PIN_8) * 4 + 2));
                    break;
                case GPIO_CNF_INPUT_FLOATING:
                case GPIO_CNF_OUTPUT_OPEN_DRAIN:
                    gpio_handle->GPIO_TypeDef->CRH &= ~(0x03UL << ((gpio_handle->GPIO_Pin - GPIO_PIN_8) * 4 + 2));
                    gpio_handle->GPIO_TypeDef->CRH |= (0x01UL << ((gpio_handle->GPIO_Pin - GPIO_PIN_8) * 4 + 2));
                    break;
                case GPIO_CNF_INPUT_PULL:
                case GPIO_CNF_OUTPUT_ALTFN_PUSH_PULL:
                    gpio_handle->GPIO_TypeDef->CRH &= ~(0x03UL << ((gpio_handle->GPIO_Pin - GPIO_PIN_8) * 4 + 2));
                    gpio_handle->GPIO_TypeDef->CRH |= (0x02UL << ((gpio_handle->GPIO_Pin - GPIO_PIN_8) * 4 + 2));
                    break;
                case GPIO_CNF_OUTPUT_ALTFN_OPEN_DRAIN:
                    gpio_handle->GPIO_TypeDef->CRH &= ~(0x03UL << ((gpio_handle->GPIO_Pin - GPIO_PIN_8) * 4 + 2));
                    gpio_handle->GPIO_TypeDef->CRH |= (0x03UL << ((gpio_handle->GPIO_Pin - GPIO_PIN_8) * 4 + 2));
                    break;
                default:
                    status = HAL_ERROR;
                    break;
        }

    }    
    }
    return status;

}


HAL_Status GPIO_WritePin(GPIO_HandleTypeDef* gpio_handle, GPIO_PinState pin_state)
{
    HAL_Status status = HAL_OKAY;
    if(NULL == gpio_handle)
    {
        status = HAL_ERROR;
    }
    else
    {
        if(GPIO_PIN_RESET == pin_state)
        {
            gpio_handle->GPIO_TypeDef->BRR |= (1UL << gpio_handle->GPIO_Pin);
        }
        else if(GPIO_PIN_SET == pin_state)
        {
            gpio_handle->GPIO_TypeDef->BSRR |= (1UL << gpio_handle->GPIO_Pin);
        }
        else
        {
            status = HAL_ERROR;
        }
    }
    return status;
}

uint8_t GPIO_ReadPin(GPIO_HandleTypeDef* gpio_handle)
{
    uint8_t pin_state = 0;
    if(NULL != gpio_handle)
    {
        if(0 == (gpio_handle->GPIO_TypeDef->IDR & (1UL << gpio_handle->GPIO_Pin)))
        {
            pin_state = 0;
        }
        else
        {
            pin_state = 1;
        }
    }
    return pin_state;
}

HAL_Status GPIO_TogglePin(GPIO_HandleTypeDef* gpio_handle)
{
    HAL_Status status = HAL_OKAY;
    if(NULL == gpio_handle)
    {
        status = HAL_ERROR;
    }
    else
    {
        if(0 == (gpio_handle->GPIO_TypeDef->ODR & (1UL << gpio_handle->GPIO_Pin)))
        {
            gpio_handle->GPIO_TypeDef->BSRR |= (1UL << gpio_handle->GPIO_Pin);
        }
        else
        {
            gpio_handle->GPIO_TypeDef->BRR |= (1UL << gpio_handle->GPIO_Pin);
        }
    }
    return status;
}


