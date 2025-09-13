#ifndef __SENSORS_H
#define __SENSORS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "sensors_params.h"

typedef enum {
    ACELEROMETER = 0x103,
    GYROSCOPE = 0x104,
    TEMPERATURE = 0x105
} Sensors;


/* ------------------ LSM6DSR ------------------ */
// Endereço do LSM6DSR
#define LSM6DSR_ADDR        (0x6A << 1) 

// Acelerômetro
#define LSM6DSR_CTRL1_XL_REG     0x10  
#define LSM6DSR_CTRL1_XL_ODR  LSM6DSR_CTRL1_XL_BYTE(Acelerometer_ODR_208HZ, Acelerometer_FS_4G, Acelerometer_LPF2_ENABLE)
#define LSM6DSR_OUTX_L_XL_REG   0x28  // Output

// Giroscópio
#define LSM6DSR_CTRL2_G_REG     0x11 
#define LSM6DSR_CTRL2_G_ODR LSM6DSR_CTRL2_G_BYTE(Gyro_ODR_208HZ, Gyro_FS_2000DPS, Gyro_FS125_DISABLE, Gyro_FS4000_DISABLE)
#define LSM6DSR_OUTX_L_G_REG    0x22  // Output

// Temperatura
#define LSM6DSR_OUT_TEMP_L_REG  0x20   // Output
/* -------------------------------------------- */

// Init Sensors
void SENSORS_LSM6DSR_Init(void);

// Read Sensors
void SENSORS_8_to_16bits(uint8_t* data, int16_t* output);
void SENSORS_Read_u8_bits(Sensors sensor, uint8_t* buf);
void SENSORS_Read_16_bits(Sensors sensor, int16_t* buf);

#ifdef __cplusplus
}
#endif

#endif