#include "LSM6DSO.h"

uint8_t LSM6DSO_init(LSM6DSO_Handle *dev, I2C_HandleTypeDef *hi2c, uint8_t addr){
	dev->hi2c = hi2c;
	dev->i2c_addr = (addr << 1);
	uint8_t read_chip_id;
	LSM6DSO_ReadRegister(dev, LSM6DSO_addr, &read_chip_id);

	if(read_chip_id != LSM6DSO_addr){
		return 0;
	}

	LSM6DSO_ReadCalibrationData(dev);

	uint8_t data;

	//set oversampling??
}

void LSM6DSO_ReadRawData(LSM6DSO_Handle *dev, int32_t *adc_strain){

}

static uint8_t LSM6DSO_ReadCalibrationData(LSM6DSO_Handle *dev){

}
