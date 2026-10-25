/*
 * This file is part of Betaflight.
 *
 * Betaflight is free software. You can redistribute this software
 * and/or modify this software under the terms of the GNU General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later
 * version.
 *
 * Betaflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define FC_TARGET_MCU        RP2350B
#define BOARD_NAME           OPENFC_LITE_RP2350B
#define MANUFACTURER_ID      OPDR

// OpenFC-Lite rev3.3: 30.5x30.5 mm mounting, RP2354B (QFN-80), 3S-8S
// https://github.com/OpenDrone-hw/OpenFC-Lite

// UART0: digital VTX connector (U8) and TX1/RX1 pads
#define UART0_TX_PIN         PA0
#define UART0_RX_PIN         PA1

// PIO UART0: TX3/RX3 pads
#define PIOUART0_TX_PIN      PA2
#define PIOUART0_RX_PIN      PA3

// UART1: TX2/RX2 pads, external serial RX
#define UART1_TX_PIN         PA22
#define UART1_RX_PIN         PA21
#define DEFAULT_RX_FEATURE   FEATURE_RX_SERIAL
#define SERIALRX_PROVIDER    SERIALRX_CRSF
#define SERIALRX_UART        SERIAL_PORT_UART1

// PIO UART1: TX4/RX4 pads
#define PIOUART1_TX_PIN      PA26
#define PIOUART1_RX_PIN      PA27

// I2C0 pads
#define I2C0_SDA_PIN         PA16
#define I2C0_SCL_PIN         PA17

// Analog OSD (framebuffer OSD, PIO2)
#define ENABLE_FB_OSD        1
#define DEFAULT_FEATURES     (FEATURE_OSD | FEATURE_ESC_SENSOR)
#define DEFAULT_OSD_DISPLAYPORT_DEVICE OSD_DISPLAYPORT_DEVICE_FBOSD
#define DEFAULT_VIDEO_SYSTEM VIDEO_SYSTEM_AUTO // digital VTX users set vcd_video_system = HD
#define OSD_W_PIN            PA4
#define OSD_EN_PIN           PA5
#define OSD_SYNC_PIN         PA6

// Beeper pad (N-MOS low-side)
#define USE_BEEPER
#define BEEPER_PIN           PA7

// 10V VTX/cam rail enable (U6 EN), active high. Inverted so pinioInit drives
// it high at boot.
#define PINIO1_PIN           PA11
#define PINIO1_CONFIG        (PINIO_CONFIG_MODE_OUT_PP | PINIO_CONFIG_OUT_INVERTED)

// Status LED
#define LED0_PIN             PA12

// Gyro+acc on SPI0: BMI270 fitted; the footprint also takes ICM-426xx/456xx
#define USE_GYRO
#define USE_ACC
#define USE_ACCGYRO_BMI270
#define USE_ACCGYRO_LSM6DSV16X
#define USE_GYRO_SPI_ICM42688P
#define USE_ACC_SPI_ICM42688P
#define USE_ACCGYRO_ICM45686
#define USE_GYRO_CLKIN
#define SPI0_SCK_PIN         PA18
#define SPI0_SDO_PIN         PA19
#define SPI0_SDI_PIN         PA20
#define GYRO_1_CS_PIN        PA14
#define GYRO_1_EXTI_PIN      PA13
#define GYRO_1_CLKIN_PIN     PA15 // used by ICM parts only
#define GYRO_1_SPI_INSTANCE  SPI0

// BMI270 sits rotated 90 deg vs ICM parts on the shared footprint (#15484).
#define ENABLE_BMI270_ALIGN_AS_ICM 1

// LED strip pad. Its WS2812 program goes on PIO1 (with the PIO UARTs): the
// default PIO2 is shared with the FB OSD, whose 31-instruction program then
// no longer fits and the OSD stays blank.
#define LED_STRIP_PIN        PA23
#define PIO_LEDSTRIP_INDEX   1
#define LED_STRIP_INVERTED   // pad driven by N-FET Q2 with 2.4k to 5V: inverts

// Motors (PIO0 DShot), silk M1-M4 = GPIO31..28
#define MOTOR1_PIN           PA31
#define MOTOR2_PIN           PA30
#define MOTOR3_PIN           PA29
#define MOTOR4_PIN           PA28

// Bidirectional DShot and ESC serial telemetry on by default: the ESC plug's
// telemetry pin is PIO UART1 RX (GPIO27).
#define DEFAULT_DSHOT_TELEMETRY DSHOT_TELEMETRY_ON
#define ESC_SENSOR_UART      SERIAL_PORT_PIOUART1

// Blackbox: microSD on SPI1
#define USE_SDCARD
#define USE_SDCARD_SPI
#define SPI1_SCK_PIN         PA42
#define SPI1_SDO_PIN         PA43
#define SPI1_SDI_PIN         PA44
#define SDCARD_SPI_CS_PIN    PA46
#define SDCARD_SPI_INSTANCE  SPI1
#define DEFAULT_BLACKBOX_DEVICE  BLACKBOX_DEVICE_SDCARD

// ADC (each input via 1k + 100nF RC)
#define USE_ADC
#define ADC_CURR_PIN         PA40
#define ADC_VBAT_PIN         PA41
#define ADC_RSSI_PIN         PA45
#define ADC_EXTERNAL1_PIN    PA47
#define DEFAULT_VOLTAGE_METER_SOURCE  VOLTAGE_METER_ADC
#define DEFAULT_VOLTAGE_METER_SCALE   110 // 100k:10k divider
#define DEFAULT_CURRENT_METER_SOURCE  CURRENT_METER_ADC
#define DEFAULT_CURRENT_METER_SCALE   100  // mV per 10 A, OpenESC-30x30: INA186A3 100 V/V on 0.1 mOhm = 10 mV/A
