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
#define LSM6DSR_CTRL1_XL    0x10 // REGISTRADOR REFERENTE À VELOCIDADE DO ACELERÔMETRO
#define LSM6DSR_CTRL2_G     0x11 // REGISTRADOR REFERENTE À VELOCIDADE DO GYROSCÓPIO

#define LSM6DSR_SLV0_ADDR   0x15
#define LSM6DSR_SLV0_SUBADD 0x16
#define LSM6DSR_SLV0_CONFIG 0x14

#define LIS3MDL_ADDR        (0x1C << 1)
#define LIS3MDL_CTRL_REG1   0x20
#define LIS3MDL_CTRL_REG2   0x21
#define LIS3MDL_CTRL_REG3   0x22

#define LSM6DSR_OUTX_L_G    0x22
#define LSM6DSR_OUTX_L_XL   0x28
#define LSM6DSR_SENSORHUB1  0x02  // primeiro byte do sensor hub

extern I2C_HandleTypeDef hi2c2;

HAL_StatusTypeDef I2C_Read(uint16_t DevAddress, uint8_t Reg, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef I2C_Write(uint16_t DevAddress, uint8_t Reg, uint8_t *pData, uint16_t Size);
void LSM6DSR_Init(void);
void Configure_SensorHub_LIS3MDL(void);
void LIS3MDL_Init(void);
void Read_Accelerometer(int16_t accelerometer[3]);
void Read_Gyroscope(int16_t gyroscope[3]);
void Read_Magnetometer(int16_t magnetometer[3]);

#ifdef __cplusplus
}
#endif
#endif