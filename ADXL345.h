/*
 * ADXL345.h
 *
 *  Created on: Mar 1, 2022
 *      Author: Anis Shakkour
 */


#ifndef ADXL345_H
#define ADXL345_H
#include "DAVE.h"

///
#define _BV(a) (1 << (a))      	//Bit Value
#define _DS(a, b) (a << (b))	//Data shift left  (a) b time
#define _DSn(a, b) (a >> (b))	//Data shift right (a) b time
#define _AndLow4(a) (a & (15))
#define Max(a, b) (a>b?a:b)
#define Min(a, b) (a<b?a:b)


uint8_t ADXL345_DataSent[32];
uint8_t ADXL345_DataRead[32];


/**
*	Inits the user selected working modes
*
 **/
void Init_ADXL345(void);

void PowerOn();
void PowerOff();
void Set_OutputDataRate(uint8_t val);

//*************************************************************************************
	//The DATA_FORMAT register controls the presentation of data
	//to Register 0x32 through Register 0x37. All data, except that for
	//the ±16 g range, must be clipped to avoid rollover
void Set_DataFormat(uint8_t val);
//*************************************************************************************
//*************************************************************************************

void Set_FIFO_CTR(uint8_t val);
//*************************************************************************************
//*************************************************************************************
	//The DUR register is eight bits and contains an unsigned time
	//value representing the maximum time that an event must be
	//above the THRESH_TAP threshold to qualify as a tap event. The
	//scale factor is 625 µs/LSB. A value of 0 disables the single tap/
	//double tap functions.
void Set_DUR(uint8_t val);
//*************************************************************************************
//*************************************************************************************
	//The latent register is eight bits and contains an unsigned time
	//value representing the wait time from the detection of a tap
	//event to the start of the time window (defined by the window
	//register) during which a possible second tap event can be detected.
	//The scale factor is 1.25 ms/LSB. A value of 0 disables the double tap
	//function
void Set_Latent(uint8_t val);
//*************************************************************************************
//*************************************************************************************
	//The window register is eight bits and contains an unsigned time
	//value representing the amount of time after the expiration of the
	//latency time (determined by the latent register) during which a
	//second valid tap can begin. The scale factor is 1.25 ms/LSB. A
void Set_Window(uint8_t val);
//*************************************************************************************
//*************************************************************************************
	//The THRESH_ACT register is eight bits and holds the threshold
	//value for detecting activity. The data format is unsigned, so the
	//magnitude of the activity event is compared with the value in
	//the THRESH_ACT register. The scale factor is 62.5 mg/LSB.
	//A value of 0 may result in undesirable behavior if the activity
	//interrupt is enabled.
void Set_ThreshACT(uint8_t val);
//*************************************************************************************
//*************************************************************************************
	//The THRESH_INACT register is eight bits and holds the threshold
	//value for detecting inactivity. The data format is unsigned, so
	//the magnitude of the inactivity event is compared with the value
	//in the THRESH_INACT register. The scale factor is 62.5 mg/LSB.
	//A value of 0 may result in undesirable behavior if the inactivity
	//interrupt is enabled.
void Set_ThreshINACT(uint8_t val);
//*************************************************************************************
//*************************************************************************************

	//value of 0 disables the double tap function.

void Get_AxisReadings();
uint8_t WriteRegister_SingleByte(uint8_t reg, uint8_t data);
uint8_t ReadRegister_SingleByte(uint8_t reg);
uint8_t GetdeviceID(void);


/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/
#define ADXL345_FixedID	0xE5
#define ADXL345_NOP		0xFF
#define DEVID  			0x00 	//Device ID register holds a fixed device ID code of 0xE5.
#define THRESH_TAP  	0x1D	//Tap threshold
#define OFSX	   		0x1E	//X-axis offset
#define OFSY    		0x1F	//Y-axis offset
#define OFSZ			0x20	//Z-axis offset
#define DUR				0x21	//Tap duration
#define Latent			0x22	//Tap latency
#define Window			0x23	//Tap window
#define THRESH_ACT  	0x24	//Activity threshold
#define THRESH_INACT 	0x25	//Inactivity threshold
#define TIME_INACT		0x26	//Inactivity time
#define ACT_INACT_CTL	0x27	//Axis enable control for activity and inactivity detection
#define THRESH_FF		0x28	//Free-fall threshold
#define TIME_FF			0x29	//Free-fall time
#define TAP_AXES		0X2A	//Axis control for single tap/double tap
#define ACT_TAP_STATUS	0x2B	//Source of single tap/double tap
#define BW_RATE			0x2C	//Data rate and power mode control
#define POWER_CTL		0x2D	//Power-saving features control
#define INT_ENABLE		0x2E	//Interrupt enable control
#define INT_MAP			0x2F	//Interrupt mapping control
#define INT_SOURCE		0x30	//Source of interrupts
#define DATA_FORMAT		0x31	//Data format control
#define DATAX0			0x32	//X-Axis Data 0
#define DATAX1			0x33	//X-Axis Data 1
#define DATAY0			0x34	//Y-Axis Data 0
#define DATAY1			0x35	//Y-Axis Data 1
#define DATAZ0			0x36	//Z-Axis Data 0
#define DATAZ1			0x37	//Z-Axis Data 1
#define FIFO_CTL		0x38	//FIFO control
#define FIFO_STATUSS	0x39	//FIFO status

/* Bit Mnemonics */
#define WR			7 //Set to read, Clear to write
#define MB			6 //Set to read Multi-Byte, Clear to read 1 byte

//Data Format
#define SELF_TEST	7
#define SPI			6
#define INT_INVERT	5
#define FULL_RES	3
#define Justify		2
#define Range1		1
#define Range0 		0

//Power CTL
#define Link		5
#define AUTO_SLEEP	4
#define Measure		3
#define Sleep		2
#define Wake1		1
#define Wake0		0

//FIFO_CTL
#define FIFO_MODE_D7	7
#define FIFO_MODE_D6	6
#define Trigger 		5
#define	Samples_D4		4
#define	Samples_D3		3
#define	Samples_D2		2
#define	Samples_D1		1
#define	Samples_D0		0

#endif //!ADXL345_H




