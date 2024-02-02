/*
 * Std_Types.h
 *
 *  Created on: Nov 19, 2023
 *      Author: mahmo
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/*------------ COMMON STD TYPES DEF -----------------*/
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned long int uint32_t;

/*------------COMMON MACRO DEFINITIONS -------------*/
#define NULL 0x00


/*----------- COMMON MACRO LIKE FUNCTIONS ----------- */
#define SET_BIT(REG,BIT_POS)	(REG |= 1 << BIT_POS)
#define CLR_BIT(REG,BIT_POS)	(REG &= ~(1 << BIT_POS))
#define TOGGLE_BIT(REG,BIT_POS)	(REG ^= 1 << BIT_POS)
#define GET_BIT(REG,BIT_POS)	((REG >> BIT_POS) & 0x01)
#define READ_REG(REG)			(REG)
#define WRITE_REG(REG,VAL)		(REG = VAL)
#define MODIFY_REG(REG,MSK,VAL) (WRITE_REG(REG, (READ_REG(REG) & ~(MSK)) | VAL))

#endif /* STD_TYPES_H_ */
