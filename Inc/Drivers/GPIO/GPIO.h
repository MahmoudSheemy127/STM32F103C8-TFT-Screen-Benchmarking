/*
 * GPIO.h
 *
 *  Created on: Nov 19, 2023
 *      Author: mahmo
 */

#ifndef GPIO_H_
#define GPIO_H_

//define registers
#define GPIO_BASE		(0x40010800UL)
#define GPIOA			((GPIO_Typedef*)(GPIO_BASE))


typedef struct{
	uint32_t CRL;
	uint32_t CRH;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t BRR;
	uint32_t LCKR;
}GPIO_Typedef;



#endif /* GPIO_H_ */
