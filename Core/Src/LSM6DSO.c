#include "LSM6DSO.h"

uint8_t LSM6DSO_init(LSM6DSO_Handle *dev, I2C_HandleTypeDef *hi2c, uint8_t addr){
	dev->hi2c = hi2c;
	dev->i2c_addr = (addr << 1);
	uint8_t who_am_i;
	LSM6DSO_ReadRegister(dev, LSM6DSO_WHO_AM_I_REG, &who_am_i, 1);

	if (who_am_i != LSM6DSO_WHO_AM_I) {
		return 0;
	}

	//12.5 Hz Low-Power CHANGE LATER IF NEEDED (Check what max vibration on car actually is)
	uint8_t ctrl1 = 0x10;
	uint8_t ctrl2 = 0x10;

	LSM6DSO_WriteRegister(dev, LSM6DSO_CTRL1_XL, &ctrl1, 1);
	LSM6DSO_WriteRegister(dev, LSM6DSO_CTRL2_G, &ctrl2, 1);

	return 1;
}


// LSM6DSO_ReadRawData
// Input:
// dev - Pointer to the LSM6DSO handle containing the I2C interface and IMU data arrays
//
// Description:
// Reads 6 bytes of accelerometer data and 6 bytes of gyroscope data from the
// LSM6DSO over I2C. The function combines each low and high byte pair into a
// signed 16-bit raw value and stores the X, Y, and Z axis data in
// dev->raw_accel[] and dev->raw_gyro[].
//
// Note:
// INT1 and INT2 are connected to STM32 GPIO pins for optional interrupt use,
// but this function uses polling over I2C and does not require those pins.
void LSM6DSO_ReadRawData(LSM6DSO_Handle *dev)
{
    uint8_t accel_data[6];
    uint8_t gyro_data[6];

    // Read 6 bytes starting at OUTX_L_A:
    // X_L, X_H, Y_L, Y_H, Z_L, Z_H
    if (LSM6DSO_ReadRegister(dev, LSM6DSO_OUTX_L_A, accel_data, 6) != HAL_OK) {
        return;
    }

    // Read 6 bytes starting at OUTX_L_G:
    // X_L, X_H, Y_L, Y_H, Z_L, Z_H
    if (LSM6DSO_ReadRegister(dev, LSM6DSO_OUTX_L_G, gyro_data, 6) != HAL_OK) {
        return;
    }

    // Accelerometer raw data
    dev->raw_accel[0] = (int16_t)((accel_data[1] << 8) | accel_data[0]); // X
    dev->raw_accel[1] = (int16_t)((accel_data[3] << 8) | accel_data[2]); // Y
    dev->raw_accel[2] = (int16_t)((accel_data[5] << 8) | accel_data[4]); // Z

    // Gyroscope raw data
    dev->raw_gyro[0] = (int16_t)((gyro_data[1] << 8) | gyro_data[0]); // X
    dev->raw_gyro[1] = (int16_t)((gyro_data[3] << 8) | gyro_data[2]); // Y
    dev->raw_gyro[2] = (int16_t)((gyro_data[5] << 8) | gyro_data[4]); // Z
}

static HAL_StatusTypeDef LSM6DSO_ReadRegister(LSM6DSO_Handle *dev, uint8_t reg, uint8_t *data, uint16_t len){
	return HAL_I2C_Mem_Read(dev->hi2c, dev->i2c_addr, reg, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY);
}

static HAL_StatusTypeDef LSM6DSO_WriteRegister(LSM6DSO_Handle *dev, uint8_t reg, uint8_t *data, uint16_t len){
	return HAL_I2C_Mem_Write(dev->hi2c, dev->i2c_addr, reg, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY);
}
