/*
 * ADS1115 Driver
 *
 * Authors: Joseph Sinder, Jason Flick
 * Created: 04/02/2026
 */

#pragma once

#include "stm32l4xx_hal_conf.h"

#define ADS1115_addr 0x48

typedef struct {
	I2C_HandleTypeDef* hi2c;
	uint8_t i2c_addr;
	//raw data from ADC
	int16_t raw_strain;
	int16_t strain_voltage;
	int16_t strain_converted;
} ADS1115_Handle;
