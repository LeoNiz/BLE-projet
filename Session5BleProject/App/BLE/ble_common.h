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

void BLE_Common_Init(void);
void BLE_Common_Process(void);

void GAP_ConnectionComplete_CB(uint8_t addr[6], uint16_t handle);
void GAP_DisconnectionComplete_CB(void);
void HCI_Event_CB(void *pckt);
void Attribute_Modified_CB(uint16_t handle, uint8_t data_length, uint8_t *att_data);
void Attribute_Read_CB(uint16_t handle, uint8_t data_length, uint8_t *att_data);

#endif //BLE_COMMON_H_
