#ifndef __SENSORS_CONFIG_H
#define __SENSORS_CONFIG_H
#ifdef __cplusplus
extern "C" {
#endif

// includes -------------------------------------------------------------------
#include "stm32u5xx.h"
#include "main.h"

// defines ----------------------------------------------
#define LSM6DSR_ADDR        (0x6A << 1)  

#define LSM6DSR_CTRL1_XL    0x10 // Endereço registrador do acelerômetro
#define LSM6DSR_CTRL1_XL_ODR 0x5C //  ODR=208 Hz, escala 8g

#define LSM6DSR_CTRL2_G     0x11 // Endereço registrador do giroscópio
#define LSM6DSR_CTRL2_G_ODR 0x5C // ODR=208 Hz, +-2000 dps



#define LSM6DSR_SLV0_ADDR   0x15
#define LSM6DSR_SLV0_SUBADD 0x16
#define LSM6DSR_SLV0_CONFIG 0x14

#define LIS3MDL_ADDR        (0x1C << 1)
#define LIS3MDL_CTRL_REG1   0x20
#define LIS3MDL_CTRL_REG2   0x21
#define LIS3MDL_CTRL_REG3   0x22

#define LSM6DSR_OUTX_L_G    0x22
#define LSM6DSR_OUTX_L_XL   0x28
#define LSM6DSR_SENSORHUB1  0x02 

extern I2C_HandleTypeDef hi2c2;

// Lê e coloca valores do I2C
HAL_StatusTypeDef SENSORS_I2C_Read(uint16_t DevAddress, uint8_t Reg, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef SENSORS_I2C_Write(uint16_t DevAddress, uint8_t Reg, uint8_t *pData, uint16_t Size);

// Inicia os sensores
void SENSORS_LSM6DSR_Init(void);
void SENSORS_Configure_SensorHub_LIS3MDL(void);
void SENSORS_LIS3MDL_Init(void);

// Lê os sensores
void SENSORS_8_to_16bits(uint8_t* data, int16_t* output);

void SENSORS_Read_Accelerometer_8(uint8_t* buf);
void SENSORS_Read_Accelerometer_16(int16_t* buf);

void SENSORS_Read_Gyroscope_8(uint8_t* buf);
void SENSORS_Read_Gyroscope_16(int16_t* buf);

void SENSORS_Read_Magnetometer_8(uint8_t* buf);
void SENSORS_Read_Magnetometer_16(int16_t* buf);


void SENSORS_Print(int16_t* data);

#ifdef __cplusplus
}
#endif
#endif