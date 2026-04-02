#include "LSM6DSO.h"

uint8_t ADS1115_init(ADS1115_Handle *dev, I2C_HandleTypeDef *hi2c, uint8_t addr){
	dev->hi2c = hi2c;
	dev->i2c_addr = (addr << 1);
	uint8_t read_chip_id;
	ADS1115_ReadRegister(dev, ADS1115_addr, &read_chip_id);

	if(read_chip_id != ADS1115_addr){
		return 0;
	}

	ADS1115_ReadCalibrationData(dev);

	uint8_t data;

	//set oversampling??
}

void ADS1115_ReadRawData(ADS1115_Handle *dev, int32_t *adc_strain){

}

static uint8_t ADS1115_ReadCalibrationData(ADS1115_Handle *dev){

}
