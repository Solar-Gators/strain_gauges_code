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

void LSM6DSO_ReadRawData(LSM6DSO_Handle *dev){

}

static HAL_StatusTypeDef LSM6DSO_ReadRegister(LSM6DSO_Handle *dev, uint8_t reg, uint8_t *data, uint16_t len){
	return HAL_I2C_Mem_Read(dev->hi2c, dev->i2c_addr, reg, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY);
}

static HAL_StatusTypeDef LSM6DSO_WriteRegister(LSM6DSO_Handle *dev, uint8_t reg, uint8_t *data, uint16_t len){
	return HAL_I2C_Mem_Write(dev->hi2c, dev->i2c_addr, reg, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY);
}
