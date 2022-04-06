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
//GIT TEST

void I2C_Scanner(){
	XMC_DEBUG("\n\nStarting I2C Scanner.... \n");

	for(uint8_t SlaveAddress = 0 ; SlaveAddress<255;SlaveAddress++){
	I2C_MASTER_FlushRxFifo(&I2C_MASTER_0);
	I2C_MASTER_FlushTxFifo(&I2C_MASTER_0);
	I2C_MASTER_Transmit(&I2C_MASTER_0,true,SlaveAddress,BMP180_DataRead,1,true);
	for(int i = 0 ; i < 0xFFF;i++); //delay
	}

	XMC_DEBUG("Done \n");
}
uint8_t BMP180_init(){
	BMP180_DataRead[0] = BMP180_Reset;
	BMP180_DataRead[1] = 0xB6;  //reset registers and goes to sleep mode
	BMP180_DataRead[2] = BMP180_CTRL_hum;
	BMP180_DataRead[3] = 1; // oversampling -> 1
	BMP180_DataRead[4] = BMP180_CTRL_meas;
	BMP180_DataRead[5] = 0b00100101; //temp oversampling->1,pressure oversampling->1, forced mode
	BMP180_DataRead[6] = BMP180_CONFIG;
	BMP180_DataRead[7] = 0b00000000; //time standby is not important as the IIR filter is off, SPI 3 wire disabled
	BMP180_I2C_Status = 0;
	I2C_MASTER_Transmit(&I2C_MASTER_0,true,_DS(BME180_Address,1),BMP180_DataRead,8,true);
	while(I2C_MASTER_IsTxBusy(&I2C_MASTER_0));
	if(BMP180_I2C_Status == 2) return 0;


	return 1;
}
uint8_t Text_Communication(uint8_t SlaveAddress){
	XMC_DEBUG("\n\nCommunication Test .... \n");
	I2C_MASTER_FlushRxFifo(&I2C_MASTER_0);
	I2C_MASTER_FlushTxFifo(&I2C_MASTER_0);
	SlaveAddress = _DS(SlaveAddress,1);
	BMP180_DataRead[0] = BMP180_ID_Reg;
	I2C_MASTER_Transmit(&I2C_MASTER_0,true,SlaveAddress,BMP180_DataRead,1,false);
	while(I2C_MASTER_IsTxBusy(&I2C_MASTER_0)); //
	if(BMP180_I2C_Status == 2) return 0;
	I2C_MASTER_Receive(&I2C_MASTER_0,true,SlaveAddress,BMP180_DataRead,1,true,true);
	while(I2C_MASTER_IsTxBusy(&I2C_MASTER_0));
	if(BMP180_DataRead[0] == BMP180_FixedAlternativID){
		XMC_DEBUG("BME280 connected\n");
		return 1;
	}
	return 0;
}
uint8_t BMP180_Test(void){

	I2C_MASTER_FlushRxFifo(&I2C_MASTER_0);
	I2C_MASTER_FlushTxFifo(&I2C_MASTER_0);
	BMP180_DataRead[0] = 0b11110100;
	I2C_MASTER_Transmit(&I2C_MASTER_0,true,BMP180_W,BMP180_DataRead,1,false);
	//while(I2C_MASTER_IsRxBusy(&I2C_MASTER_0));


	//I2C_MASTER_ClearFlag(&I2C_MASTER_0,I2C_MASTER_STATUS_BUSY);
	//I2C_MASTER_FlushTxFifo(&I2C_MASTER_0);
	//I2C_MASTER_FlushRxFifo(&I2C_MASTER_0);
	//BMP180_DataSent[0] = 0xD0;

	///I2C_MASTER_Transmit(&I2C_MASTER_0,true,0xEE,BMP180_DataSent,1,true);
	//while(I2C_MASTER_IsTxBusy(&I2C_MASTER_0));
	//I2C_MASTER_Receive(&I2C_MASTER_0,true,BMP180_Address|BMP180_R,&BMP180_DataRead,1,true,true);
	//while(I2C_MASTER_IsRxBusy(&I2C_MASTER_0));
	return BMP180_DataRead[0];
}





#endif //!BMP180_H

