/*
 * BMP180.c
 *
 *  Created on: Mar 18, 2022
 *      Author: Anis Shakkour
 *      Email: anis.shakkour399@gmail.com
 */


#ifndef BMP180_H
#define BMP180_H

#include "BMP180.h"

uint8_t BMP180_Test(void){
	//I2C_MASTER_ClearFlag(&I2C_MASTER_0,I2C_MASTER_STATUS_BUSY);
	//I2C_MASTER_FlushTxFifo(&I2C_MASTER_0);
	//I2C_MASTER_FlushRxFifo(&I2C_MASTER_0);
	BMP180_DataSent[0] = 0xD0;

	I2C_MASTER_Transmit(&I2C_MASTER_0,true,0xEE,BMP180_DataSent,1,true);
	//while(I2C_MASTER_IsTxBusy(&I2C_MASTER_0));
	//I2C_MASTER_Receive(&I2C_MASTER_0,true,BMP180_Address|BMP180_R,&BMP180_DataRead,1,true,true);
	//while(I2C_MASTER_IsRxBusy(&I2C_MASTER_0));
	return BMP180_DataRead[0];
}





#endif //!BMP180_H

