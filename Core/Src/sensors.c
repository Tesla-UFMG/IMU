#include "sensors.h"


void SENSORS_LSM6DSR_Init(void) {
    // Configura o ODR do Acelerômetro
    uint8_t data = LSM6DSR_CTRL1_XL_ODR; 
    I2C_Write(LSM6DSR_ADDR, LSM6DSR_CTRL1_XL, &data, 1); 

    // Configura o ODR do Giroscópio
    data = LSM6DSR_CTRL2_G_ODR;
    I2C_Write(LSM6DSR_ADDR, LSM6DSR_CTRL2_G, &data, 1); 
}

void SENSORS_Configure_SensorHub_LIS3MDL(void) {
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

void SENSORS_LIS3MDL_Init(void) {
    uint8_t data;
    data = 0x70; // ODR=155 Hz
    I2C_Write(LIS3MDL_ADDR, LIS3MDL_CTRL_REG1, &data, 1);
    data = 0x20; // escala ±4 gauss
    I2C_Write(LIS3MDL_ADDR, LIS3MDL_CTRL_REG2, &data, 1);
    data = 0x00; // modo contínuo
    I2C_Write(LIS3MDL_ADDR, LIS3MDL_CTRL_REG3, &data, 1);
}

void SENSORS_8_to_16bits(uint8_t* data, int16_t* output){
    memset(output, 0, 8);
    output[0] = (int16_t)(data[1] << 8 | data[0]); 
    output[1] = (int16_t)(data[3] << 8 | data[2]);
    output[2] = (int16_t)(data[5] << 8 | data[4]); 
    output[3] = (int16_t)(data[6] << 8 | data[5]);
    output[4] = (int16_t)(data[8] << 8 | data[7]);
}

void SENSORS_Read_u8_bits(Sensors sensor, uint8_t* buf) {
    switch (sensor) {
        case GYROSCOPE:
            I2C_Read(LSM6DSR_ADDR, LSM6DSR_OUTX_L_G, buf, 6);
            break;
        case ACELEROMETER:
            I2C_Read(LSM6DSR_ADDR, LSM6DSR_OUTX_L_XL, buf, 6);
            break;
        case MAGNETOMETER:
            I2C_Read(LSM6DSR_ADDR, LSM6DSR_SENSORHUB1, buf, 6);
            break;
        case TEMPERATURE:
            I2C_Read(LSM6DSR_ADDR, LSM6DSR_OUT_TEMP_L, buf, 2);
            break;
        default:
            break;
    }
}

void SENSORS_Read_16_bits(Sensors sensor, int16_t* buf) {
    uint8_t buf_8[8];
    SENSORS_Read_u8_bits(sensor, buf_8);
    SENSORS_8_to_16bits(buf_8, buf);
}

