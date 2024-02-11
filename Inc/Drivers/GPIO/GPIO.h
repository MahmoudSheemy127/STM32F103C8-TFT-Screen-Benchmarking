/*
 * GPIO.h
 *
 *  Created on: Nov 19, 2023
 *      Author: mahmo
 */

#ifndef GPIO_H_
#define GPIO_H_

//define registers
/*---------------START INCLUDES---------------------*/
#include "Drivers/Common/Common.h"
#include "Std_Types.h"
/*---------------END INCLUDES-----------------------*/

/*---------------START MACROS-----------------------*/
#define GPIO_BASE		(APB2_BASE+0x0800UL)
#define GPIOA_BASE		(GPIO_BASE+0x0000UL)
#define GPIOB_BASE		(GPIO_BASE+0x0400UL)
#define GPIOC_BASE		(GPIO_BASE+0x0800UL)
#define GPIOD_BASE		(GPIO_BASE+0x0C00UL)
#define GPIOE_BASE		(GPIO_BASE+0x1000UL)
#define GPIOF_BASE		(GPIO_BASE+0x1400UL)
#define GPIOG_BASE		(GPIO_BASE+0x1800UL)
#define GPIOA			((GPIO_Typedef*)(GPIOA_BASE))
#define GPIOB 			((GPIO_Typedef*)(GPIOB_BASE))


/*---------------END MACROS-------------------------*/

/*---------------START FUNCTION-LIKE MACROS---------*/
/*---------------END FUNCTION-LIKE MACROS----------*/

/*---------------START DATATYPES-------------------*/
typedef enum{
	GPIO_PIN_0 = 0x00UL,
	GPIO_PIN_1 = 0x01UL,
	GPIO_PIN_2 = 0x02UL,
	GPIO_PIN_3 = 0x03UL,
	GPIO_PIN_4 = 0x04UL,
	GPIO_PIN_5 = 0x05UL,
	GPIO_PIN_6 = 0x06UL,
	GPIO_PIN_7 = 0x07UL,
	GPIO_PIN_8 = 0x08UL,
	GPIO_PIN_9 = 0x09UL,
	GPIO_PIN_10 = 0x0AUL,
	GPIO_PIN_11 = 0x0BUL,
	GPIO_PIN_12 = 0x0CUL,
	GPIO_PIN_13 = 0x0DUL,
	GPIO_PIN_14 = 0x0EUL,
	GPIO_PIN_15 = 0x0FUL
}GPIO_Pin;

typedef enum{
	GPIO_MODE_INPUT = 0x00UL,
	GPIO_MODE_OUTPUT_10MHZ = 0x01UL,
	GPIO_MODE_OUTPUT_2MHZ = 0x02UL,
	GPIO_MODE_OUTPUT_50MHZ = 0x03UL
}GPIO_Mode;

typedef enum{
	GPIO_CNF_INPUT_ANALOG = 0x00UL,
	GPIO_CNF_INPUT_FLOATING = 0x01UL,
	GPIO_CNF_INPUT_PULL = 0x02UL,
	GPIO_CNF_OUTPUT_PUSH_PULL = 0x03UL,
	GPIO_CNF_OUTPUT_OPEN_DRAIN = 0x04UL,
	GPIO_CNF_OUTPUT_ALTFN_PUSH_PULL = 0x05UL,
	GPIO_CNF_OUTPUT_ALTFN_OPEN_DRAIN = 0x06UL
}GPIO_CNF;


typedef enum{
	GPIO_PIN_RESET = 0x00UL,
	GPIO_PIN_SET = 0x01UL
}GPIO_PinState;



typedef struct{
	uint32_t CRL;
	uint32_t CRH;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t BRR;
	uint32_t LCKR;
}GPIO_Typedef;

typedef struct{
	GPIO_Typedef* GPIO_TypeDef;
	GPIO_Pin GPIO_Pin;
	GPIO_Mode GPIO_Mode;
	GPIO_CNF GPIO_CNF;
	GPIO_PinState GPIO_PinState;
}GPIO_HandleTypeDef;
/*---------------END DATATYPES---------------------*/

/*---------------START FUNCTIONS-------------------*/
HAL_Status GPIO_Init(GPIO_HandleTypeDef* gpio_handle);
HAL_Status GPIO_WritePin(GPIO_HandleTypeDef* gpio_handle, GPIO_PinState pin_state);
uint8_t GPIO_ReadPin(GPIO_HandleTypeDef* gpio_handle);
HAL_Status GPIO_TogglePin(GPIO_HandleTypeDef* gpio_handle);
/*---------------END FUNCTIONS---------------------*/







#endif /* GPIO_H_ */
