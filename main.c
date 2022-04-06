/*
 * main.c
 *
 *  Created on: 2022 Feb 17 11:44:16
 *  Author: Anis Shakkour
 */

#include "DAVE.h"                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "nRF24L01+.h"
#include "ADXL345.h"
#include "BMP180.h"

extern void initialise_monitor_handles(void);

extern uint8_t ADXL345_DataRead[32];
char data[] = "X, .Y, .Z, ";
uint8_t slaveID = 236;

int main(void)
{
  DAVE_STATUS_t status;
  status = DAVE_Init();
  initialise_monitor_handles(); // enable XMC_DEBUG outputs


  if (status != DAVE_STATUS_SUCCESS)
  	  { XMC_DEBUG("DAVE APPs initialization failed\n");  while(1U); }

  XMC_DEBUG("DAVE APPs initialization passed\n");
  DIGITAL_IO_SetOutputLow(&SPI_CE);
  SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
  SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_1);

  //XMC_DEBUG("Data shifted %d",ROTATE_LEFT(0x76,1));
  //XMC_DEBUG("Data moved %d",0x76<<1);
  //Init_RF24();
  //TX_Mode();
  //Init_ADXL345();
  XMC_DEBUG("Test Communication returned %d \n",Text_Communication(BME180_Address));
  XMC_DEBUG("Init returned %d \n",BMP180_init());

  while(1U)
  {
	  //XMC_DEBUG("BMP_Test\n");
	  //XMC_DEBUG("Status flag %lu",(unsigned long)XMC_I2C_CH_GetStatusFlag(I2C_MASTER_0.channel));
	  //BMP180_Test();
	  //for(; slaveID< 0xFF; slaveID++){
		  //I2C_MASTER_FlushRxFifo(&I2C_MASTER_0);
		  //I2C_MASTER_FlushTxFifo(&I2C_MASTER_0);
		  //BMP180_DataRead[0] = 0xD0;
		  //I2C_MASTER_Transmit(&I2C_MASTER_0,true,slaveID,BMP180_DataRead,1,false);
		  //for(int i = 0 ; i < 0xFFFF;i++); //delay
		  //while(I2C_MASTER_IsTxBusy(&I2C_MASTER_0));
		  //I2C_MASTER_Receive(&I2C_MASTER_0,true,slaveID,BMP180_DataRead,1,true,true);
		  //while(I2C_MASTER_IsTxBusy(&I2C_MASTER_0));
		  //for(int i = 0 ; i < 0xFF;i++); //delay
	  //}
	  //Send_Word("Hello Anis 2");
	  //for(int i = 0 ; i < 0xFFFF;i++); //delay
	  //for(int i = 0 ; i < 0xFFFF;i++); //delay
	  ////for(int i = 0 ; i < 0xFFFF;i++); //delay
	  //SetSPIworkingMode();
	  //for(int i = 0 ; i < 0xFFFF;i++); //delay
	  //data = GetdeviceID();
	  //if(data == ADXL345_FixedID)
	 	  //Send_Word("ADXL Connected");
	  //else
		  //Send_Word("ADXL Not Connected");

	  //Get_AxisReadings();
	  //data[2]  = ADXL345_DataRead[1];
	  //data[6]  = ADXL345_DataRead[3];
	  //data[10] = ADXL345_DataRead[5];
	  //Send_Word(data);
	  //ReadRegister_SingleByte(DATAX0);
	  //Send_OneByte(ADXL345_DataRead[1]);
	  //for(int i = 0 ; i < 0xFF;i++); //delay
	  //data = ReadRegister(POWER_CTL);
	  //for(int i = 0 ; i < 0xFFFF;i++); //delay

  }
}

void Nack_ISR(){
	XMC_DEBUG("NO ACK, Check Communication or slave address. (Aborting)\n");
	BMP180_I2C_Status = 2;
	I2C_MASTER_ClearFlag(&I2C_MASTER_0, (uint32_t)XMC_I2C_CH_STATUS_FLAG_NACK_RECEIVED);
	I2C_MASTER_AbortTransmit(&I2C_MASTER_0);
}

void ARB_LOST_ISR(){
	XMC_DEBUG("\bARB lost\n");
}
void Error_detect_ISR(){
	XMC_DEBUG("I2C error detect\n");
	I2C_MASTER_ClearFlag(&I2C_MASTER_0, (uint32_t)XMC_I2C_CH_STATUS_FLAG_ERROR);
	I2C_MASTER_AbortTransmit(&I2C_MASTER_0);
	I2C_MASTER_AbortReceive(&I2C_MASTER_0);
}
void I2C_Transmit_ISR(){
	//XMC_DEBUG("I2C device found, Slave ID %d\n",ROTATE_RIGHT(BMP180_DataRead[31],1));
	//I2C_MASTER_ClearFlag(&I2C_MASTER_0, (uint32_t)XMC_I2C_CH_STATUS_FLAG_r);

}
void I2C_Recive_ISR(){
	//XMC_DEBUG("\nI2C Rx ISR, Data recived %d",BMP180_DataRead[0]);
}
void SPI_Test(){
	XMC_DEBUG("SPI test error\n");
}
void enableSpecialFeatures(){
	SPI_MASTER_TransmitWord(&SPI_MASTER_0, ACTIVATE); //activate special features
	SPI_MASTER_TransmitWord(&SPI_MASTER_0,0x73);

}
