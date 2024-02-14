/*-----------START INCLUDES-----------------*/
#include "Drivers/Common/Common.h"
#include  "Std_Types.h"

/*-----------END INCLUDES-----------------*/


/*-----------START MACROS-----------------------------*/
#define TIM_2_BASE          ((TIM_TypeDef*)(APB1_BASE+0x0000))
#define TIM_3_BASE          ((TIM_TypeDef*)(APB1_BASE+0x0400))
#define TIM_4_BASE          ((TIM_TypeDef*)(APB1_BASE+0x0800))
#define TIM_5_BASE          ((TIM_TypeDef*)(APB1_BASE+0x0C00))
#define TIM_6_BASE          ((TIM_TypeDef*)(APB1_BASE+0x1000))
#define TIM_7_BASE          ((TIM_TypeDef*)(APB1_BASE+0x1400))

/* Register Bit Position Macros */
#define TIM_CR1_CEN_POS     0
#define TIM_CR1_UDIS_POS    1
#define TIM_CR1_URS_POS     2
#define TIM_CR1_OPM_POS     3
#define TIM_CR1_ARPE_POS    7
#define TIM_DIER_UIE_POS    0
#define TIM_SR_UIF_POS      0

/* TIMING MACROS */
#define TIM_OVERFLOW_TIME_IN_MS         1
#define TIM_ARR_VALUE                   (uint16_t)0x03E8
#define TIM_PRESCALAR_VALUE_DIV_8       0x08

#define TIM_STOPWATCH_APP_MODE     0
#define TIM_TIMER_APP_MODE         1
#define TIM_APP_MODE               TIM_TIMER_APP_MODE
        

/*-----------END MACROS-------------------------------*/

/*-----------START MACRO-LIKE FUNCTIONS-----------------*/

/*-----------END MACRO-LIKE FUNCTIONS-----------------*/

/*-----------START DATATYPES-----------------*/
typedef enum{
    TIM_INTERRUPT_ENABLE = 0,
    TIM_INTERRUPT_DISABLE = 1
}TIM_INTERRUPT;



typedef struct{
    uint32_t  CR1;
    uint32_t  CR2;
    uint32_t SMCR;
    uint32_t DIER;
    uint32_t SR;
    uint32_t EGR;
    uint32_t RES2[3];
    uint32_t CNT;
    uint32_t PSC;
    uint32_t ARR;
}TIM_TypeDef;


typedef struct{
    TIM_TypeDef *Instance;
    uint32_t NumberOfMilliseconds;
    uint32_t Prescaler;
    TIM_INTERRUPT Interrupt;
}TIM_HandleTypeDef;


/* Init a callback function */
void (*TIM2_CallbackFn)(void);
void (*TIM3_CallbackFn)(void);




/*-----------END DATATYPES-----------------*/

/*-----------START FUNCTIONS-----------------*/
HAL_Status TIM_Init(TIM_HandleTypeDef *TIM_Handle);
HAL_Status TIM_SetPeriodicity(TIM_HandleTypeDef *TIM_Handle,uint32_t TIM_NumOfMilliSeconds);
HAL_Status TIM_SetCallBackFn(TIM_HandleTypeDef *TIM_Handle,void (*callback_fn)(void));
HAL_Status TIM_Start(TIM_HandleTypeDef *TIM_Handle);
HAL_Status TIM_Stop(TIM_HandleTypeDef *TIM_Handle);
HAL_Status TIM_SetAutoReload(TIM_HandleTypeDef *TIM_Handle, uint32_t AutoReload);
HAL_Status TIM_SetPrescaler(TIM_HandleTypeDef *TIM_Handle, uint32_t Prescaler);
HAL_Status TIM_SetInterrupt(TIM_HandleTypeDef *TIM_Handle);
HAL_Status TIM_ClearInterrupt(TIM_HandleTypeDef *TIM_Handle);

/*-----------END FUNCTIONS-----------------*/