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
// nouvelles datas
int32_t acc_xn, acc_yn, acc_zn;
int32_t gyr_xn, gyr_yn, gyr_zn;
int32_t mag_xn, mag_yn, mag_zn;
int32_t press1n, press2n;
int32_t hum1n, hum2n;
int32_t temp1n, temp2n;
int led2;


//FONCTIONS
void BLE_Common_Init(void);
void BLE_Common_Process(void);

void GAP_ConnectionComplete_CB(uint8_t addr[6], uint16_t handle);
void GAP_DisconnectionComplete_CB(void);
void HCI_Event_CB(void *pckt);

void Write_Request_CB(uint16_t handle, uint8_t *data, uint16_t length);
void Read_Request_CB(uint16_t handle);

tBleStatus Add_Acc_Service(void);
void User_Process(AxesRaw_t* p_axes);
tBleStatus Acc_Update(AxesRaw_t *data);
void Update_Time_Characteristics(void);
tBleStatus Seconds_Update(void);
tBleStatus Minutes_Notify(void);
tBleStatus Add_Environmental_Sensor_Service(void);
tBleStatus Add_LED_Service(void);
void Attribute_Modified_CB(uint16_t handle, uint8_t data_length, uint8_t *att_data);
tBleStatus Temp_Update(int16_t temp);
tBleStatus Press_Update(int32_t press);
tBleStatus Humidity_Update(uint16_t humidity);
void Read_Request_CB(uint16_t handle);


#endif //BLE_COMMON_H_
