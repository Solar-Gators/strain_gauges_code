/*
 * I2C, CAN Driver for Strain Gauge Sensor
 *
 * Authors: Joseph Sinder,
 * Created: 04/02/2026
 */

#pragma once

#include "stm32l4xx_hal_conf.h"

typedef struct {
	I2C_HandleTypeDef* hi2c;
	uint8_t i2c_addr;
	//raw data from ADC, IMU
	int16_t raw_strain;
	int16_t strain_voltage;
	int16_t strain_converted;
	int16_t raw_IMU_data;
	int8_t IMU_accel_converted;
	int8_t IMU_gyro_converted;
	int16_t adjusted_strain;
} Strain_Gauge_Handle;
