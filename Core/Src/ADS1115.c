#include "ADS1115.h"

uint8_t ADS1115_init(ADS1115_Handle *dev, I2C_HandleTypeDef *hi2c, uint8_t addr){
	dev->hi2c = hi2c;
	dev->i2c_addr = (addr << 1);

	//check ADS1115 ready
	if ((HAL_I2C_IsDeviceReady(dev->hi2c, dev->i2c_addr, 3, HAL_MAX_DELAY)) != HAL_OK) {
		return 0;
	}

	uint8_t config_data[2];
	config_data[0] = 0x84; // MSB of Config register to be written
	config_data[1] = 0x83; // LSB of Config register to be written
	ADS1115_WriteRegister(dev, ADS1115_CONFIG_REG, config_data, 2);

	return 1;
}

void ADS1115_ReadRawData(ADS1115_Handle *dev, uint8_t pin){

}

static HAL_StatusTypeDef ADS1115_ReadRegister(ADS1115_Handle *dev, uint8_t reg, uint8_t *data, uint16_t len){
	return HAL_I2C_Mem_Read(dev->hi2c, dev->i2c_addr, reg, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY);
}

static HAL_StatusTypeDef ADS1115_WriteRegister(ADS1115_Handle *dev, uint8_t reg, uint8_t *data, uint16_t len){
	return HAL_I2C_Mem_Write(dev->hi2c, dev->i2c_addr, reg, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY);
}
