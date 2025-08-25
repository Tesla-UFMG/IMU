#ifndef __SENSORS_ODR_H
#define __SENSORS_ODR_H

#ifdef __cplusplus
extern "C" {
#endif

#define LSM6DSR_CTRL1_XL_BYTE(odr, fs, lpf2) ((uint8_t)((odr) | (fs) | (lpf2) | 0x0))
#define LSM6DSR_CTRL2_G_BYTE(odr, fs, fs125, fs4000) ((uint8_t)((odr) | (fs) | (fs125) | (fs4000)))

/* ------------- Acelerômetro ------------- */
enum Acelerometer_ODR_ {
    Acelerometer_ODR_PD       = 0x0 << 4, /* Power-down */
    Acelerometer_ODR_1_6HZ    = 0xB << 4, /* 1.6 Hz (low-power only) */
    Acelerometer_ODR_12_5HZ   = 0x1 << 4, /* 12.5 Hz */
    Acelerometer_ODR_26HZ     = 0x2 << 4, /* 26 Hz */
    Acelerometer_ODR_52HZ     = 0x3 << 4, /* 52 Hz */
    Acelerometer_ODR_104HZ    = 0x4 << 4, /* 104 Hz */
    Acelerometer_ODR_208HZ    = 0x5 << 4, /* 208 Hz */
    Acelerometer_ODR_416HZ    = 0x6 << 4, /* 416 Hz */
    Acelerometer_ODR_833HZ    = 0x7 << 4, /* 833 Hz */
    Acelerometer_ODR_1_66KHZ  = 0x8 << 4, /* 1.66 kHz */
    Acelerometer_ODR_3_33KHZ  = 0x9 << 4, /* 3.33 kHz */
    Acelerometer_ODR_6_66KHZ  = 0xA << 4  /* 6.66 kHz */
};

enum Acelerometer_FS_ {
    Acelerometer_FS_2G   = 0x0 << 2, /* ±2 g  */
    Acelerometer_FS_16G  = 0x1 << 2, /* ±16 g */
    Acelerometer_FS_4G   = 0x2 << 2, /* ±4 g  */
    Acelerometer_FS_8G   = 0x3 << 2  /* ±8 g  */
};

enum Acelerometer_LPF2_ {
    Acelerometer_LPF2_DISABLE = 0 << 1,
    Acelerometer_LPF2_ENABLE  = 1 << 1 // Habilita filtro passa-baixa
};
/* ------------------------------------------ */


/* --------------- Giroscópio --------------- */
enum Gyro_ODR_ {
    Gyro_ODR_PD        = 0x0 << 4, /* Power-down */
    Gyro_ODR_12_5HZ    = 0x1 << 4, /* 12.5 Hz */
    Gyro_ODR_26HZ      = 0x2 << 4, /* 26 Hz */
    Gyro_ODR_52HZ      = 0x3 << 4, /* 52 Hz */
    Gyro_ODR_104HZ     = 0x4 << 4, /* 104 Hz */
    Gyro_ODR_208HZ     = 0x5 << 4, /* 208 Hz */
    Gyro_ODR_416HZ     = 0x6 << 4, /* 416 Hz */
    Gyro_ODR_833HZ     = 0x7 << 4, /* 833 Hz */
    Gyro_ODR_1_66KHZ   = 0x8 << 4, /* 1.66 kHz */
    Gyro_ODR_3_33KHZ   = 0x9 << 4, /* 3.33 kHz */
    Gyro_ODR_6_66KHZ   = 0xA << 4  /* 6.66 kHz */
};

enum Gyro_FS_ {
    Gyro_FS_250DPS   = 0x0 << 2, /* ±250 dps  */
    Gyro_FS_500DPS   = 0x1 << 2, /* ±500 dps  */
    Gyro_FS_1000DPS  = 0x2 << 2, /* ±1000 dps */
    Gyro_FS_2000DPS  = 0x3 << 2  /* ±2000 dps */
};

enum Gyro_FS_Special_ {
    Gyro_FS125_DISABLE = 0 << 1,
    Gyro_FS125_ENABLE  = 1 << 1, /* Quando ativo, FS = ±125 dps (sobrescreve FS[1:0]) */

    Gyro_FS4000_DISABLE = 0 << 0,
    Gyro_FS4000_ENABLE  = 1 << 0  /* Quando ativo, FS = ±4000 dps (sobrescreve todos) */
};
/* ------------------------------------------ */





#ifdef __cplusplus
}
#endif
#endif