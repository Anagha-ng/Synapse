/*
 * mpu9250.c
 *
 *  Created on: 28-Nov-2025
 *      Author: Anagha N C
 */

#include "mpu9250.h"
#include "driver/i2c.h"
#include "esp_log.h"
#include <string.h>

static const char *TAG = "MPU9250";

// Registers (MPU9250 / MPU6500 core)
#define REG_PWR_MGMT_1    0x6B
#define REG_SMPLRT_DIV    0x19
#define REG_CONFIG        0x1A
#define REG_GYRO_CONFIG   0x1B
#define REG_ACCEL_CONFIG  0x1C
#define REG_ACCEL_XOUT_H  0x3B
#define REG_WHO_AM_I      0x75

// Sensitivity scale factors for default ranges (we set ±2g, ±250dps)
#define ACCEL_SENS_2G 16384.0f   // LSB/g
#define GYRO_SENS_250DPS 131.0f  // LSB/(°/s)

static bool i2c_installed = false;

// low-level helpers
static esp_err_t i2c_write_reg(uint8_t reg, uint8_t val)
{
    return i2c_master_write_to_device(MPU9250_I2C_PORT, MPU9250_ADDR, (const uint8_t[]){reg, val}, 2, pdMS_TO_TICKS(1000));
}

static esp_err_t i2c_read_regs(uint8_t reg, uint8_t *buf, size_t len)
{
    return i2c_master_write_read_device(MPU9250_I2C_PORT, MPU9250_ADDR, &reg, 1, buf, len, pdMS_TO_TICKS(1000));
}

// init i2c peripheral and sensor
esp_err_t mpu9250_init(void)
{
    esp_err_t ret;

    if (!i2c_installed) {
        i2c_config_t conf = {
            .mode = I2C_MODE_MASTER,
            .sda_io_num = MPU9250_SDA_GPIO,
            .scl_io_num = MPU9250_SCL_GPIO,
            .sda_pullup_en = GPIO_PULLUP_ENABLE,
            .scl_pullup_en = GPIO_PULLUP_ENABLE,
            .master.clk_speed = MPU9250_I2C_FREQ_HZ
        };
        ret = i2c_param_config(MPU9250_I2C_PORT, &conf);
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "i2c_param_config failed: %s", esp_err_to_name(ret));
            return ret;
        }
        ret = i2c_driver_install(MPU9250_I2C_PORT, I2C_MODE_MASTER, 0, 0, 0);
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "i2c_driver_install failed: %s", esp_err_to_name(ret));
            return ret;
        }
        i2c_installed = true;
    }

    // check WHO_AM_I
    uint8_t who = 0;
    ret = i2c_read_regs(REG_WHO_AM_I, &who, 1);
    if (ret != ESP_OK) {
        ESP_LOGW(TAG, "WHO_AM_I read failed: %s", esp_err_to_name(ret));
    } else {
        ESP_LOGI(TAG, "WHO_AM_I = 0x%02x", who);
    }

    // wake up device
    ret = i2c_write_reg(REG_PWR_MGMT_1, 0x01); // set clock source to PLL, exit sleep
    if (ret != ESP_OK) return ret;
    vTaskDelay(pdMS_TO_TICKS(100));

    // sample rate divider (SMPLRT_DIV): default
    i2c_write_reg(REG_SMPLRT_DIV, 0x00);

    // CONFIG: DLPF (set to 0x03 for ~44Hz bandwidth typical)
    i2c_write_reg(REG_CONFIG, 0x03);

    // GYRO_CONFIG: set ±250 dps (0<<3)
    i2c_write_reg(REG_GYRO_CONFIG, 0x00);

    // ACCEL_CONFIG: set ±2g (0<<3)
    i2c_write_reg(REG_ACCEL_CONFIG, 0x00);

    vTaskDelay(pdMS_TO_TICKS(50));
    ESP_LOGI(TAG, "MPU9250 init done");
    return ESP_OK;
}

esp_err_t mpu9250_read_accel_gyro(mpu9250_data_t *out)
{
    if (!out) return ESP_ERR_INVALID_ARG;
    uint8_t buf[14];
    esp_err_t r = i2c_read_regs(REG_ACCEL_XOUT_H, buf, sizeof(buf));
    if (r != ESP_OK) return r;

    // big-endian 16-bit signed values
    int16_t ax = (int16_t)((buf[0] << 8) | buf[1]);
    int16_t ay = (int16_t)((buf[2] << 8) | buf[3]);
    int16_t az = (int16_t)((buf[4] << 8) | buf[5]);
    // temp in buf[6..7] ignored
    int16_t gx = (int16_t)((buf[8] << 8) | buf[9]);
    int16_t gy = (int16_t)((buf[10] << 8) | buf[11]);
    int16_t gz = (int16_t)((buf[12] << 8) | buf[13]);

    out->ax = (float)ax / ACCEL_SENS_2G;
    out->ay = (float)ay / ACCEL_SENS_2G;
    out->az = (float)az / ACCEL_SENS_2G;

    out->gx = (float)gx / GYRO_SENS_250DPS;
    out->gy = (float)gy / GYRO_SENS_250DPS;
    out->gz = (float)gz / GYRO_SENS_250DPS;

    return ESP_OK;
}

void mpu9250_deinit(void)
{
    if (i2c_installed) {
        i2c_driver_delete(MPU9250_I2C_PORT);
        i2c_installed = false;
    }
}



