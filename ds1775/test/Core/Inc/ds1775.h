/*
 * DS1775.h
 *
 *  Created on: May 8, 2020
 *      Author: ERCAN
 */
#include<stdint.h>
#include<string.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"

#define DS1775R_ADDR		0x48
#define DS1775R1_ADDR		0x48 | 1
#define DS1775R2_ADDR		0x48 | 2
#define DS1775R3_ADDR		0x48 | 3
#define DS1775R4_ADDR		0x48 | 4
#define DS1775R5_ADDR		0x48 | 5
#define DS1775R6_ADDR		0x48 | 6
#define DS1775R7_ADDR		0x48 | 7

#define TEMPERATURE			0x00
#define CONFIGURATION		0x01
#define THYST				0x02
#define TOS					0x03

#define ENABLE				1
#define DISABLE				0
#define HIGH				ENABLE
#define LOW					DISABLE

#define DS1775_DECIMAL_STEPS_12BIT		0.0625
#define DS1775_DECIMAL_STEPS_11BIT		0.125
#define DS1775_DECIMAL_STEPS_10BIT		0.25
#define DS1775_DECIMAL_STEPS_9BIT		0.5

typedef enum {
	DS1775_Result_Ok = 0x00,
	DS1775_Result_Error,
	DS1775_Result_DeviveNotConnected,
	DS1775_Device_Invalid
}DS1775_Result;

typedef enum{
	DS1775_COMPAROTOR_MODE=0x00,
	DS1775_INTERRUPT_MODE=0x01
}DS1775_Mode;

typedef enum{
	DS1775_TEMP_RES_9 = 0x00,
	DS1775_TEMP_RES_10 = 0x01,
	DS1775_TEMP_RES_11 = 0x02,
	DS1775_TEMP_RES_12 = 0x03
}DS1775_Resolution;

typedef enum{
	DS1775_FAULT_TOL1 = 0x00,
	DS1775_FAULT_TOL2 = 0x01,
	DS1775_FAULT_TOL4 = 0x02,
	DS1775_FAULT_TOL6 = 0x03
}DS1775_Fault_Tolerance;

typedef union {
	struct{
		uint8_t SD:1;
		uint8_t TM:1;
		uint8_t POL:1;
		uint8_t F0F1:2;
		uint8_t R0R1:2;
		uint8_t RW:1;
	}F;
	uint8_t Status;
}DS1775_Config;

typedef struct{
	float Temperature;
	float Tos;
	float Thyst ;
}DS1775_Data;


DS1775_Result DS1775_Init(I2C_HandleTypeDef *pI2Cx, DS1775_Config *pConfig, DS1775_Mode Mode, DS1775_Resolution Res, DS1775_Fault_Tolerance Fault);
DS1775_Result DS1775_ReadTempature(I2C_HandleTypeDef *hi2c, uint16_t DS1775_ADDR, DS1775_Data *pData, DS1775_Resolution resolution);


#ifndef INC_DS1775_H_
#define INC_DS1775_H_



#endif /* INC_DS1775_H_ */
