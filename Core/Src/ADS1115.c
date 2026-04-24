#include "ADS1115.h"
#include "LSM6DSO.h"

uint8_t ADS1115_init(ADS1115_Handle *dev, I2C_HandleTypeDef *hi2c, uint8_t addr){
	dev->hi2c = hi2c;
	dev->i2c_addr = (addr << 1);

	//check ADS1115 ready
	if ((HAL_I2C_IsDeviceReady(dev->hi2c, dev->i2c_addr, 3, HAL_MAX_DELAY)) != HAL_OK) {
		return 0;
	}
	return 1;
}

// Read Raw Data function
// This function configures the ADS1115 to read a selected input channel,
// starts a single conversion, waits for it to complete, and then reads the
// 16-bit result from the conversion register. The result is stored as a
// signed integer in dev->raw_strain.
// ADS1115_ReadRawData
// Inputs:
// dev  - Pointer to the device handle, which contains the I2C peripheral and stores ADC results
// pin  - Selects which analog input to read:
//        0 -> AIN0 (OUT2 from Wheatstone bridge)
//        1 -> AIN1 (OUT3 from Wheatstone bridge)
//        2 -> AIN2 (OUT1 from Wheatstone bridge)
//        3 -> AIN3 (unused or GND)
//
// Description:
// This function selects the desired ADC channel, triggers a single conversion,
// reads the result from the ADS1115 conversion register via I2C, and stores
// the raw 16-bit ADC value in the device structure.
void ADS1115_ReadRawData(ADS1115_Handle *dev, uint8_t pin)
{
    uint8_t config_data[2];
    uint8_t data[2];
    uint16_t config = 0;

    config |= (1 << 15); // start conversion

    switch(pin)
    {
        case 0: config |= (0x4 << 12); break; // AIN0
        case 1: config |= (0x5 << 12); break; // AIN1
        case 2: config |= (0x6 << 12); break; // AIN2
        case 3: config |= (0x7 << 12); break; // AIN3
        default: return;
    }

    config |= (0x1 << 9);  // ±4.096V
    config |= (1 << 8);    // single-shot
    config |= (0x4 << 5);  // 128 SPS
    config |= 0x0003;      // disable comparator

    config_data[0] = (config >> 8) & 0xFF;
    config_data[1] = config & 0xFF;

    if (ADS1115_WriteRegister(dev, ADS1115_CONFIG_REG, config_data, 2) != HAL_OK) {
        return;
    }

    HAL_Delay(10);

    if (ADS1115_ReadRegister(dev, ADS1115_CONVERSION_REG, data, 2) != HAL_OK) {
        return;
    }

    dev->raw_strain[pin] = (int16_t)((data[0] << 8) | data[1]);
}

void ADS1115_ConvertToVoltage(ADS1115_Handle *dev, int16_t avg_ain0, int16_t avg_ain1, int16_t avg_ain2){
	 // convert raw strain to voltage, subtract 1.65V reference offset, calibrate at startup (COULD BE DIFF FROM 1.65)
	dev->strain_voltage[0] = (avg_ain0 * 4.096f / 32768.0f) - 1.65f;
	dev->strain_voltage[1] = (avg_ain1 * 4.096f / 32768.0f) - 1.65f;
	dev->strain_voltage[2] = (avg_ain2 * 4.096f / 32768.0f) - 1.65f;
}

static HAL_StatusTypeDef ADS1115_ReadRegister(ADS1115_Handle *dev, uint8_t reg, uint8_t *data, uint16_t len){
	return HAL_I2C_Mem_Read(dev->hi2c, dev->i2c_addr, reg, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY);
}

void ADS1115_AdjustedStrain(ADS1115_Handle *ads_dev, LSM6DSO_Handle *imu_dev){
	for (int i = 0; i < 3; i++){
		float inertial_strain = STRAIN_MASS * (imu_dev->accel_converted[i] - imu_dev->gravity_oriented[i]) / (YOUNGS_MODULUS * STRAIN_AREA);
		float inertial_voltage = inertial_strain * (GAUGE_FACTOR * WHEATSTONE_BRIDGE_VOLTAGE / 2.0f);
		ads_dev->strain_converted[i] = ads_dev->strain_voltage[i] - inertial_voltage;
	}
}

static HAL_StatusTypeDef ADS1115_WriteRegister(ADS1115_Handle *dev, uint8_t reg, uint8_t *data, uint16_t len){
	return HAL_I2C_Mem_Write(dev->hi2c, dev->i2c_addr, reg, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY);
}
