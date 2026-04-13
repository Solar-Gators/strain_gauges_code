/*
 * ADS1115 Driver
 *
 * Authors: Joseph Sinder, Jason Flick
 * Created: 04/02/2026
 */

#pragma once

#include "stm32l4xx_hal_conf.h"

#define ADS1115_I2C_ADDR 0x48
#define ADS1115_CONVERSION_REG 0x00
#define ADS1115_CONFIG_REG 0x01


typedef struct {
	I2C_HandleTypeDef* hi2c;
	uint8_t i2c_addr;
	//raw data from ADC
	int16_t raw_strain[2]; //low byte AIN0, high byte AIN1
	float strain_voltage;
	float strain_converted;
} ADS1115_Handle;

uint8_t ADS1115_init(ADS1115_Handle *dev, I2C_HandleTypeDef *hi2c, uint8_t addr);

//Get raw data from ADC
void ADS1115_ReadRawData(ADS1115_Handle *dev, uint8_t pin);
