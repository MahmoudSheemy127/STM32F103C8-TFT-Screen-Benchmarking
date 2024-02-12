/*-----------START INCLUDES-----------------*/
#include "Drivers/Common/Common.h"
#include  "Std_Types.h"

/*-----------END INCLUDES-----------------*/


/*-----------START MACROS-----------------------------*/
#define TIM_2_BASE          (APB1_BASE+0x0000)
#define TIM_3_BASE          (APB1_BASE+0x0400)
#define TIM_4_BASE          (APB1_BASE+0x0800)
#define TIM_5_BASE          (APB1_BASE+0x0C00)
#define TIM_6_BASE          (APB1_BASE+0x1000)
#define TIM_7_BASE          (APB1_BASE+0x1400)
/*-----------END MACROS-------------------------------*/

/*-----------START MACRO-LIKE FUNCTIONS-----------------*/

/*-----------END MACRO-LIKE FUNCTIONS-----------------*/

/*-----------START DATATYPES-----------------*/
typedef struct{
    uint32_t  CR1;
    uint32_t  CR2;
    uint32_t RES1;
    uint32_t DIER;
    uint32_t SR;
    uint32_t EGR;
    uint32_t RES2[3];
    uint32_t CNT;
    uint32_t PSC;
    uint32_t ARR;
}TIM_TypeDef;



/*-----------END DATATYPES-----------------*/

/*-----------START FUNCTIONS-----------------*/
/*-----------END FUNCTIONS-----------------*/