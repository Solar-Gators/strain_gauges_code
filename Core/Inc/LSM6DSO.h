/*
 * LSM6DSO Driver
 *
 * Authors: Joseph Sinder, Jason Flick
 * Created: 04/02/2026
 */

#pragma once

#include "stm32l4xx_hal_conf.h"

#define LSM6DSO_addr 0x63

typedef struct {
	I2C_HandleTypeDef* hi2c;
	uint8_t i2c_addr;
	//raw data from IMU
	int16_t raw_IMU_data;
	int8_t IMU_accel_converted;
	int8_t IMU_gyro_converted;
} LSM6DSO_Handle;
