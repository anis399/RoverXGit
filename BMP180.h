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
 * UP Pressure data 16-19bit
 * UT temperature data 16bit
 */
// SCL 1.3
// SDA 1.2
#include "DAVE.h"

#define INT_BITS 8
#define _BV(a) (1 << (a))      	//Bit Value
#define _DS(a, b) (a << (b))	//Data shift left  (a) b time
#define _DSn(a, b) (a >> (b))	//Data shift right (a) b time
#define _AndLow4(a) (a & (15))
#define Max(a, b) (a>b?a:b)
#define Min(a, b) (a<b?a:b)
#define ROTATE_LEFT(data, pos) ((data << pos)|(data >> (INT_BITS - pos)))
#define ROTATE_RIGHT(data, pos) ((data >> pos)|(data << (INT_BITS - pos)))

uint8_t BMP180_DataSent[32];
uint8_t BMP180_DataRead[32];
uint8_t BMP180_I2C_Status;

uint8_t BMP180_init(); // will set BME180 in weather monitoring
void I2C_Scanner();
uint8_t Text_Communication(uint8_t SlaveAddress);

uint8_t BMP180_Test(void);



/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/

#define BME180_Address				0x76
#define BMP180_R					0xEF
#define BMP180_W					0xEE
#define BMP180_FixedID				0x55
#define BMP180_FixedAlternativID	0x60
#define BMP180_Measurment_Control	0xF4

/***********************************************************************************************************************
 * REGISTERS
 **********************************************************************************************************************/
#define BMP180_ID_Reg				0xD0
#define BMP180_Reset				0xE0  //Write 0xB6 to reset, Readout gives 0x00 always
#define BMP180_CTRL_hum				0xF2  //3 lsb bits -> 000 Skipped OUTPUT always 0x8000, 001 OverSampling 1, 010 2OS, 011 4OS, 100 8OS, else 16OS
#define BMP180_Status				0xF3  //Bit3 set when measuring, Bit0 set when saving data to NVM
#define BMP180_CTRL_meas			0xF4  //[7:5]temp  -> 000 Skipped OUTPUT always 0x8000, 001 OverSampling 1, 010 2OS, 011 4OS, 100 8OS, else 16OS
										  //[4:2]press -> 000 Skipped OUTPUT always 0x8000, 001 OverSampling 1, 010 2OS, 011 4OS, 100 8OS, else 16OS
										  //[1:0]mode  -> 00 Sleep Mode, 11 Normal Mode, else Forced Mode
#define BMP180_CONFIG				0xF5  //[7:5]time[ms] delay between measures in normal mode
										  //[4:2] IIR coefficient, 000->OFF, 001->2, 010->4, 011->8, else 16
										  //Bit0 enables 3wire SPI.
#define	BMP180_PressMSB				0xF7  //[19:12] -> [7:0]
#define	BMP180_PressLSB				0xF8  //[11:4]  -> [7:0]
#define	BMP180_PressXLSB			0xF9  //[3:0]	-> [7:4]
#define	BMP180_TempMSB				0xFA  //[19:12] -> [7:0]
#define	BMP180_TempLSB				0xFB  //[11:4]  -> [7:0]
#define	BMP180_TempXLSB			    0xFC  //[3:0]	-> [7:4]
#define	BMP180_HumMSB				0xFD  //[15:8] -> [7:0]
#define	BMP180_HumLSB				0xFE  //[7:0]  -> [7:0]




