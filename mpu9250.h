/*
 * mpu9250.h
 *
 *  Created on: 28-Nov-2025
 *      Author: Anagha N C
 */

#ifndef MAIN_MPU9250_H_
#define MAIN_MPU9250_H_





#endif /* MAIN_MPU9250_H_ */

#ifndef MPU9250_H
#define MPU9250_H

#include <stdint.h>
#include "esp_err.h"

// configure these if you want different I2C pins or address
#define MPU9250_I2C_PORT I2C_NUM_0
#define MPU9250_SDA_GPIO 21
#define MPU9250_SCL_GPIO 22
#define MPU9250_I2C_FREQ_HZ 400000
#define MPU9250_ADDR     0x68      // set to 0x69 if AD0 high

typedef struct {
    float ax; // g
    float ay;
    float az;
    float gx; // dps
    float gy;
    float gz;
} mpu9250_data_t;

esp_err_t mpu9250_init(void);
esp_err_t mpu9250_read_accel_gyro(mpu9250_data_t *out);
void mpu9250_deinit(void);

#endif // MPU9250_H
