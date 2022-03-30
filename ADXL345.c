/*
 * ADXL345.c
 *
 *  Created on: Mar 1, 2022
 *      Author: Anis Shakkour
 */

#include "ADXL345.h"


void Init_ADXL345(void){
	Set_DataFormat(_BV(FULL_RES) | _BV(Range0));
	Set_FIFO_CTR(_BV(Samples_D2));
	PowerOn();
}
void Set_DataFormat(uint8_t val){
	//SPI 4Wire (0)- INT_INVERT (0)- Full resolution (1)- Justify left (0)- Range 4g (01)
	WriteRegister_SingleByte(DATA_FORMAT, val);
}
void Set_FIFO_CTR(uint8_t val){
	//FIFO_Modes bypass (00)- Trigger (0)- Samples 2 (00010
	WriteRegister_SingleByte(FIFO_CTL,val);
}
void PowerOn(){
	//Link (0)-  Auto_Sleep (0)- Measure (1)- Sleep (0)- WakeUp (00)
	WriteRegister_SingleByte(POWER_CTL,_BV(Measure));
}
void PowerOff(){
	//Link (0)-  Auto_Sleep (0)- Measure (0)- Sleep (0)- WakeUp (00)
	WriteRegister_SingleByte(POWER_CTL,0);
}
uint8_t GetdeviceID(void){
	return ReadRegister_SingleByte(DEVID);
}
void Get_AxisReadings(){
	ADXL345_DataSent [0] = _BV(WR) | _BV(MB) | DATAX0;
	ADXL345_DataSent [1] = ADXL345_NOP;
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_1, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_1, ADXL345_DataSent, ADXL345_DataRead,7);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_1);
}
uint8_t ReadRegister_SingleByte(uint8_t reg){
	ADXL345_DataSent [0] = _BV(WR) | reg;
	ADXL345_DataSent [1] = ADXL345_NOP;
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_1, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_1, ADXL345_DataSent, ADXL345_DataRead, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_1);
	return ADXL345_DataRead[1];
}
uint8_t WriteRegister_SingleByte(uint8_t reg, uint8_t data){
	ADXL345_DataSent [0] = reg;
	ADXL345_DataSent [1] = data;
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_1, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_1, ADXL345_DataSent, ADXL345_DataRead, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_1);
	return ADXL345_DataRead[1];
}

void Set_DUR(uint8_t val){
	WriteRegister_SingleByte(DUR, val); //time = val * 625 µs/LSB
}
void Set_Latent(uint8_t val){
	WriteRegister_SingleByte(Latent, val); //time = val *  1.25 ms/LSB
}
void Set_Window(uint8_t val){
	WriteRegister_SingleByte(Window, val); //time = val *  1.25 ms/LSB
}
void Set_ThreshACT(uint8_t val){
	WriteRegister_SingleByte(THRESH_ACT, val); //time = val *  62.5 mg/LSB
}
void Set_ThreshINACT(uint8_t val){
	WriteRegister_SingleByte(THRESH_INACT, val); //time = val *  62.5 mg/LSB
}
void Set_OutputDataRate(uint8_t val){
	WriteRegister_SingleByte(BW_RATE,Min(val,15));
}
void Set_ThreshTap(uint8_t val){
	WriteRegister_SingleByte(THRESH_TAP,val);
}
