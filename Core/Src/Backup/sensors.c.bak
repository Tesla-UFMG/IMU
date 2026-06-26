#include "sensors.h"


void SENSORS_LSM6DSR_Init(void) {
    uint8_t data;

    // Configura o ODR do Acelerômetro
    data = LSM6DSR_CTRL1_XL_ODR; 
    I2C_Write(LSM6DSR_ADDR, LSM6DSR_CTRL1_XL_REG, &data, 1); 

    // Configura o ODR do Giroscópio
    data = LSM6DSR_CTRL2_G_ODR;
    I2C_Write(LSM6DSR_ADDR, LSM6DSR_CTRL2_G_REG, &data, 1); 
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
            I2C_Read(LSM6DSR_ADDR, LSM6DSR_OUTX_L_G_REG, buf, 6);
            break;
        case ACELEROMETER:
            I2C_Read(LSM6DSR_ADDR, LSM6DSR_OUTX_L_XL_REG, buf, 6);
            break;
        case TEMPERATURE:
            I2C_Read(LSM6DSR_ADDR, LSM6DSR_OUT_TEMP_L_REG, buf, 2);
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