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
#define BOARD_NAME           OPENFC_LITE_REV2_RP2350B
#define MANUFACTURER_ID      OPFC

// OpenFC-Lite Rev 2: 30.5x30.5 mm mounting, RP2354B (QFN-80), 3S-6S
// https://github.com/incutec-hw/OpenFC-Lite
// Pin map extracted from hardware/OpenFC.kicad_sch netlist (Rev 2)

// Rev 2 erratum: GPIO0-3, GPIO28, GPIO31 are shorted to GND, killing the
// stock UART0 (VTX connector), PIOUART0 (GPS pads) and M1/M4 pads.
// Rev 2 rework mapping:
//   receiver     -> UART0 remapped to the I2C pads (rx TX -> SCL, rx RX -> SDA)
//   air unit     -> PIOUART1 on TP1/RP1 pads (leave ESC TLM wire unconnected)
//   motor 1      -> RX1 pad (PA21), motor 4 -> TX1 pad (PA22)
//   UART1 + I2C0 -> sacrificed (pins reused above)
#define UART0_TX_PIN         PA16 // SDA pad, to receiver RX
#define UART0_RX_PIN         PA17 // SCL pad, from receiver TX

// Analog OSD (framebuffer OSD, PIO2)
#define ENABLE_FB_OSD        1
#define DEFAULT_FEATURES     (FEATURE_OSD)
#define DEFAULT_OSD_DISPLAYPORT_DEVICE OSD_DISPLAYPORT_DEVICE_FBOSD
#define DEFAULT_VIDEO_SYSTEM VIDEO_SYSTEM_AUTO // analog by default; digital VTX users set vcd_video_system = HD
#define OSD_W_PIN            PA4
#define OSD_EN_PIN           PA5
#define OSD_SYNC_PIN         PA6

// Beeper pad (N-MOS low-side)
#define USE_BEEPER
#define BEEPER_PIN           PA7

// 10V VTX/cam rail enable, active high. Inverted so pinioInit drives it high
// at boot: the rail powers the VTX/air unit, which must come up without a
// switch. Bind PINIO1_BOX to a mode only if switched rail control is wanted.
#define PINIO1_PIN           PA11
#define PINIO1_CONFIG        (PINIO_CONFIG_MODE_OUT_PP | PINIO_CONFIG_OUT_INVERTED)

// Status LED (blue)
#define LED0_PIN             PA12

// Gyro+acc on SPI0: Rev 2 boards assembled with BMI270 (KiCad/BOM still says
// LSM6DSV16X); footprint also takes ICM-426xx/456xx
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
#define GYRO_1_CLKIN_PIN     PA15 // unused by ST parts
#define GYRO_1_SPI_INSTANCE  SPI0

// I2C0 pads carry UART0 (receiver) on rev 2, see erratum note above.
// #define I2C0_SDA_PIN         PA16
// #define I2C0_SCL_PIN         PA17

// UART1 pads (TX1/RX1) carry motors 1 and 4 on rev 2, see erratum note above.
// #define UART1_TX_PIN         PA22
// #define UART1_RX_PIN         PA21
#define DEFAULT_RX_FEATURE   FEATURE_RX_SERIAL
#define SERIALRX_PROVIDER    SERIALRX_CRSF
#define SERIALRX_UART        SERIAL_PORT_UART0

// LED strip pad
#define LED_STRIP_PIN        PA23

// PIO UART1: TX pad; RX wired to ESC connector telemetry pin
#define PIOUART1_TX_PIN      PA26
#define PIOUART1_RX_PIN      PA27

// Motors (PIO0 DShot)
// Rev 2 erratum: M1/M4 pads (PA31/PA28) shorted to GND; motor 1 relocated
// to the RX1 pad, motor 4 to the TX1 pad, see erratum note above.
#define MOTOR1_PIN           PA21
#define MOTOR2_PIN           PA30
#define MOTOR3_PIN           PA29
#define MOTOR4_PIN           PA22

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
#define DEFAULT_VOLTAGE_METER_SCALE   110 // 100k:10k divider (R1/R2)
#define DEFAULT_CURRENT_METER_SOURCE  CURRENT_METER_ADC // ESC current signal via 1k, scale depends on ESC
