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

extern uint8_t ADXL345_DataRead[32];
char data[] = "X, .Y, .Z, ";

int main(void)
{
  DAVE_STATUS_t status;

  status = DAVE_Init();           /* Initialization of DAVE APPs */

  if (status != DAVE_STATUS_SUCCESS)
  	  { XMC_DEBUG("DAVE APPs initialization failed\n");  while(1U); }

  DIGITAL_IO_SetOutputLow(&SPI_CE);
  SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_0);
  SPI_MASTER_DisableSlaveSelectSignal(&SPI_MASTER_1);

  Init_RF24();
  TX_Mode();

  Init_ADXL345();

  while(1U)
  {
	  BMP180_Test();
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
	  for(int i = 0 ; i < 0xFFFF;i++); //delay
	  //data = ReadRegister(POWER_CTL);
	  //for(int i = 0 ; i < 0xFFFF;i++); //delay

  }
}

void Nack_ISR(){


}

void SPI_Test(){
	XMC_DEBUG("DAVE APPs initialization failed\n");
}

void enableSpecialFeatures(){
	SPI_MASTER_TransmitWord(&SPI_MASTER_0, ACTIVATE); //activate special features
	SPI_MASTER_TransmitWord(&SPI_MASTER_0,0x73);

}
