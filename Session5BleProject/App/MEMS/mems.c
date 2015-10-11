/*
 * mems.c
 *
 *  Created on: Sep 24, 2015
 *      Author: maxime
 */

#include "mems.h"
#include "gp_timer.h"
#include "debug.h"
#include "x_nucleo_iks01a1.h"
#include <math.h>

/*
 * Sensors values
 * */
static uint16_t sensor_activated;
volatile Axes_TypeDef ACC_Value; /*!< Acceleration Value */
volatile Axes_TypeDef GYR_Value; /*!< Gyroscope Value */
volatile Axes_TypeDef MAG_Value; /*!< Magnetometer Value */
volatile float PRESSURE_Value; /*!< Pressure Value */
volatile float HUMIDITY_Value; /*!< Humidity Value */
volatile float TEMPERATURE_Value; /*!< Temperature Value */

/*
 * timer used to manage the read frequency
 * */
static gp_timer_t read_period_timer;
volatile uint32_t mems_read_period_ms;

/*
 * Local functions
 * */
static void floatToInt(float in, int32_t *out_int, int32_t *out_dec,
		int32_t dec_prec);
static void Imu_6axes_Sensor_Handler();
static void Magneto_Sensor_Handler();
static void Pressure_Sensor_Handler();
static void HumTemp_Sensor_Handler();

/*
 * Function called before using this module
 * */
void Mems_Init(void) {
	sensor_activated = NONE_SENSOR;
}

/**
 * @brief  Starts reading data from the mems.
 * @param  read_period_ms frequency of the read
 * @param  sensor mask of sensors activated
 * @retval None
 */
void Mems_StartReadSensors(uint32_t read_period_ms, uint16_t sensor) {
	mems_read_period_ms = read_period_ms;
	sensor_activated = sensor;
	Timer_Set(&read_period_timer, mems_read_period_ms);
}

void Mems_StopReadSensors(void) {
	sensor_activated = NONE_SENSOR;
}

/*
 * Functions called when new data is available
 * */
__weak void Mems_Acc_CB(int32_t acc_x, int32_t acc_y, int32_t acc_z) {
	DEBUG_LINE("ACC_X: %d, ACC_Y: %d, ACC_Z: %d\n", (int ) acc_x, (int ) acc_y,
			(int ) acc_z);
}

__weak void Mems_Gyr_CB(int32_t gyr_x, int32_t gyr_y, int32_t gyr_z) {
	DEBUG_LINE("GYR_X: %d, GYR_Y: %d, GYR_Z: %d\n", (int ) gyr_x, (int ) gyr_y,
			(int ) gyr_z);
}

__weak void Mems_Mag_CB(int32_t mag_x, int32_t mag_y, int32_t mag_z) {
	DEBUG_LINE("MAG_X: %d, MAG_Y: %d, MAG_Z: %d\n", (int ) mag_x, (int ) mag_y,
			(int ) mag_z);
}

__weak void Mems_Pressure_CB(int32_t d1, int32_t d2) {
	DEBUG_LINE("Pressure: %d.%02d\n", (int ) d1, (int ) d2);
}

__weak void Mems_Hum_CB(int32_t d1, int32_t d2) {
	DEBUG_LINE("HUM: %d.%02d\n", (int ) d1, (int ) d2);
}

__weak void Mems_Temp_CB(int32_t d1, int32_t d2) {
	DEBUG_LINE("TEMP: %d.%02d\n", (int ) d1, (int ) d2);
}

/**
 * @brief  Handles the ACC+GYR axes data getting/sending
 * @retval None
 */
static void Imu_6axes_Sensor_Handler() {
	int32_t data[6];

	if (BSP_IMU_6AXES_isInitialized()) {
		BSP_IMU_6AXES_X_GetAxes((Axes_TypeDef *) &ACC_Value);
		BSP_IMU_6AXES_G_GetAxes((Axes_TypeDef *) &GYR_Value);

		data[0] = ACC_Value.AXIS_X;
		data[1] = ACC_Value.AXIS_Y;
		data[2] = ACC_Value.AXIS_Z;
		data[3] = GYR_Value.AXIS_X;
		data[4] = GYR_Value.AXIS_Y;
		data[5] = GYR_Value.AXIS_Z;

		if (sensor_activated & ACCELEROMETER_SENSOR)
			Mems_Acc_CB(data[0], data[1], data[2]);

		if (sensor_activated & GYROSCOPE_SENSOR)
			Mems_Gyr_CB(data[3], data[4], data[5]);
	}

	else {
		BSP_IMU_6AXES_Init();
	}
}

/**
 * @brief  Handles the MAG axes data getting/sending
 * @retval None
 */
static void Magneto_Sensor_Handler() {
	int32_t data[3];

	if (BSP_MAGNETO_isInitialized()) {
		BSP_MAGNETO_M_GetAxes((Axes_TypeDef *) &MAG_Value);

		data[0] = MAG_Value.AXIS_X;
		data[1] = MAG_Value.AXIS_Y;
		data[2] = MAG_Value.AXIS_Z;

		Mems_Mag_CB(data[0], data[1], data[2]);
	}

	else {
		BSP_MAGNETO_Init();
	}
}

/**
 * @brief  Handles the PRESS sensor data getting/sending
 * @retval None
 */
static void Pressure_Sensor_Handler() {
	int32_t d1, d2;

	if (BSP_PRESSURE_isInitialized()) {
		BSP_PRESSURE_GetPressure((float *) &PRESSURE_Value);
		floatToInt(PRESSURE_Value, &d1, &d2, 2);

		Mems_Pressure_CB(d1, d2);
	}

	else {
		BSP_PRESSURE_Init();
	}
}

/**
 * @brief  Handles the HUM+TEMP axes data getting/sending
 * @retval None
 */
static void HumTemp_Sensor_Handler() {
	int32_t d1, d2, d3, d4;

	if (BSP_HUM_TEMP_isInitialized()) {
		BSP_HUM_TEMP_GetHumidity((float *) &HUMIDITY_Value);
		BSP_HUM_TEMP_GetTemperature((float *) &TEMPERATURE_Value);
		floatToInt(HUMIDITY_Value, &d1, &d2, 2);
		floatToInt(TEMPERATURE_Value, &d3, &d4, 2);

		if (sensor_activated & HUMIDITY_SENSOR) {
			Mems_Hum_CB(d1, d2);
		}
		if (sensor_activated & TEMPERATURE_SENSOR) {
			Mems_Temp_CB(d3, d4);
		}
	}

	else {
		BSP_HUM_TEMP_Init();
	}
}

void Mems_Process(void) {
	if (Timer_Expired(&read_period_timer) != 0) {

		Timer_Restart(&read_period_timer);

		if ((sensor_activated & ACCELEROMETER_SENSOR)
				|| (sensor_activated & GYROSCOPE_SENSOR)) {
			Imu_6axes_Sensor_Handler();
		}

		if (sensor_activated & PRESSURE_SENSOR) {
			Pressure_Sensor_Handler();
		}

		if ((sensor_activated & HUMIDITY_SENSOR)
				|| (sensor_activated & TEMPERATURE_SENSOR)) {
			HumTemp_Sensor_Handler();

		}
		if (sensor_activated & MAGNETIC_SENSOR) {
			Magneto_Sensor_Handler();
		}
	}
}

/**
 * @brief  Splits a float into two integer values.
 * @param  in the float value as input
 * @param  out_int the pointer to the integer part as output
 * @param  out_dec the pointer to the decimal part as output
 * @param  dec_prec the decimal precision to be used
 * @retval None
 */
static void floatToInt(float in, int32_t *out_int, int32_t *out_dec,
		int32_t dec_prec) {
	*out_int = (int32_t) in;
	in = in - (float) (*out_int);
	*out_dec = (int32_t) trunc(in * pow(10, dec_prec));
}
