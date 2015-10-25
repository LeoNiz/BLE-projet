#ifndef BLE_COMMON_H_
#define BLE_COMMON_H_

#include "stm32f4xx_nucleo.h"
#include "stm32_bluenrg_ble.h"
#include "cube_hal.h"
#include "hal_types.h"
#include "bluenrg_gatt_server.h"
#include "bluenrg_gap.h"
#include "string.h"
#include "bluenrg_gap_aci.h"
#include "bluenrg_gatt_aci.h"
#include "hci_const.h"
#include "gp_timer.h"
#include "bluenrg_hal_aci.h"
#include "bluenrg_aci_const.h"
#include "hci.h"
#include "hal.h"
#include "sm.h"
#include "debug.h"

#include <stdlib.h>


//DEFINE
/* Exported defines ----------------------------------------------------------*/
/**
 * @brief Instantiate two new services:
 *        1. Timer Service with two characteristics
 *           - Seconds characteristic (Readable only)
 *           - Minutes characteristics (Readable and Notifiable)
 *        2. LED Button Service with one characteristic
 *           - LED characteristic (Readable and Writable)
 */
#define NEW_SERVICES 0
/**
 * @}
 */

/** @addtogroup SENSOR_SERVICE_Exported_Types
 *  @{
 */
typedef int i32_t;

/**
 * @brief Structure containing acceleration value (in mg) of each axis.
 */
typedef struct {
  i32_t AXIS_X;
  i32_t AXIS_Y;
  i32_t AXIS_Z;
} AxesRaw_t;

/* nouvelles datas */
int32_t acc_xn, acc_yn, acc_zn;
int32_t gyr_xn, gyr_yn, gyr_zn;
int32_t mag_xn, mag_yn, mag_zn;
int32_t press1n, press2n;
int32_t hum1n, hum2n;
int32_t temp1n, temp2n;
uint16_t count;


//FONCTIONS
void BLE_Common_Init(void);
void BLE_Common_Process(void);

void GAP_ConnectionComplete_CB(uint8_t addr[6], uint16_t handle);
void GAP_DisconnectionComplete_CB(void);
void HCI_Event_CB(void *pckt);

void Write_Request_CB(uint16_t handle, uint8_t *data, uint16_t length);
void Read_Request_CB(uint16_t handle);

/* ADD services */
tBleStatus Add_Acc_Service(void);
tBleStatus Add_Environmental_Sensor_Service(void);
tBleStatus Add_LED_Service(void);
tBleStatus Add_Motion_Service(void);
tBleStatus Add_Count_Service(void);

/* Update */
tBleStatus Acc_Update(AxesRaw_t *data);
tBleStatus Temp_Update(int16_t temp);
tBleStatus Press_Update(int32_t press);
tBleStatus Humidity_Update(uint16_t humidity);
void Led_Update(uint8_t led);
void Count_Update(uint16_t count);
void Inc_Update(uint32_t inc);

/* Modify */
void Attribute_Modified_CB(uint16_t handle, uint8_t data_length, uint8_t *att_data);

/* Notify */
void Notify_Process(AxesRaw_t* p_axes);

#endif //BLE_COMMON_H_
