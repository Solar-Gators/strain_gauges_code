/*
 * ADS1115 Driver
 *
 * Authors: Joseph Sinder, Jason Flick
 * Created: 04/02/2026
 */

#pragma once

#include "stm32l4xx_hal_conf.h"
#include "LSM6DSO.h"

#define ADS1115_I2C_ADDR 0x48
#define ADS1115_CONVERSION_REG 0x00
#define ADS1115_CONFIG_REG 0x01
#define WHEATSTONE_BRIDGE_VOLTAGE 3.3f
#define GAUGE_FACTOR 2.0f
#define STRAIN_MASS 0.985f // mass of part of chassis gauge is on
#define YOUNGS_MODULUS 231000000000.0f // Young's Modulus value for strain gauge
#define STRAIN_AREA 0.2551f // Cross-section area of mount for gauge


typedef struct {
	I2C_HandleTypeDef* hi2c;
	uint8_t i2c_addr;
	//raw data from ADC
	int16_t raw_strain[3]; // AIN0, AIN1, AIN2
	float strain_voltage[3];
	float strain_converted[3];
} ADS1115_Handle;

uint8_t ADS1115_init(ADS1115_Handle *dev, I2C_HandleTypeDef *hi2c, uint8_t addr);

//Get raw data from ADC
void ADS1115_ReadRawData(ADS1115_Handle *dev, uint8_t pin);

void ADS1115_ConvertToVoltage(ADS1115_Handle *dev, int16_t avg_ain0, int16_t avg_ain1, int16_t avg_ain2);

void ADS1115_AdjustedStrain(ADS1115_Handle *ads_dev, LSM6DSO_Handle *imu_dev);
