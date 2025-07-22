#include "sensors_config.h"

HAL_StatusTypeDef SENSORS_I2C_Read(uint16_t DevAddress, uint8_t Reg, uint8_t *pData, uint16_t Size) {
    return HAL_I2C_Mem_Read(&hi2c2, DevAddress, Reg, I2C_MEMADD_SIZE_8BIT, pData, Size, HAL_MAX_DELAY);
}

HAL_StatusTypeDef SENSORS_I2C_Write(uint16_t DevAddress, uint8_t Reg, uint8_t *pData, uint16_t Size) {
    return HAL_I2C_Mem_Write(&hi2c2, DevAddress, Reg, I2C_MEMADD_SIZE_8BIT, pData, Size, HAL_MAX_DELAY);
}

void SENSORS_LSM6DSR_Init(void) {
    uint8_t data = LSM6DSR_CTRL1_XL_ODR; 
    SENSORS_I2C_Write(LSM6DSR_ADDR, LSM6DSR_CTRL1_XL, &data, 1); // Configura o acelerometro
    
    data = LSM6DSR_CTRL2_G_ODR;
    SENSORS_I2C_Write(LSM6DSR_ADDR, LSM6DSR_CTRL2_G, &data, 1); // Configura o giroscopio
}

void SENSORS_Configure_SensorHub_LIS3MDL(void) {
    uint8_t data[3];

    // Endereço (leitura): addr do LIS3MDL + bit leitura
    data[0] = (0x1C << 1) | 0x01;
    // Sub-endereço: OUTX_L_REG do LIS3MDL
    data[1] = 0x28;
    // Config: leitura 6 bytes
    data[2] = (6 & 0x07) | (0<<3); // se necessária repetição, movimente bits adequadamente
    SENSORS_I2C_Write(LSM6DSR_ADDR, LSM6DSR_SLV0_ADDR, &data[0], 3);

    // Ativar leitura automática
    data[0] = 0x01; // 1 av de leitura
    SENSORS_I2C_Write(LSM6DSR_ADDR, LSM6DSR_SLV0_CONFIG, &data[0], 1);
}

void SENSORS_LIS3MDL_Init(void) {
    uint8_t data;
    data = 0x70; // ODR=155 Hz
    SENSORS_I2C_Write(LIS3MDL_ADDR, LIS3MDL_CTRL_REG1, &data, 1);
    data = 0x20; // escala ±4 gauss
    SENSORS_I2C_Write(LIS3MDL_ADDR, LIS3MDL_CTRL_REG2, &data, 1);
    data = 0x00; // modo contínuo
    SENSORS_I2C_Write(LIS3MDL_ADDR, LIS3MDL_CTRL_REG3, &data, 1);
}

void SENSORS_8_to_16bits(uint8_t* data, int16_t* output){
    output[0] = (int16_t)(data[1] << 8 | data[0]); // X
    output[1] = (int16_t)(data[3] << 8 | data[2]); // Y
    output[2] = (int16_t)(data[5] << 8 | data[4]); // Z

    for (size_t i = 3; i < 8; i++){
        output[i] = 0;
    }

}

void SENSORS_Read_Accelerometer_8(uint8_t* buf) {
    HAL_I2C_Mem_Read(&hi2c2, LSM6DSR_ADDR, LSM6DSR_OUTX_L_XL, I2C_MEMADD_SIZE_8BIT, buf, 6, HAL_MAX_DELAY);
}

void SENSORS_Read_Accelerometer_16(int16_t* buf) {
    uint8_t buf_8[6];
    SENSORS_Read_Accelerometer_8(buf_8);
    SENSORS_8_to_16bits(buf_8, buf);    
}

void SENSORS_Read_Gyroscope_8(uint8_t* buf) {
    HAL_I2C_Mem_Read(&hi2c2, LSM6DSR_ADDR, LSM6DSR_OUTX_L_G, I2C_MEMADD_SIZE_8BIT, buf, 6, HAL_MAX_DELAY);
}

void SENSORS_Read_Gyroscope_16(int16_t* buf) {
    uint8_t buf_8[6];
    SENSORS_Read_Gyroscope_8(buf_8);
    SENSORS_8_to_16bits(buf_8, buf);    
}

void SENSORS_Read_Magnetometer_8(uint8_t* buf) {
    HAL_I2C_Mem_Read(&hi2c2, LSM6DSR_ADDR, LSM6DSR_SENSORHUB1, I2C_MEMADD_SIZE_8BIT, buf, 6, HAL_MAX_DELAY);
}

void SENSORS_Read_Magnetometer_16(int16_t* buf) {
    uint8_t buf_8[6];
    SENSORS_Read_Magnetometer_8(buf_8);
    SENSORS_8_to_16bits(buf_8, buf);    
}

void SENSORS_Print(int16_t* data){
    printf("X: %d, Y: %d, Z: %d\n", data[0], data[1], data[2]);
}

void SENSORS_Print_for_Reconstruction(int id, int16_t* data) {
    printf("%d,", id);
    size_t vecSize = 8;
    for (size_t i = 0; i < vecSize; i++){
        printf("%d", data[i]);
        if (i < vecSize - 1)
            putchar(',');
    }
    putchar('\n');
}