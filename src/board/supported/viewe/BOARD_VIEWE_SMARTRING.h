/*
 * SPDX-FileCopyrightText: 2023-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
/**
 * @file   BOARD_VIEWE_SMARTRING.h
 * @brief  Configuration file for Viewe SMARTRING
 * @author Viewe@VIEWESMART
 * @link   https://github.com/VIEWESMART/VIEWE-SMARTRING
 */

#pragma once

#include <driver/gpio.h>
#include "esp_lcd_panel_io.h"

// *INDENT-OFF*

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// Please update the following macros to configure general panel /////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Board name
 */
#define ESP_PANEL_BOARD_NAME                "Viewe:SMARTRING"

/**
 * @brief Panel resolution configuration in pixels
 */
#define ESP_PANEL_BOARD_WIDTH               (472)   // Panel width (horizontal, in pixels)
#define ESP_PANEL_BOARD_HEIGHT              (466)   // Panel height (vertical, in pixels)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// Please update the following macros to configure the LCD panel /////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief LCD panel configuration flag (0/1)
 *
 * Set to `1` to enable LCD panel support, `0` to disable
 */
#define ESP_PANEL_BOARD_USE_LCD             (1)

#if ESP_PANEL_BOARD_USE_LCD
/**
 * @brief LCD controller selection
 */
#define ESP_PANEL_BOARD_LCD_CONTROLLER      SH8601

/**
 * @brief LCD bus type selection
 *
 * Supported bus types:
 * - `ESP_PANEL_BUS_TYPE_SPI`
 * - `ESP_PANEL_BUS_TYPE_QSPI`
 * - `ESP_PANEL_BUS_TYPE_RGB` (ESP32-S3 only)
 * - `ESP_PANEL_BUS_TYPE_MIPI_DSI` (ESP32-P4 only)
 */
#define ESP_PANEL_BOARD_LCD_BUS_TYPE        (ESP_PANEL_BUS_TYPE_QSPI)

#if (ESP_PANEL_BOARD_LCD_BUS_TYPE == ESP_PANEL_BUS_TYPE_SPI) || \
    (ESP_PANEL_BOARD_LCD_BUS_TYPE == ESP_PANEL_BUS_TYPE_QSPI)
/**
 * If set to 1, the bus will skip to initialize the corresponding host. Users need to initialize the host in advance.
 *
 * For drivers which created by this library, even if they use the same host, the host will be initialized only once.
 * So it is not necessary to set the macro to `1`. For other drivers (like `Wire`), please set the macro to `1`
 * ensure that the host is initialized only once.
 */
#define ESP_PANEL_BOARD_LCD_BUS_SKIP_INIT_HOST      (0)     // 0/1. Typically set to 0
#endif

/**
 * @brief LCD bus parameters configuration
 *
 * Configure parameters based on the selected bus type. Parameters for other bus types will be ignored.
 * For detailed parameter explanations, see:
 * https://docs.espressif.com/projects/esp-idf/en/v5.3.1/esp32s3/api-reference/peripherals/lcd/index.html
 * https://docs.espressif.com/projects/esp-iot-solution/en/latest/display/lcd/index.html
 */
#if ESP_PANEL_BOARD_LCD_BUS_TYPE == ESP_PANEL_BUS_TYPE_QSPI

/**
 * @brief QSPI bus
 */
/* For general */
#define ESP_PANEL_BOARD_LCD_QSPI_HOST_ID        (1)     // Typically set to 1
#if !ESP_PANEL_BOARD_LCD_BUS_SKIP_INIT_HOST
/* For host */
#define ESP_PANEL_BOARD_LCD_QSPI_IO_SCK         (13)
#define ESP_PANEL_BOARD_LCD_QSPI_IO_DATA0       (12)
#define ESP_PANEL_BOARD_LCD_QSPI_IO_DATA1       (8)
#define ESP_PANEL_BOARD_LCD_QSPI_IO_DATA2       (14)
#define ESP_PANEL_BOARD_LCD_QSPI_IO_DATA3       (9)
#endif // ESP_PANEL_BOARD_LCD_BUS_SKIP_INIT_HOST
/* For panel */
#define ESP_PANEL_BOARD_LCD_QSPI_IO_CS          (7)     // -1 if not used
#define ESP_PANEL_BOARD_LCD_QSPI_MODE           (0)     // 0-3, typically set to 0
#define ESP_PANEL_BOARD_LCD_QSPI_CLK_HZ         (40 * 1000 * 1000)
                                                        // Should be an integer divisor of 80M, typically set to 40M
#define ESP_PANEL_BOARD_LCD_QSPI_CMD_BITS       (32)    // Typically set to 32
#define ESP_PANEL_BOARD_LCD_QSPI_PARAM_BITS     (8)     // Typically set to 8

#endif // ESP_PANEL_BOARD_LCD_BUS_TYPE

/**
 * @brief LCD vendor initialization commands
 *
 * Vendor specific initialization can be different between manufacturers, should consult the LCD supplier for
 * initialization sequence code. Please uncomment and change the following macro definitions. Otherwise, the LCD driver
 * will use the default initialization sequence code.
 *
 * The initialization sequence can be specified in two formats:
 * 1. Raw format:
 *    {command, (uint8_t []){data0, data1, ...}, data_size, delay_ms}
 * 2. Helper macros:
 *    - ESP_PANEL_LCD_CMD_WITH_8BIT_PARAM(delay_ms, command, {data0, data1, ...})
 *    - ESP_PANEL_LCD_CMD_WITH_NONE_PARAM(delay_ms, command)
 */
#define ESP_PANEL_BOARD_LCD_VENDOR_INIT_CMD() \
{                                                                          \
    {0xFE, (uint8_t []){0x00}, 0, 0},                                      \
    {0xC4, (uint8_t []){0x80}, 1, 0},                                      \
    {0x3A, (uint8_t []){0x55}, 1, 0},                                      \
    {0x35, (uint8_t []){0x00}, 0, 10},                                     \
    {0x53, (uint8_t []){0x20}, 1, 10},                                     \
    {0x51, (uint8_t []){0xFF}, 1, 10},                                     \
    {0x63, (uint8_t []){0xFF}, 1, 10},                                     \
    {0x2A, (uint8_t []){0x00,0x06,0x01,0xDD}, 4, 0},                       \
    {0x2B, (uint8_t []){0x00,0x00,0x01,0xD1}, 4, 0},                       \
    {0x11, (uint8_t []){0x00}, 0, 60},                                     \
    {0x29, (uint8_t []){0x00}, 0, 0},                                      \
}
/**
 * @brief LCD color configuration
 */
#define ESP_PANEL_BOARD_LCD_COLOR_BITS          (ESP_PANEL_LCD_COLOR_BITS_RGB565)
                                                        // ESP_PANEL_LCD_COLOR_BITS_RGB565/RGB666/RGB888
#define ESP_PANEL_BOARD_LCD_COLOR_BGR_ORDER     (0)     // 0: RGB, 1: BGR
#define ESP_PANEL_BOARD_LCD_COLOR_INEVRT_BIT    (0)     // 0/1

/**
 * @brief LCD transformation configuration
 */
#define ESP_PANEL_BOARD_LCD_SWAP_XY             (0)     // 0/1
#define ESP_PANEL_BOARD_LCD_MIRROR_X            (0)     // 0/1
#define ESP_PANEL_BOARD_LCD_MIRROR_Y            (0)     // 0/1
#define ESP_PANEL_BOARD_LCD_GAP_X               (0)     // [0, ESP_PANEL_BOARD_WIDTH]
#define ESP_PANEL_BOARD_LCD_GAP_Y               (0)     // [0, ESP_PANEL_BOARD_HEIGHT]

/**
 * @brief LCD reset pin configuration
 */
#define ESP_PANEL_BOARD_LCD_RST_IO              (11)    // Reset pin, -1 if not used
#define ESP_PANEL_BOARD_LCD_RST_LEVEL           (0)     // Reset active level, 0: low, 1: high

#endif // ESP_PANEL_BOARD_USE_LCD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// Please update the following macros to configure the touch panel ///////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Touch panel configuration flag (0/1)
 *
 * Set to `1` to enable touch panel support, `0` to disable
 */
#define ESP_PANEL_BOARD_USE_TOUCH               (1)

#if ESP_PANEL_BOARD_USE_TOUCH
/**
 * @brief Touch controller selection
 */
#define ESP_PANEL_BOARD_TOUCH_CONTROLLER        CST820

/**
 * @brief Touch bus type selection
 * - `ESP_PANEL_BUS_TYPE_SPI`
 */
#define ESP_PANEL_BOARD_TOUCH_BUS_TYPE          (ESP_PANEL_BUS_TYPE_I2C)

#if (ESP_PANEL_BOARD_TOUCH_BUS_TYPE == ESP_PANEL_BUS_TYPE_I2C) || \
    (ESP_PANEL_BOARD_TOUCH_BUS_TYPE == ESP_PANEL_BUS_TYPE_SPI)
/**
 * If set to 1, the bus will skip to initialize the corresponding host. Users need to initialize the host in advance.
 *
 * For drivers which created by this library, even if they use the same host, the host will be initialized only once.
 * So it is not necessary to set the macro to `1`. For other drivers (like `Wire`), please set the macro to `1`
 * ensure that the host is initialized only once.
 */
#define ESP_PANEL_BOARD_TOUCH_BUS_SKIP_INIT_HOST        (0)     // 0/1. Typically set to 0
#endif

/**
 * @brief Touch bus parameters configuration
 */
#if ESP_PANEL_BOARD_TOUCH_BUS_TYPE == ESP_PANEL_BUS_TYPE_I2C

    /**
     * @brief I2C bus
     */
    /* For general */
    #define ESP_PANEL_BOARD_TOUCH_I2C_HOST_ID           (1)     // Typically set to 0
#if !ESP_PANEL_BOARD_TOUCH_BUS_SKIP_INIT_HOST
    /* For host */
    #define ESP_PANEL_BOARD_TOUCH_I2C_CLK_HZ            (400 * 1000)
                                                                // Typically set to 400K
    #define ESP_PANEL_BOARD_TOUCH_I2C_SCL_PULLUP        (1)     // 0/1. Typically set to 1
    #define ESP_PANEL_BOARD_TOUCH_I2C_SDA_PULLUP        (1)     // 0/1. Typically set to 1
    #define ESP_PANEL_BOARD_TOUCH_I2C_IO_SCL            (45)
    #define ESP_PANEL_BOARD_TOUCH_I2C_IO_SDA            (41)
#endif
    /* For panel */
    #define ESP_PANEL_BOARD_TOUCH_I2C_ADDRESS           (0)     // Typically set to 0 to use the default address.
                                                                // - For touchs with only one address, set to 0
                                                                // - For touchs with multiple addresses, set to 0 or
                                                                //   the address. Like GT911, there are two addresses:
                                                                //   0x5D(default) and 0x14

#endif // ESP_PANEL_BOARD_TOUCH_BUS_TYPE

/**
 * @brief Touch panel transformation flags
 */
#define ESP_PANEL_BOARD_TOUCH_SWAP_XY           (0)     // 0/1
#define ESP_PANEL_BOARD_TOUCH_MIRROR_X          (0)     // 0/1
#define ESP_PANEL_BOARD_TOUCH_MIRROR_Y          (0)     // 0/1

/**
 * @brief Touch panel control pins
 */
#define ESP_PANEL_BOARD_TOUCH_RST_IO            (46)    // Reset pin, -1 if not used
#define ESP_PANEL_BOARD_TOUCH_RST_LEVEL         (0)     // Reset active level, 0: low, 1: high
#define ESP_PANEL_BOARD_TOUCH_INT_IO            (42)    // Interrupt pin, -1 if not used
#define ESP_PANEL_BOARD_TOUCH_INT_LEVEL         (0)     // Interrupt active level, 0: low, 1: high

#endif // ESP_PANEL_BOARD_USE_TOUCH

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// Please update the following macros to configure the backlight ////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Backlight configuration flag (0/1)
 *
 * Set to `1` to enable backlight support, `0` to disable
 */
#define ESP_PANEL_BOARD_USE_BACKLIGHT           (1)

#if ESP_PANEL_BOARD_USE_BACKLIGHT
/**
 * @brief Backlight control type selection
 */
#define ESP_PANEL_BOARD_BACKLIGHT_TYPE          (ESP_PANEL_BACKLIGHT_TYPE_CUSTOM)

#if (ESP_PANEL_BOARD_BACKLIGHT_TYPE == ESP_PANEL_BACKLIGHT_TYPE_SWITCH_GPIO) || \
    (ESP_PANEL_BOARD_BACKLIGHT_TYPE == ESP_PANEL_BACKLIGHT_TYPE_SWITCH_EXPANDER) || \
    (ESP_PANEL_BOARD_BACKLIGHT_TYPE == ESP_PANEL_BACKLIGHT_TYPE_PWM_LEDC)

    /**
     * @brief Backlight control pin configuration
     */
    #define ESP_PANEL_BOARD_BACKLIGHT_IO        (40)    // Output GPIO pin number
    #define ESP_PANEL_BOARD_BACKLIGHT_ON_LEVEL  (1)     // Active level, 0: low, 1: high

#endif // ESP_PANEL_BOARD_BACKLIGHT_TYPE

#if (ESP_PANEL_BOARD_BACKLIGHT_TYPE == ESP_PANEL_BACKLIGHT_TYPE_CUSTOM)

#define ESP_PANEL_BOARD_BACKLIGHT_IO        (40)

// SH8601 用 tx_param 相当のヘルパー
static inline esp_err_t viewe_sh8601_tx_param(esp_lcd_panel_io_handle_t io,
                                              int lcd_cmd,
                                              const void *param,
                                              size_t param_size)
{
    // QSPI のときは SH8601 ドライバと同じように 32bit コマンドに変換
#if (ESP_PANEL_BOARD_LCD_BUS_TYPE == ESP_PANEL_BUS_TYPE_QSPI)
    lcd_cmd &= 0xff;
    lcd_cmd <<= 8;
    lcd_cmd |= (0x02U << 24);   // LCD_OPCODE_WRITE_CMD と同じ値
#endif
    return esp_lcd_panel_io_tx_param(io, lcd_cmd, param, param_size);
}

#define ESP_PANEL_BOARD_BACKLIGHT_CUSTOM_FUNCTION(percent, user_data)              \
{                                                                                  \
    auto board = static_cast<Board *>(user_data);                                  \
    if (!board) {                                                                  \
        ESP_UTILS_LOGE("BL: board is null");                                     \
        return false;                                                              \
    }                                                                              \
                                                                                   \
    auto lcd = board->getLCD();                                                    \
    if (!lcd) {                                                                    \
        ESP_UTILS_LOGE("BL: lcd is null");                                       \
        return false;                                                              \
    }                                                                              \
                                                                                   \
    auto bus = lcd->getBus();                                                      \
    if (!bus) {                                                                    \
        ESP_UTILS_LOGE("BL: bus is null");                                       \
        return false;                                                              \
    }                                                                              \
                                                                                   \
    esp_lcd_panel_io_handle_t io = bus->getControlPanelHandle();                   \
    if (!io) {                                                                     \
        ESP_UTILS_LOGE("BL: io handle is null");                                 \
        return false;                                                              \
    }                                                                              \
                                                                                   \
    /* 0〜100% を 0〜255 に変換 */                                                 \
    uint8_t value = (uint8_t)((percent * 255) / 100);                              \
    ESP_UTILS_LOGD("BL: set brightness percent=%d, value=0x%02X",                \
                   (int)percent, (int)value);                                      \
                                                                                   \
    /* （必要なら）GPIO 40 で電源 ON/OFF */                                        \
    do {                                                                           \
        int bl_io = ESP_PANEL_BOARD_BACKLIGHT_IO;                                  \
        if (bl_io >= 0) {                                                          \
            gpio_config_t io_conf = {};                                            \
            io_conf.pin_bit_mask = (1ULL << bl_io);                                \
            io_conf.mode = GPIO_MODE_OUTPUT;                                       \
            io_conf.pull_up_en = GPIO_PULLUP_DISABLE;                              \
            io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;                          \
            io_conf.intr_type = GPIO_INTR_DISABLE;                                 \
            gpio_config(&io_conf);                                                 \
            gpio_set_level((gpio_num_t)bl_io, (percent > 0) ? 1 : 0);              \
        }                                                                          \
    } while (0);                                                                   \
                                                                                   \
    esp_err_t err;                                                                 \
                                                                                   \
    /* ★ SH8601 の tx_param と同じルートで FE/C4/51 を送る */                     \
    uint8_t p;                                                                     \
                                                                                   \
    p = 0x00;                                                                      \
    err = viewe_sh8601_tx_param(io, 0xFE, &p, 1);                                  \
    if (err != ESP_OK) {                                                           \
        ESP_UTILS_LOGE("BL: tx_param(0xFE) failed: 0x%x", (int)err);             \
        return false;                                                              \
    }                                                                              \
                                                                                   \
    p = 0x80;                                                                      \
    err = viewe_sh8601_tx_param(io, 0xC4, &p, 1);                                  \
    if (err != ESP_OK) {                                                           \
        ESP_UTILS_LOGE("BL: tx_param(0xC4) failed: 0x%x", (int)err);             \
        return false;                                                              \
    }                                                                              \
                                                                                   \
    err = viewe_sh8601_tx_param(io, 0x51, &value, 1);                              \
    if (err != ESP_OK) {                                                           \
        ESP_UTILS_LOGE("BL: tx_param(0x51) failed: 0x%x", (int)err);             \
        return false;                                                              \
    }                                                                              \
                                                                                   \
    return true;                                                                   \
}

#endif // ESP_PANEL_BOARD_BACKLIGHT_TYPE


/**
 * @brief Backlight idle state configuration (0/1)
 *
 * Set to 1 if want to turn off the backlight after initializing. Otherwise, the backlight will be on.
 */
#define ESP_PANEL_BOARD_BACKLIGHT_IDLE_OFF      (0)

#endif // ESP_PANEL_BOARD_USE_BACKLIGHT

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// Please update the following macros to configure the IO expander //////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief IO expander configuration flag (0/1)
 *
 * Set to `1` to enable IO expander support, `0` to disable
 */
#define ESP_PANEL_BOARD_USE_EXPANDER            (0)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////// Please utilize the following macros to execute any additional code if required /////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// File Version ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Do not change the following versions. These version numbers are used to check compatibility between this
 * configuration file and the library. Rules for version numbers:
 * 1. Major version mismatch: Configurations are incompatible, must use library version
 * 2. Minor version mismatch: May be missing new configurations, recommended to update
 * 3. Patch version mismatch: No impact on functionality
 */
#define ESP_PANEL_BOARD_CUSTOM_FILE_VERSION_MAJOR 1
#define ESP_PANEL_BOARD_CUSTOM_FILE_VERSION_MINOR 0
#define ESP_PANEL_BOARD_CUSTOM_FILE_VERSION_PATCH 0

// *INDENT-ON*
