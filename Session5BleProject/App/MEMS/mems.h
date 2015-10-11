/*
 * mems.h
 *
 *  Created on: Sep 24, 2015
 *      Author: maxime
 */

#ifndef MEMS_H_
#define MEMS_H_

#include "cube_hal.h"
#include "x_nucleo_iks01a1.h"
#include "x_nucleo_iks01a1_imu_6axes.h"
#include "x_nucleo_iks01a1_magneto.h"
#include "x_nucleo_iks01a1_pressure.h"
#include "x_nucleo_iks01a1_hum_temp.h"
#include "stm32f4xx_nucleo.h"

// Enable sensor masks
#define NONE_SENSOR		                        0x00000000
#define PRESSURE_SENSOR                         0x00000001
#define TEMPERATURE_SENSOR                      0x00000002
#define HUMIDITY_SENSOR                         0x00000004
#define UV_SENSOR                               0x00000008  // for future use
#define ACCELEROMETER_SENSOR                    0x00000010
#define GYROSCOPE_SENSOR                        0x00000020
#define MAGNETIC_SENSOR                         0x00000040

void Mems_Init(void);
void Mems_Process(void);

void Mems_StartReadSensors(uint32_t read_period_ms, uint16_t sensor);
void Mems_StopReadSensors(void);

void Mems_Acc_CB(int32_t accX, int32_t accY, int32_t accZ);
void Mems_Gyr_CB(int32_t gyrX, int32_t gyrY, int32_t gyrZ);
void Mems_Mag_CB(int32_t magX, int32_t magY, int32_t magZ);
void Mems_Pressure_CB(int32_t d1, int32_t d2);
void Mems_HumTemp_CB(int32_t d1, int32_t d2, int32_t d3, int32_t d4);

#endif /* MEMS_H_ */
