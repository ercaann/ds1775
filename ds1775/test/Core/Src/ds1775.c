/*
 * DS1775.c
 *
 *  Created on: May 8, 2020
 *      Author: ERCAN
 */

#include <ds1775.h>


DS1775_Result DS1775_ReadTempature(I2C_HandleTypeDef *hi2c, uint16_t DS1775_ADDR, DS1775_Data *pData, DS1775_Resolution resolution)
{

	uint16_t temperature;
	int8_t digit, minus = 0;
	uint8_t data[2];
	float decimal;

	while (HAL_I2C_Master_Transmit(hi2c, DS1775_ADDR, TEMPERATURE, 1, 1000) != HAL_OK);

	while (HAL_I2C_Master_Receive(hi2c, DS1775_ADDR, data, 2, 1000) != HAL_OK);

	// data[0]=MSB  data[1]=LSB
	temperature =  (data[0] << 8) | data[1] ;

	//check if temperature is negative
	if(temperature & 0x8000){

		temperature = ~temperature + 1;
		minus = 1;
	}

	//store temperature integer and decimal digits
	digit = temperature >> 8;

	switch (resolution)
	{
	case 0:
		decimal = (temperature>>7) & 0x01;
		decimal *= (float)DS1775_DECIMAL_STEPS_9BIT;
		break;

	case 1:
		decimal = (temperature>>6) & 0x03;
		decimal *= (float)DS1775_DECIMAL_STEPS_10BIT;
		break;

	case 2:
		decimal = (temperature>>5) & 0x07;
		decimal *= (float)DS1775_DECIMAL_STEPS_11BIT;
		break;

	case 3:
		decimal = (temperature>>4) & 0x0F;
		decimal *= (float)DS1775_DECIMAL_STEPS_12BIT;
		break;
	default:
		decimal = 0xFF;
		digit=0;
	}

	decimal = digit + decimal;

	//check for negative
	if(minus){
		decimal = 0 - decimal;
	}

	pData->Temperature = decimal;

		return DS1775_Result_Ok;
}


