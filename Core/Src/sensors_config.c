#include "sensors_config.h"

HAL_StatusTypeDef I2C_Read(uint16_t DevAddress, uint8_t Reg, uint8_t *pData, uint16_t Size) {
    return HAL_I2C_Mem_Read(&hi2c2, DevAddress, Reg, I2C_MEMADD_SIZE_8BIT, pData, Size, HAL_MAX_DELAY);
}

HAL_StatusTypeDef I2C_Write(uint16_t DevAddress, uint8_t Reg, uint8_t *pData, uint16_t Size) {
    return HAL_I2C_Mem_Write(&hi2c2, DevAddress, Reg, I2C_MEMADD_SIZE_8BIT, pData, Size, HAL_MAX_DELAY);
}

void LSM6DSR_Init(void) {
    uint8_t data;
    data = 0x60; // ODR=104 Hz, accel 2 g
    I2C_Write(LSM6DSR_ADDR, LSM6DSR_CTRL1_XL, &data, 1);
    data = 0x60; // ODR=104 Hz, gyro 2000 dps
    I2C_Write(LSM6DSR_ADDR, LSM6DSR_CTRL2_G, &data, 1);
}

void Configure_SensorHub_LIS3MDL(void) {
    uint8_t data[3];

    // Endereço (leitura): addr do LIS3MDL + bit leitura
    data[0] = (0x1C << 1) | 0x01;
    // Sub-endereço: OUTX_L_REG do LIS3MDL
    data[1] = 0x28;
    // Config: leitura 6 bytes
    data[2] = (6 & 0x07) | (0<<3); // se necessária repetição, movimente bits adequadamente
    I2C_Write(LSM6DSR_ADDR, LSM6DSR_SLV0_ADDR, &data[0], 3);

    // Ativar leitura automática
    data[0] = 0x01; // 1 av de leitura
    I2C_Write(LSM6DSR_ADDR, LSM6DSR_SLV0_CONFIG, &data[0], 1);
}

void LIS3MDL_Init(void) {
    uint8_t data;
    data = 0x70; // ODR=155 Hz
    I2C_Write(LIS3MDL_ADDR, LIS3MDL_CTRL_REG1, &data, 1);
    data = 0x20; // escala ±4 gauss
    I2C_Write(LIS3MDL_ADDR, LIS3MDL_CTRL_REG2, &data, 1);
    data = 0x00; // modo contínuo
    I2C_Write(LIS3MDL_ADDR, LIS3MDL_CTRL_REG3, &data, 1);
}

void Read_Accelerometer(int16_t accelerometer[3]) {
    uint8_t buf[6];
    HAL_I2C_Mem_Read(&hi2c2, LSM6DSR_ADDR, LSM6DSR_OUTX_L_XL, I2C_MEMADD_SIZE_8BIT, buf, 6, HAL_MAX_DELAY);

    accelerometer[0] = (int16_t)(buf[1] << 8 | buf[0]); // X
    accelerometer[1] = (int16_t)(buf[3] << 8 | buf[2]); // Y
    accelerometer[2] = (int16_t)(buf[5] << 8 | buf[4]); // Z
}

void Read_Gyroscope(int16_t gyroscope[3]) {
    uint8_t buf[6];
    HAL_I2C_Mem_Read(&hi2c2, LSM6DSR_ADDR, LSM6DSR_OUTX_L_G, I2C_MEMADD_SIZE_8BIT, buf, 6, HAL_MAX_DELAY);

    gyroscope[0] = (int16_t)(buf[1] << 8 | buf[0]); // X
    gyroscope[1] = (int16_t)(buf[3] << 8 | buf[2]); // Y
    gyroscope[2] = (int16_t)(buf[5] << 8 | buf[4]); // Z
}

void Read_Magnetometer(int16_t magnetometer[3]) {
    uint8_t buf[6];
    HAL_I2C_Mem_Read(&hi2c2, LSM6DSR_ADDR, LSM6DSR_SENSORHUB1, I2C_MEMADD_SIZE_8BIT, buf, 6, HAL_MAX_DELAY);

    magnetometer[0] = (int16_t)(buf[1] << 8 | buf[0]); // X
    magnetometer[1] = (int16_t)(buf[3] << 8 | buf[2]); // Y
    magnetometer[2] = (int16_t)(buf[5] << 8 | buf[4]); // Z
}
