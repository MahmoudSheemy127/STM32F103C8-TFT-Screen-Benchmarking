#include "Drivers/TIM/TIM.h"


/* Init Global variables */
uint32_t TIM2_OverFlowCounter = 0;
uint32_t TIM2_NumOfOverFlows;
uint32_t TIM3_OverFlowCounter = 0;
uint32_t TIM3_NumOfOverFlows;

/**
 * @brief Initialize the timer
 * 
 * @param TIM_Handle 
 * @return HAL_Status 
 */
HAL_Status TIM_Init(TIM_HandleTypeDef *TIM_Handle)
{
    HAL_Status status = HAL_OKAY;

    if(NULL == TIM_Handle)
    {
        status = HAL_ERROR;
    }
    else
    {
        /* Set the URS bit */
        SET_BIT(TIM_Handle->Instance->CR1, TIM_CR1_URS_POS);

        /* Set the ARPE bit */
        SET_BIT(TIM_Handle->Instance->CR1, TIM_CR1_ARPE_POS);


        /* Set Counter with Preload value */
        TIM_Handle->Instance->CNT = TIM_ARR_VALUE;

        /* Set Auto-Reload value */
        TIM_Handle->Instance->ARR = TIM_ARR_VALUE;

        /* Set Periodicity */
        switch((uint32_t)TIM_Handle->Instance)
        {
            case TIM_2_BASE:
            TIM2_NumOfOverFlows =   TIM_Handle->NumberOfMilliseconds / TIM_OVERFLOW_TIME_IN_MS;
            break;
            case TIM_3_BASE:
            TIM3_NumOfOverFlows =   TIM_Handle->NumberOfMilliseconds / TIM_OVERFLOW_TIME_IN_MS;
            break;
        }

        /* Set Prescaler value */
        TIM_Handle->Instance->PSC = TIM_Handle->Prescaler;

        /* Check Interrupt */
        if(TIM_INTERRUPT_ENABLE == TIM_Handle->Interrupt)
        {
            /* Enable the interrupt */
            SET_BIT(TIM_Handle->Instance->DIER, TIM_DIER_UIE_POS);
        }
        else
        {
            /* Disable the interrupt */
            CLR_BIT(TIM_Handle->Instance->DIER, TIM_DIER_UIE_POS);
        }

    }
    return status;

}

/**
 * @brief Start the timer
 * 
 * @param TIM_Handle 
 * @return HAL_Status 
 */
HAL_Status TIM_Start(TIM_HandleTypeDef *TIM_Handle)
{
    HAL_Status status = HAL_OKAY;
    if(NULL == TIM_Handle)
    {
        status = HAL_ERROR;
    }
    else
    {
        /* Enable the timer */
        SET_BIT(TIM_Handle->Instance->CR1, TIM_CR1_CEN_POS);
    }
}

/**
 * @brief Stop the timer
 * 
 * @param TIM_Handle 
 * @return HAL_Status 
 */
HAL_Status TIM_Stop(TIM_HandleTypeDef *TIM_Handle)
{
    HAL_Status status = HAL_OKAY;
    if(NULL == TIM_Handle)
    {
        status = HAL_ERROR;
    }
    else
    {
        /* Disable the timer */
        CLR_BIT(TIM_Handle->Instance->CR1, TIM_CR1_CEN_POS);
    }
}


/**
 * @brief Set the Auto-Reload value
 * 
 * @param TIM_Handle 
 * @param AutoReload 
 * @return HAL_Status 
 */
HAL_Status TIM_SetAutoReload(TIM_HandleTypeDef *TIM_Handle, uint32_t AutoReload)
{
    HAL_Status status = HAL_OKAY;
    if(NULL == TIM_Handle)
    {
        status = HAL_ERROR;
    }
    else
    {
        /* Set Auto-Reload value */
        WRITE_REG(TIM_Handle->Instance->ARR, AutoReload);
    }
    return status;
}

/**
 * @brief Set the Prescaler value
 * 
 * @param TIM_Handle 
 * @param Prescaler 
 * @return HAL_Status 
 */ 
HAL_Status TIM_SetPrescaler(TIM_HandleTypeDef *TIM_Handle, uint32_t Prescaler)
{
    HAL_Status status = HAL_OKAY;
    if(NULL == TIM_Handle)
    {
        status = HAL_ERROR;
    }
    else
    {
        /* Set Prescaler value */
        WRITE_REG(TIM_Handle->Instance->PSC, Prescaler);
    }
    return status;
}


/**
 * @brief Set the interrupt
 * 
 * @param TIM_Handle 
 * @return HAL_Status 
 */
HAL_Status TIM_SetInterrupt(TIM_HandleTypeDef *TIM_Handle)
{
    HAL_Status status = HAL_OKAY;
    if(NULL == TIM_Handle)
    {
        status = HAL_ERROR;
    }
    else
    {
        /* Enable the interrupt */
        SET_BIT(TIM_Handle->Instance->DIER, TIM_DIER_UIE_POS);
    }
    return status;
}


/**
 * @brief Clear the interrupt
 * 
 * @param TIM_Handle 
 * @return HAL_Status 
 */
HAL_Status TIM_ClearInterrupt(TIM_HandleTypeDef *TIM_Handle)
{
    HAL_Status status = HAL_OKAY;
    if(NULL == TIM_Handle)
    {
        status = HAL_ERROR;
    }
    else
    {
        /* Clear the interrupt */
        CLR_BIT(TIM_Handle->Instance->SR, TIM_DIER_UIE_POS);
    }
    return status;
}


/**
 * @brief Set the periodicity
 * 
 * @param TIM_Handle 
 * @param TIM_NumOfMilliSeconds 
 * @return HAL_Status 
 */
HAL_Status TIM_SetPeriodicity(TIM_HandleTypeDef *TIM_Handle,uint32_t TIM_NumOfMilliSeconds)
{
   HAL_Status status = HAL_OKAY;

    if(NULL == TIM_Handle)
    {
        status = HAL_ERROR;
    }
    else
    {
        /* Set Periodicity */
        switch((uint32_t)TIM_Handle->Instance)
        {
            case TIM_2_BASE:
            TIM2_NumOfOverFlows =   TIM_NumOfMilliSeconds / TIM_OVERFLOW_TIME_IN_MS;
            break;
            case TIM_3_BASE:
            TIM3_NumOfOverFlows =   TIM_NumOfMilliSeconds / TIM_OVERFLOW_TIME_IN_MS;
            break;
        }

    }
    return status;
}

/**
 * @brief Set the callback function
 * 
 * @param TIM_Handle 
 * @param callback_fn 
 * @return HAL_Status 
 */
HAL_Status TIM_SetCallBackFn(TIM_HandleTypeDef *TIM_Handle,void (*callback_fn)(void))
{
     HAL_Status status = HAL_OKAY;

    if(NULL == TIM_Handle)
    {
        status = HAL_ERROR;
    }
    else
    {
        TIM2_CallbackFn = callback_fn;
    }
    return status;
}

/**
 * @brief Timer 2 interrupt handler
 * 
 */
void TIM2_IRQHandler()
{
    #if TIM_APP_MODE == TIM_STOPWATCH_APP_MODE
    TIM2_OverFlowCounter++;
    #elif TIM_APP_MODE == TIM_TIMER_APP_MODE
    /* Check overflow counter */
    if(TIM2_OverFlowCounter < TIM2_NumOfOverFlows)
    {
        TIM2_OverFlowCounter++;
    }
    else
    {
        /* Call the callback function */
        TIM2_CallbackFn();
        TIM2_OverFlowCounter = 0;
    }

    #endif
}
