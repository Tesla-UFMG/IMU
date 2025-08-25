#ifndef __SENSORS_H
#define __SENSORS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "sensors_odr.h"

typedef enum {
    ACELEROMETER = 0x103,
    GYROSCOPE = 0x104,
    MAGNETOMETER = 0x105,
    TEMPERATURE = 0x106
} Sensors;


/* ------------------ LSM6DSR ------------------ */
// Endereço do LSM6DSR
#define LSM6DSR_ADDR        (0x6A << 1) 

// Acelerômetro
#define LSM6DSR_CTRL1_XL     0x10  
#define LSM6DSR_CTRL1_XL_ODR  LSM6DSR_CTRL1_XL_BYTE(Acelerometer_ODR_208HZ, Acelerometer_FS_4G, Acelerometer_LPF2_ENABLE)
#define LSM6DSR_OUTX_L_XL   0x28  // Output

// Giroscópio
#define LSM6DSR_CTRL2_G     0x11 
#define LSM6DSR_CTRL2_G_ODR SM6DSR_CTRL2_G_BYTE(Gyro_ODR_208HZ, Gyro_FS_2000DPS, Gyro_FS125_DISABLE, Gyro_FS4000_DISABLE)
#define LSM6DSR_OUTX_L_G    0x22  // Output

// Temperatura
#define LSM6DSR_OUT_TEMP_L  0x20   // Output
/* -------------------------------------------- */


/* ------------------ LIS2MDL ------------------ */
// Enderelo do LIS2MDL
#define LIS3MDL_ADDR        (0x1C << 1)

// Registradores de range do LIS2MDL
#define LIS3MDL_CTRL_REG1   0x20
#define LIS3MDL_CTRL_REG2   0x21
#define LIS3MDL_CTRL_REG3   0x22

#define LSM6DSR_SLV0_ADDR   0x15
#define LSM6DSR_SLV0_SUBADD 0x16
#define LSM6DSR_SLV0_CONFIG 0x14

#define LSM6DSR_SENSORHUB1  0x02 
/* -------------------------------------------------- */



// Init Sensors
void SENSORS_LSM6DSR_Init(void);
void SENSORS_Configure_SensorHub_LIS3MDL(void);
void SENSORS_LIS3MDL_Init(void);

// Read Sensors
void SENSORS_8_to_16bits(uint8_t* data, int16_t* output);
void SENSORS_Read_u8_bits(Sensors sensor, uint8_t* buf);
void SENSORS_Read_16_bits(Sensors sensor, int16_t* buf);

#ifdef __cplusplus
}
#endif
#endif