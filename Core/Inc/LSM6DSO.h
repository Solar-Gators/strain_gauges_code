/*
 * LSM6DSO Driver
 *
 * Authors: Joseph Sinder, Jason Flick
 * Created: 04/02/2026
 */

#pragma once

#include "stm32l4xx_hal_conf.h"

#define LSM6DSO_I2C_ADDR 0x6A
#define LSM6DSO_WHO_AM_I_REG 0x0F
#define LSM6DSO_WHO_AM_I 0x6C
#define LSM6DSO_CTRL1_XL 0x10
#define LSM6DSO_CTRL2_G 0x11

// Output data register starting addresses
#define LSM6DSO_OUTX_L_G      0x22
#define LSM6DSO_OUTX_L_A      0x28

typedef struct {
	I2C_HandleTypeDef* hi2c;
	uint8_t i2c_addr;
	//raw data from IMU
	int16_t raw_accel[3]; // X, Y, Z data
	int16_t raw_gyro[3]; // X, Y, Z data
	float accel_converted[3]; // in m/s^2
	float gyro_converted[3]; // in deg / s
} LSM6DSO_Handle;

uint8_t LSM6DSO_init(LSM6DSO_Handle *dev, I2C_HandleTypeDef *hi2c, uint8_t addr);

//Get Raw Data from IMU
void LSM6DSO_ReadRawData(LSM6DSO_Handle *dev);

// Low-Level Functions
//****Chat recommends removing these and adding to them to the .c file only
static HAL_StatusTypeDef LSM6DSO_ReadRegister(LSM6DSO_Handle *dev, uint8_t reg, uint8_t *data, uint16_t len);
static HAL_StatusTypeDef LSM6DSO_WriteRegister(LSM6DSO_Handle *dev, uint8_t reg, uint8_t *data, uint16_t len);
