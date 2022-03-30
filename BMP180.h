/*
 * BMP180.h
 *
 *  Created on: Mar 18, 2022
 *      Author: Anis Shakkour
 *      Email: anis.shakkour399@gmail.com
 */


/**
 * I2C MSB->LSB
 * I2C Speed <3.4M  selected 400Khz
 * bit0 ->1 read, bit0 ->0 write
 * UP Preasure data 16-19bit
 * UT temperature data 16bit
 */
#include "DAVE.h"


#define _BV(a) (1 << (a))      	//Bit Value
#define _DS(a, b) (a << (b))	//Data shift left  (a) b time
#define _DSn(a, b) (a >> (b))	//Data shift right (a) b time
#define _AndLow4(a) (a & (15))
#define Max(a, b) (a>b?a:b)
#define Min(a, b) (a<b?a:b)

uint8_t BMP180_DataSent[32];
uint8_t BMP180_DataRead[32];

uint8_t BMP180_Test(void);



/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/
#define SLAVE_ADDRESS 			   (0xA0)
#define BMP180_R					0x01
#define BMP180_W					0x00
#define BMP180_FixedID				0x55
#define BMP180_Address				0xD0
#define BMP180_Measurment_Control	0xF4

