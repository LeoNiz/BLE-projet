#include "ble_common.h"

#define BDADDR_SIZE 6

#define COPY_UUID_128(uuid_struct, uuid_15, uuid_14, uuid_13, uuid_12, uuid_11, uuid_10, uuid_9, uuid_8, uuid_7, uuid_6, uuid_5, uuid_4, uuid_3, uuid_2, uuid_1, uuid_0) \
do {\
    uuid_struct[0] = uuid_0; uuid_struct[1] = uuid_1; uuid_struct[2] = uuid_2; uuid_struct[3] = uuid_3; \
        uuid_struct[4] = uuid_4; uuid_struct[5] = uuid_5; uuid_struct[6] = uuid_6; uuid_struct[7] = uuid_7; \
            uuid_struct[8] = uuid_8; uuid_struct[9] = uuid_9; uuid_struct[10] = uuid_10; uuid_struct[11] = uuid_11; \
                uuid_struct[12] = uuid_12; uuid_struct[13] = uuid_13; uuid_struct[14] = uuid_14; uuid_struct[15] = uuid_15; \
}while(0)

/* Store Value into a buffer in Little Endian Format */
#define STORE_LE_16(buf, val)    ( ((buf)[0] =  (uint8_t) (val)    ) , \
                                   ((buf)[1] =  (uint8_t) (val>>8) ) )

/* Private variables ---------------------------------------------------------*/
volatile int connected = FALSE;
volatile uint8_t set_connectable = 1;
volatile uint16_t connection_handle = 0;
uint16_t accServHandle, freeFallCharHandle, accCharHandle;

void Add_Acc_Service(tBleStatus* ret)
{

  uint8_t uuid[16];

  COPY_ACC_SERVICE_UUID(uuid);
  &ret = aci_gatt_add_serv(UUID_TYPE_128,  uuid, PRIMARY_SERVICE, 7,
                          &accServHandle);
  if (ret != BLE_STATUS_SUCCESS) goto fail;

  COPY_FREE_FALL_UUID(uuid);
  &ret =  aci_gatt_add_char(accServHandle, UUID_TYPE_128, uuid, 1,
                           CHAR_PROP_NOTIFY, ATTR_PERMISSION_NONE, 0,
                           16, 0, &freeFallCharHandle);
  if (&ret != BLE_STATUS_SUCCESS) goto fail;

  COPY_ACC_UUID(uuid);
  &ret =  aci_gatt_add_char(accServHandle, UUID_TYPE_128, uuid, 6,
                           CHAR_PROP_NOTIFY|CHAR_PROP_READ,
                           ATTR_PERMISSION_NONE,
                           GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                           16, 0, &accCharHandle);
  if (&ret != BLE_STATUS_SUCCESS) goto fail;

  PRINTF("Service ACC added. Handle 0x%04X, Free fall Charac handle: 0x%04X, Acc Charac handle: 0x%04X\n",accServHandle, freeFallCharHandle, accCharHandle);
  &ret=BLE_STATUS_SUCCESS;

fail:
  PRINTF("Error while adding ACC service.\n");
  &ret=BLE_STATUS_ERROR ;

}

void BLE_Common_Init(void)
{
	const char *name = "Team2";
	//This avoid to clear the cache on some Android device
#ifdef BLUENRG_MS
	uint8_t SERVER_BDADDR[] =
	{	0x12, 0x34, 0x00, 0xE1, 0x80, 0x02};
#else
	uint8_t SERVER_BDADDR[] =
	{ 0xCC, 0x45, 0x4C, 0x45, 0x00, 0x02 };
#endif
	uint8_t bdaddr[BDADDR_SIZE];
	uint16_t service_handle, dev_name_char_handle, appearance_char_handle;
	int ret;
	/* Initialize the BlueNRG SPI driver */
	BNRG_SPI_Init();

	/* Initialize the BlueNRG HCI */
	HCI_Init();

	/* Reset BlueNRG hardware */
	BlueNRG_RST();

	/* The Nucleo board must be configured as SERVER */
	memcpy(bdaddr, SERVER_BDADDR, sizeof(SERVER_BDADDR));

	ret = aci_hal_write_config_data(CONFIG_DATA_PUBADDR_OFFSET,
	CONFIG_DATA_PUBADDR_LEN, bdaddr);
	if (ret)
	{
		DEBUG_LINE("Setting BD_ADDR failed.\n");
	}

	ret = aci_gatt_init();
	if (ret)
	{
		DEBUG_LINE("GATT_Init failed.\n");
	}

#ifdef BLUENRG_MS
	ret = aci_gap_init(GAP_PERIPHERAL_ROLE, 0, 0x07, &service_handle, &dev_name_char_handle, &appearance_char_handle);
#else
	ret = aci_gap_init(GAP_PERIPHERAL_ROLE, &service_handle, &dev_name_char_handle, &appearance_char_handle);
#endif

	if (ret != BLE_STATUS_SUCCESS)
	{
		DEBUG_LINE("GAP_Init failed.\n");
	}

	ret = aci_gatt_update_char_value(service_handle, dev_name_char_handle, 0, strlen(name), (uint8_t *) name);

	if (ret)
	{
		DEBUG_LINE("aci_gatt_update_char_value failed.\n");
		while (1)
			;
	}

	ret = aci_gap_set_auth_requirement(MITM_PROTECTION_REQUIRED,
	OOB_AUTH_DATA_ABSENT,
	NULL, 7, 16,
	USE_FIXED_PIN_FOR_PAIRING, 123456,
	BONDING);
	if (ret == BLE_STATUS_SUCCESS)
	{
		DEBUG_LINE("BLE Stack Initialized.\n");
	}

	DEBUG_LINE("SERVER: BLE Stack Initialized\n");
//AJOUT
	Add_Acc_Service(ret);

	  if(ret == BLE_STATUS_SUCCESS)
	    DEBUG_LINE("Acc service added successfully.\n");
	  else
	    DEBUG_LINE("Error while adding Acc service.\n");

	  ret = Add_Environmental_Sensor_Service();

	  if(ret == BLE_STATUS_SUCCESS)
	    DEBUG_LINE("Environmental Sensor service added successfully.\n");
	  else
	    DEBUG_LINE("Error while adding Environmental Sensor service.\n");

	#if NEW_SERVICES
	  /* Instantiate Timer Service with two characteristics:
	   * - seconds characteristic (Readable only)
	   * - minutes characteristics (Readable and Notifiable )
	   */
	  ret = Add_Time_Service();

	  if(ret == BLE_STATUS_SUCCESS)
	    DEBUG_LINE("Time service added successfully.\n");
	  else
	    DEBUG_LINE("Error while adding Time service.\n");

	  /* Instantiate LED Button Service with one characteristic:
	   * - LED characteristic (Readable and Writable)
	   */
	  ret = Add_LED_Service();

	  if(ret == BLE_STATUS_SUCCESS)
	    DEBUG_LINE("LED service added successfully.\n");
	  else
	    DEBUG_LINE("Error while adding LED service.\n");
	#endif


	//STOP


	/* Set output power level */
	ret = aci_hal_set_tx_power_level(1, 4);
}

void BLE_Common_Process(void)
{
	HCI_Process();
}

void BLE_Common_Set_Discoverable(void)
{
	tBleStatus ret;

	const char local_name[] =
	{ AD_TYPE_COMPLETE_LOCAL_NAME, 'e', 'l', 'e', '4', '1', '0', '_','t','e','a','m','2' };

	/* disable scan response */
	hci_le_set_scan_resp_data(0, NULL);
	DEBUG_LINE("General Discoverable Mode.\n");

	ret = aci_gap_set_discoverable(ADV_IND, 0, 0, PUBLIC_ADDR, NO_WHITE_LIST_USE, sizeof(local_name), local_name, 0, NULL, 0, 0);
	if (ret != BLE_STATUS_SUCCESS)
	{
		DEBUG_LINE("Error while setting discoverable mode (%d)\n", ret);
	}
}

/**
 * @brief  This function is called when there is a LE Connection Complete event.
 * @param  uint8_t Address of peer device
 * @param  uint16_t Connection handle
 * @retval None
 */
void GAP_ConnectionComplete_CB(uint8_t addr[6], uint16_t handle)
{
	connected = TRUE;
	connection_handle = handle;

	DEBUG_LINE("Connected to device:");
	for (int i = 5; i > 0; i--)
	{
		DEBUG_LINE("%02X-", addr[i]);
	}
	DEBUG_LINE("%02X\n", addr[0]);
}

/**
 * @brief  This function is called when the peer device gets disconnected.
 * @param  None
 * @retval None
 */
void GAP_DisconnectionComplete_CB(void)
{
	connected = FALSE;
	DEBUG_LINE("BLE Disconnected\n");
}

void Read_Request_CB(uint16_t handle)
{
	//This Callback is called when a GATT Client wants to read an attribute
	if (connection_handle != 0)
		aci_gatt_allow_read(connection_handle);
}

void Write_Request_CB(uint16_t handle, uint8_t *data, uint16_t length)
{
	//This Callback is called when a GATT Client wants to write an attribute
}

/**
 * @brief  Callback processing the ACI events.
 * @note   Inside this function each event must be identified and correctly
 *         parsed.
 * @param  void* Pointer to the ACI packet
 * @retval None
 */
void HCI_Event_CB(void *pckt)
{
	hci_uart_pckt *hci_pckt = pckt;
	/* obtain event packet */
	hci_event_pckt *event_pckt = (hci_event_pckt*) hci_pckt->data;

	if (hci_pckt->type != HCI_EVENT_PKT)
		return;

	switch (event_pckt->evt)
	{

	case EVT_DISCONN_COMPLETE:
	{
		GAP_DisconnectionComplete_CB();
	}
		break;

	case EVT_LE_META_EVENT:
	{
		evt_le_meta_event *evt = (void *) event_pckt->data;

		switch (evt->subevent)
		{
		case EVT_LE_CONN_COMPLETE:
		{
			evt_le_connection_complete *cc = (void *) evt->data;
			GAP_ConnectionComplete_CB(cc->peer_bdaddr, cc->handle);
		}
			break;
		}
	}
		break;

	case EVT_VENDOR:
	{
		evt_blue_aci *blue_evt = (void*) event_pckt->data;
		switch (blue_evt->ecode)
		{
		case EVT_BLUE_GATT_READ_PERMIT_REQ:
		{
			evt_gatt_read_permit_req *pr = (void*) blue_evt->data;
			Read_Request_CB(pr->attr_handle);
		}
			break;

		case EVT_BLUE_GATT_WRITE_PERMIT_REQ:
		{
			evt_gatt_write_permit_req *pr = (void*) blue_evt->data;
			Write_Request_CB(pr->attr_handle, pr->data, pr->data_length);
		}
			break;
		}
	}
		break;
	}
}


