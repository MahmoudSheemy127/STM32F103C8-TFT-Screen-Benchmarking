/*
 * Common.h
 *
 *  Created on: Dec 3, 2023
 *      Author: mahmo
 */

#ifndef DRIVERS_COMMON_COMMON_H_
#define DRIVERS_COMMON_COMMON_H_


#define PERIPH_BASE			0x40000000UL
#define APB1_BASE			(PERIPH_BASE+0x00000000UL)
#define APB2_BASE			(PERIPH_BASE+0x00010000UL)
#define AHB_BASE			(PERIPH_BASE+0x00018000UL)


typedef enum HAL_Status{
	HAL_OKAY = 0x00UL,
	HAL_ERROR = 0x01UL
}HAL_Status;



#endif /* DRIVERS_COMMON_COMMON_H_ */
