/*
 * nRF24L01+.c
 *
 *  Created on: Feb 19, 2022
 *      Author: Anis Shakkour
 */

#include "nRF24L01+.h"

void Init_RF24(void){
	for(int i = 0 ; i < 0xFFFF;i++); //delay
	//uint8_t temp = getChannel();
	setChannel(76);
	//temp = getChannel();
	setRetries(5,15);
	setRadiation(3,0); //see Header file
	setAddressWidth(5); //Address width 5 bytes
	setFeatures(0); //
	//enableDynamicPayLoads();
	enableAutoACK();
	enableRXpipe(0);
	setPayloadSize(0x3f,0);
	setRxPipeAddress(0,"00000",5);
	setTxPipeAddress("00000",5);
	resetStatus();
	flushTX();
	flushRX();
	PowerUP();
}
void TestCom(void){
	Send_Word("If you see this message then OKI");
}
void Send_OneByte(uint8_t data){
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_TransmitWord(&SPI_MASTER_0, W_TX_PAYLOAD);
	SPI_MASTER_TransmitWord(&SPI_MASTER_0, data);
	for(int  i = 1 ; i < 32;i++)
		SPI_MASTER_TransmitWord(&SPI_MASTER_0, 0);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	DIGITAL_IO_SetOutputHigh(&SPI_CE);
	for(int i = 0 ; i < 0x1FF;i++); //delay 10us
	DIGITAL_IO_SetOutputLow(&SPI_CE);
	for(int i = 0 ; i < 0x3FFF;i++); //delay 10us
	for(int i = 0 ; i < 0x3FFF;i++); //delay
	resetStatus();
	flushTX();
}
void Send_Word(char* data){
	uint8_t len = Max(sizeof(data),32);
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_TransmitWord(&SPI_MASTER_0, W_TX_PAYLOAD);
	for(int  i = 0 ; i < len;i++)
		SPI_MASTER_TransmitWord(&SPI_MASTER_0, data[i]);
	for(int  i = len ; i < 32;i++)
		SPI_MASTER_TransmitWord(&SPI_MASTER_0, 0);

	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	DIGITAL_IO_SetOutputHigh(&SPI_CE);

	//while(!Is_TX_DS()) //;| !Is_MAX_RT());

	for(int i = 0 ; i < 0x1FF;i++); //delay 10us
	DIGITAL_IO_SetOutputLow(&SPI_CE);
	for(int i = 0 ; i < 0x3FFF;i++); //delay 10us
	for(int i = 0 ; i < 0x3FFF;i++); //delay
	resetStatus();
	flushTX();
	//for(int i = 0 ; i < 0x3FFF;i++); //delay
	//for(int i = 0 ; i < 0x3FFF;i++); //delay
}

void setChannel(uint8_t ch){
	NRF24SendData [0] = (W_REGISTER | RFCH);
	NRF24SendData [1] = (ch);
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
}
uint8_t getChannel(void){
	NRF24SendData [0] = (R_REGISTER | RFCH);
	NRF24SendData [1] = (RF24_NOP);
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
	return NRF24ReadData[1];
}

void setRetries(uint8_t AutoTransmitDelay, uint8_t AutoTransmitCount){
	NRF24SendData [0] = (W_REGISTER | SETUP_RETR);
	NRF24SendData [1] = (_DS(Min(AutoTransmitDelay,15),4) | Min(AutoTransmitCount,15));
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
}
uint8_t getRetriesDelay(void){
	NRF24SendData [0] = (R_REGISTER | SETUP_RETR);
	NRF24SendData [1] = (RF24_NOP);
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
	return _DSn(NRF24ReadData[1],4);
}
uint8_t getRetriesCount(void){
	NRF24SendData [0] = (R_REGISTER | SETUP_RETR);
	NRF24SendData [1] = (RF24_NOP);
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
	return _AndLow4(NRF24ReadData[1]);
}

void setRadiation (uint8_t RFpwerMode, uint8_t RFspeedMode){
	NRF24SendData [0] = (W_REGISTER | RF_SETUP);
	NRF24SendData [1] = _DS(RFpwerMode, 1) | _DS(RFspeedMode & 2,4) | _DS(RFspeedMode & 1,3);
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
}
uint8_t getRadiation(void){
	NRF24SendData [0] = (R_REGISTER | RF_SETUP);
	NRF24SendData [1] = (RF24_NOP);
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
	return NRF24ReadData[1];
}

void setAddressWidth(uint8_t width){
	NRF24SendData [0] = (W_REGISTER | SETUP_AW);
	NRF24SendData [1] = Max(Min(3,width),5) - 2;
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
}
uint8_t getAddressWidth(void){
	NRF24SendData [0] = (R_REGISTER | SETUP_AW);
	NRF24SendData [1] = (RF24_NOP);
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
	return (NRF24ReadData[1] & 3) + 2; // 2 is added cu
}

void setFeatures(uint8_t val){
	NRF24SendData [0] = (W_REGISTER | FEATURE);
	NRF24SendData [1] = Max(Min(0,val),3);
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
}
uint8_t getFeatures(){
	NRF24SendData [0] = (R_REGISTER | FEATURE);
	NRF24SendData [1] = RF24_NOP;
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
	return NRF24ReadData[1];
}

void disableDynamicPayLoads(){
	NRF24SendData [0] = (W_REGISTER | FEATURE);
	NRF24SendData [1] = getFeatures() & 0b11111101;
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
}
void enableDynamicPayLoads(){
	NRF24SendData [0] = (W_REGISTER | FEATURE);
	NRF24SendData [1] = getFeatures() | 0b00000010;
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
}


void enableAutoACK(){ // all pipes
	NRF24SendData [0] = (W_REGISTER | ENAA);
	NRF24SendData [1] = 0x3F;
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
}


void enableRXpipe(uint8_t pipeNum){
	NRF24SendData [0] = (W_REGISTER | EN_RXADDR);
	NRF24SendData [1] = getRXpipesEnabled() | _DS(1,pipeNum);
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
}
uint8_t getRXpipesEnabled(void){
	NRF24SendData [0] = (R_REGISTER | EN_RXADDR);
	NRF24SendData [1] = RF24_NOP;
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
	return NRF24ReadData[1];
}

void setPayloadSizeAllPipes(uint8_t size){
	for(int i = 0; i < 6 ; i++){
		NRF24SendData [0] = (W_REGISTER | (RX_PW_P0 + i));
		NRF24SendData [1] = size;
		SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
		SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
		SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
		Status_reg = NRF24ReadData[0];
	}
}
void setPayloadSize(uint8_t size,uint8_t pipeNum){
	NRF24SendData [0] = (W_REGISTER | (RX_PW_P0 + Min(pipeNum,5)));
	NRF24SendData [1] = size;
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
}

void setRxPipeAddress(uint8_t pipe ,char* address, uint8_t size){
	NRF24SendData [0] = (W_REGISTER | (RX_ADDR_P0 + Min(pipe,5)));
	for(uint8_t i = 0; i < size; i++)
		NRF24SendData [1+i] = address[i];
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, size + 1);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
}
void setTxPipeAddress(char* address, uint8_t size){
	NRF24SendData [0] = (W_REGISTER | TXADDR);
	for(uint8_t i = 0; i < size; i++)
		NRF24SendData [1+i] = address[i];
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, size + 1);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
}

void resetStatus(){
	NRF24SendData [0] = (W_REGISTER | NRF_STATUS);
	NRF24SendData [1] = 0b01111110;
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
}
bool Is_TX_FIFO_full(void){
	NRF24SendData [0] = (R_REGISTER | NRF_STATUS);
	NRF24SendData [1] = RF24_NOP;
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
	return NRF24ReadData[1] & 1;
}
uint8_t RX_Data_PipeNum_Payload_Available(void){
	NRF24SendData [0] = (R_REGISTER | NRF_STATUS);
	NRF24SendData [1] = RF24_NOP;
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
	return _DSn(NRF24ReadData[1],1) & 7;
}
bool Is_RX_DR(void){
	NRF24SendData [0] = (R_REGISTER | NRF_STATUS);
	NRF24SendData [1] = RF24_NOP;
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
	return _DSn(NRF24ReadData[1],6) & 1;
}
bool Is_TX_DS(void){
	NRF24SendData [0] = (R_REGISTER | NRF_STATUS);
	NRF24SendData [1] = RF24_NOP;
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
	return _DSn(NRF24ReadData[1],5) & 1;
}
bool Is_MAX_RT(void){
	NRF24SendData [0] = (R_REGISTER | NRF_STATUS);
	NRF24SendData [1] = RF24_NOP;
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
	return _DSn(NRF24ReadData[1],4) & 1;
}

void flushTX(){
	NRF24SendData [0] = (R_REGISTER | FLUSH_TX);
	NRF24SendData [1] = RF24_NOP;
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
}
void flushRX(){
	NRF24SendData [0] = (R_REGISTER | FLUSH_RX);
	NRF24SendData [1] = RF24_NOP;
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
}

void PowerUP(void){
	NRF24SendData [0] = (W_REGISTER | NRF_CONFIG);
	NRF24SendData [1] = _BV(MASK_RX_DR) | _BV(MASK_TX_DS) | _BV(MASK_MAX_RT) | _BV(EN_CRC) | _BV(CRCO) | _BV(PWR_UP) | ~_BV(PRIM_RX) ;
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
	for(int i = 0 ; i < 0x3FFF;i++); //delay
}
void TX_Mode(void){
	NRF24SendData [0] = (W_REGISTER | NRF_CONFIG);
	NRF24SendData [1] = getConfigRegister() | _BV(PRIM_RX) ;
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
}
uint8_t getConfigRegister(void){
	NRF24SendData [0] = (R_REGISTER | NRF_CONFIG);
	NRF24SendData [1] = RF24_NOP;
	SPI_MASTER_EnableSlaveSelectSignal(&SPI_MASTER_0, SPI_MASTER_SS_SIGNAL_0);
	SPI_MASTER_Transfer(&SPI_MASTER_0, NRF24SendData, NRF24ReadData, 2);
	SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
	Status_reg = NRF24ReadData[0];
	Config_Regiter = NRF24ReadData[1];
	return Config_Regiter;
}
