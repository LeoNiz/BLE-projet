#include "ble_common.h"
#include "mems.h"

#define BDADDR_SIZE 6

#define COPY_UUID_128(uuid_struct, uuid_15, uuid_14, uuid_13, uuid_12, uuid_11, uuid_10, uuid_9, uuid_8, uuid_7, uuid_6, uuid_5, uuid_4, uuid_3, uuid_2, uuid_1, uuid_0) \
do {\
    uuid_struct[0] = uuid_0; uuid_struct[1] = uuid_1; uuid_struct[2] = uuid_2; uuid_struct[3] = uuid_3; \
        uuid_struct[4] = uuid_4; uuid_struct[5] = uuid_5; uuid_struct[6] = uuid_6; uuid_struct[7] = uuid_7; \
            uuid_struct[8] = uuid_8; uuid_struct[9] = uuid_9; uuid_struct[10] = uuid_10; uuid_struct[11] = uuid_11; \
                uuid_struct[12] = uuid_12; uuid_struct[13] = uuid_13; uuid_struct[14] = uuid_14; uuid_struct[15] = uuid_15; \
}while(0)
//#if NEW_SERVICES
  //#define COPY_ACC_SERVICE_UUID(uuid_struct)  COPY_UUID_128(uuid_struct,0x01,0x36,0x6e,0x80, 0xcf,0x3a, 0x11,0xe1, 0x9a,0xb4, 0x00,0x02,0xa5,0xd5,0xc5,0x1b)
  #define COPY_ACC_SERVICE_UUID(uuid_struct)    COPY_UUID_128(uuid_struct,0x02,0x36,0x6e,0x80, 0xcf,0x3a, 0x11,0xe1, 0x9a,0xb4, 0x00,0x02,0xa5,0xd5,0xc5,0x1b)
  #define COPY_ACC_UUID(uuid_struct)          COPY_UUID_128(uuid_struct,0x34,0x0a,0x1b,0x80, 0xcf,0x4b, 0x11,0xe1, 0xac,0x36, 0x00,0x02,0xa5,0xd5,0xc5,0x1b)

  #define COPY_ENV_SENS_SERVICE_UUID(uuid_struct)  COPY_UUID_128(uuid_struct,0x42,0x82,0x1a,0x40, 0xe4,0x77, 0x11,0xe2, 0x82,0xd0, 0x00,0x02,0xa5,0xd5,0xc5,0x1b)
  #define COPY_TEMP_CHAR_UUID(uuid_struct)         COPY_UUID_128(uuid_struct,0xa3,0x2e,0x55,0x20, 0xe4,0x77, 0x11,0xe2, 0xa9,0xe3, 0x00,0x02,0xa5,0xd5,0xc5,0x1b)
  #define COPY_PRESS_CHAR_UUID(uuid_struct)        COPY_UUID_128(uuid_struct,0xcd,0x20,0xc4,0x80, 0xe4,0x8b, 0x11,0xe2, 0x84,0x0b, 0x00,0x02,0xa5,0xd5,0xc5,0x1b)
  #define COPY_HUMIDITY_CHAR_UUID(uuid_struct)     COPY_UUID_128(uuid_struct,0x01,0xc5,0x0b,0x60, 0xe4,0x8c, 0x11,0xe2, 0xa0,0x73, 0x00,0x02,0xa5,0xd5,0xc5,0x1b)

  // Time service: uuid = 0x08, 0x36, 0x6e, 0x80, 0xcf, 0x3a, 0x11, 0xe1, 0x9a, 0xb4, 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b
  //      straight uuid = 0x08366e80cf3a11e19ab40002a5d5c51b
  #define COPY_TIME_SERVICE_UUID(uuid_struct)  COPY_UUID_128(uuid_struct,0x08,0x36,0x6e,0x80, 0xcf,0x3a, 0x11,0xe1, 0x9a,0xb4, 0x00,0x02,0xa5,0xd5,0xc5,0x1b)
  #define COPY_TIME_UUID(uuid_struct)          COPY_UUID_128(uuid_struct,0x09,0x36,0x6e,0x80, 0xcf,0x3a, 0x11,0xe1, 0x9a,0xb4, 0x00,0x02,0xa5,0xd5,0xc5,0x1b)
  #define COPY_MINUTE_UUID(uuid_struct)        COPY_UUID_128(uuid_struct,0x0a,0x36,0x6e,0x80, 0xcf,0x3a, 0x11,0xe1, 0x9a,0xb4, 0x00,0x02,0xa5,0xd5,0xc5,0x1b)

  // LED service
  //#define COPY_LED_SERVICE_UUID(uuid_struct)  COPY_UUID_128(uuid_struct,0x0b,0x36,0x6e,0x80, 0xcf,0x3a, 0x11,0xe1, 0x9a,0xb4, 0x00,0x02,0xa5,0xd5,0xc5,0x1b)
  //#define COPY_LED_UUID(uuid_struct)          COPY_UUID_128(uuid_struct,0x0c,0x36,0x6e,0x80, 0xcf,0x3a, 0x11,0xe1, 0x9a,0xb4, 0x00,0x02,0xa5,0xd5,0xc5,0x1b)
/*#else
  #define COPY_ACC_SERVICE_UUID(uuid_struct)  COPY_UUID_128(uuid_struct,0x02,0x36,0x6e,0x80, 0xcf,0x3a, 0x11,0xe1, 0x9a,0xb4, 0x00,0x02,0xa5,0xd5,0xc5,0x1b)
  #define COPY_FREE_FALL_UUID(uuid_struct)    COPY_UUID_128(uuid_struct,0xe2,0x3e,0x78,0xa0, 0xcf,0x4a, 0x11,0xe1, 0x8f,0xfc, 0x00,0x02,0xa5,0xd5,0xc5,0x1b)
  #define COPY_ACC_UUID(uuid_struct)          COPY_UUID_128(uuid_struct,0x34,0x0a,0x1b,0x80, 0xcf,0x4b, 0x11,0xe1, 0xac,0x36, 0x00,0x02,0xa5,0xd5,0xc5,0x1b)

  #define COPY_ENV_SENS_SERVICE_UUID(uuid_struct)  COPY_UUID_128(uuid_struct,0x42,0x82,0x1a,0x40, 0xe4,0x77, 0x11,0xe2, 0x82,0xd0, 0x00,0x02,0xa5,0xd5,0xc5,0x1b)
  #define COPY_TEMP_CHAR_UUID(uuid_struct)         COPY_UUID_128(uuid_struct,0xa3,0x2e,0x55,0x20, 0xe4,0x77, 0x11,0xe2, 0xa9,0xe3, 0x00,0x02,0xa5,0xd5,0xc5,0x1b)
  #define COPY_PRESS_CHAR_UUID(uuid_struct)        COPY_UUID_128(uuid_struct,0xcd,0x20,0xc4,0x80, 0xe4,0x8b, 0x11,0xe2, 0x84,0x0b, 0x00,0x02,0xa5,0xd5,0xc5,0x1b)
  #define COPY_HUMIDITY_CHAR_UUID(uuid_struct)     COPY_UUID_128(uuid_struct,0x01,0xc5,0x0b,0x60, 0xe4,0x8c, 0x11,0xe2, 0xa0,0x73, 0x00,0x02,0xa5,0xd5,0xc5,0x1b)
#endif
/* Store Value into a buffer in Little Endian Format */
#define STORE_LE_16(buf, val)    ( ((buf)[0] =  (uint8_t) (val)    ) , \
                                   ((buf)[1] =  (uint8_t) (val>>8) ) )

/* Private variables ---------------------------------------------------------*/
volatile int connected = FALSE;
volatile uint8_t set_connectable = 1;
volatile uint16_t connection_handle = 0;
AxesRaw_t axes_data;
uint16_t sampleServHandle, TXCharHandle, RXCharHandle;
uint16_t accServHandle, freeFallCharHandle, accCharHandle;
uint16_t envSensServHandle, tempCharHandle, pressCharHandle, humidityCharHandle;


//#if NEW_SERVICES
  uint16_t timeServHandle, secondsCharHandle, minuteCharHandle;
  uint16_t ledServHandle, ledButtonCharHandle;
  uint8_t ledState = 0;
  int previousMinuteValue = -1;
//#endif

void BLE_Common_Init(void)
{
	const char *name = "BlueNRG";
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

	ret = Add_Acc_Service();

	  if(ret == BLE_STATUS_SUCCESS)
	    DEBUG_LINE("Acc service added successfully.\n");
	  else
	    DEBUG_LINE("Error while adding Acc service.\n");
	  ret = Add_Environmental_Sensor_Service();

	    if(ret == BLE_STATUS_SUCCESS)
	      DEBUG_LINE("Environmental Sensor service added successfully.\n");
	    else
	      DEBUG_LINE("Error while adding Environmental Sensor service.\n");

	    /* Instantiate LED Button Service with one characteristic:
	   	     * - LED characteristic (Readable and Writable)
	   	     */
	   	    ret = Add_LED_Service();

	   	    if(ret == BLE_STATUS_SUCCESS)
	   	      DEBUG_LINE("LED service added successfully.\n");
	   	    else
	   	      DEBUG_LINE("Error while adding LED service.\n");

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


	  #endif

	/* Set output power level */
	ret = aci_hal_set_tx_power_level(1, 4);
}

void BLE_Common_Process(void)
{
	HCI_Process();
	User_Process(&axes_data);
	#if NEW_SERVICES
	    Update_Time_Characteristics();
	#endif
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
  if(handle == accCharHandle + 1){
    Acc_Update((AxesRaw_t*)&axes_data);
  }
  else if(handle == tempCharHandle + 1){
	Mems_StartReadSensors(100,TEMPERATURE_SENSOR);
	DEBUG_LINE("Temperature : %d.%02d C",(int)temp1n, (int)temp2n);
	int temp1 = (int)temp1n;
	int temp2 = (int)temp2n;
    int16_t data;
    data = (int16_t)(temp1*100+temp2);
    Acc_Update((AxesRaw_t*)&axes_data); //FIXME: to overcome issue on Android App
                                        // If the user button is not pressed within
                                        // a short time after the connection,
                                        // a pop-up reports a "No valid characteristics found" error.
    Temp_Update(data);
  }
  else if(handle == pressCharHandle + 1){
	Mems_StartReadSensors(100,PRESSURE_SENSOR);
	DEBUG_LINE("Pression : %d.%02d hPa", (int) press1n, (int) press2n);
	int press1 = (int)press1n;
	int press2 = (int)press2n;
    int32_t data;
    data = (int32_t)(press1*100+press2);
    Press_Update(data);
  }
  else if(handle == humidityCharHandle + 1){
	Mems_StartReadSensors(100,HUMIDITY_SENSOR);
	DEBUG_LINE("HUM: %d.%02d", (int ) hum1n, (int ) hum2n);
	int hum1 = (int)hum1n;
	int hum2 = (int)hum2n;
	uint16_t data;
    data = (uint16_t)(hum1*100+hum2);
    Humidity_Update(data);
  }

  //EXIT:
  if(connection_handle != 0)
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
			//AJOUT
		case EVT_BLUE_GATT_ATTRIBUTE_MODIFIED:
		 {
		 /* this callback is invoked when a GATT attribute is modified
		  extract callback data and pass to suitable handler function */
		  evt_gatt_attr_modified *evt = (evt_gatt_attr_modified*)blue_evt->data;

		  Attribute_Modified_CB(evt->attr_handle, evt->data_length, evt->att_data);
		 }
		 //STOP
		    break;
		}
	}
		break;
	}
}

//NOUVELLES FONCTIONS
tBleStatus Add_Acc_Service(void)
{
  tBleStatus ret;

  uint8_t uuid[16];

  COPY_ACC_SERVICE_UUID(uuid);
  ret = aci_gatt_add_serv(UUID_TYPE_128,  uuid, PRIMARY_SERVICE, 7,
                          &accServHandle);
  if (ret != BLE_STATUS_SUCCESS) goto fail;

  /*COPY_FREE_FALL_UUID(uuid);
  ret =  aci_gatt_add_char(accServHandle, UUID_TYPE_128, uuid, 1,
                           CHAR_PROP_NOTIFY, ATTR_PERMISSION_NONE, 0,
                           16, 0, &freeFallCharHandle);
  if (ret != BLE_STATUS_SUCCESS) goto fail;*/

  COPY_ACC_UUID(uuid);
  ret =  aci_gatt_add_char(accServHandle, UUID_TYPE_128, uuid, 6,
                           CHAR_PROP_NOTIFY|CHAR_PROP_READ,
                           ATTR_PERMISSION_NONE,
                           GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                           16, 0, &accCharHandle);
  if (ret != BLE_STATUS_SUCCESS) goto fail;

  PRINTF("Service ACC added. Handle 0x%04X, Free fall Charac handle: 0x%04X, Acc Charac handle: 0x%04X\n",accServHandle, freeFallCharHandle, accCharHandle);
  return BLE_STATUS_SUCCESS;

fail:
  PRINTF("Error while adding ACC service.\n");
  return BLE_STATUS_ERROR ;

}

void User_Process(AxesRaw_t* p_axes)
{
  if(set_connectable){
	  BLE_Common_Set_Discoverable();
    set_connectable = FALSE;
  }

  /* Check if the user has pushed the button */
  if(BSP_PB_GetState(BUTTON_KEY) == RESET)
  {
    while (BSP_PB_GetState(BUTTON_KEY) == RESET);

    //BSP_LED_Toggle(LED2); //used for debugging (BSP_LED_Init() above must be also enabled)

    if(connected)
    {
      /* Update acceleration data */
      Mems_StartReadSensors(100,ACCELEROMETER_SENSOR);
      DEBUG_LINE("ACC_X: %d, ACC_Y: %d, ACC_Z: %d\n", (int ) acc_xn, (int ) acc_yn,
    				(int ) acc_zn);
      p_axes->AXIS_X = acc_xn;
      p_axes->AXIS_Y = acc_yn;
      p_axes->AXIS_Z = acc_zn;
      //DEBUG_LINE("ACC: X=%6d Y=%6d Z=%6d\r\n", p_axes->AXIS_X, p_axes->AXIS_Y, p_axes->AXIS_Z);
      Acc_Update(p_axes);
    }
  }
}

tBleStatus Acc_Update(AxesRaw_t *data)
{
  tBleStatus ret;
  uint8_t buff[6];

  STORE_LE_16(buff,data->AXIS_X);
  STORE_LE_16(buff+2,data->AXIS_Y);
  STORE_LE_16(buff+4,data->AXIS_Z);

  ret = aci_gatt_update_char_value(accServHandle, accCharHandle, 0, 6, buff);

  if (ret != BLE_STATUS_SUCCESS){
    PRINTF("Error while updating ACC characteristic.\n") ;
    return BLE_STATUS_ERROR ;
  }
  return BLE_STATUS_SUCCESS;
}

void Update_Time_Characteristics(void) {
  /* update "seconds and minutes characteristics" of time service */
  Seconds_Update();
  Minutes_Notify();
}

tBleStatus Seconds_Update(void)
{
  uint32_t val;
  tBleStatus ret;

  /* Obtain system tick value in milliseconds, and convert it to seconds. */
  val = HAL_GetTick();
  val = val/1000;

  /* create a time[] array to pass as last argument of aci_gatt_update_char_value() API*/
  const uint8_t time[4] = {(val >> 24)&0xFF, (val >> 16)&0xFF, (val >> 8)&0xFF, (val)&0xFF};
  /*
   * Update value of "Seconds characteristic" using aci_gatt_update_char_value() API
   * Please refer to 'BlueNRG Application Command Interface.pdf' for detailed
   * API description
   */
  ret = aci_gatt_update_char_value(timeServHandle, secondsCharHandle, 0, 4,
                                   time);

  if (ret != BLE_STATUS_SUCCESS){
    PRINTF("Error while updating TIME characteristic.\n") ;
    return BLE_STATUS_ERROR ;
  }
  return BLE_STATUS_SUCCESS;
}

tBleStatus Minutes_Notify(void)
{
  uint32_t val;
  uint32_t minuteValue;
  tBleStatus ret;

  /* Obtain system tick value in milliseconds */
  val = HAL_GetTick();

  /* update "Minutes characteristic" value iff it has changed w.r.t. previous
   * "minute" value.
   */
  if((minuteValue=val/(60*1000))!=previousMinuteValue) {
    /* memorize this "minute" value for future usage */
    previousMinuteValue = minuteValue;

    /* create a time[] array to pass as last argument of aci_gatt_update_char_value() API*/
    const uint8_t time[4] = {(minuteValue >> 24)&0xFF, (minuteValue >> 16)&0xFF, (minuteValue >> 8)&0xFF, (minuteValue)&0xFF};

  /*
   * Update value of "Minutes characteristic" using aci_gatt_update_char_value() API
   * Please refer to 'BlueNRG Application Command Interface.pdf' for detailed
   * API description
   */
    ret = aci_gatt_update_char_value(timeServHandle, minuteCharHandle, 0, 4,
                                     time);
    if (ret != BLE_STATUS_SUCCESS){
      PRINTF("Error while updating TIME characteristic.\n") ;
      return BLE_STATUS_ERROR ;
    }
  }
  return BLE_STATUS_SUCCESS;
}

tBleStatus Add_Environmental_Sensor_Service(void)
{
  tBleStatus ret;
  uint8_t uuid[16];
  uint16_t uuid16;
  charactFormat charFormat;
  uint16_t descHandle;

  COPY_ENV_SENS_SERVICE_UUID(uuid);
  ret = aci_gatt_add_serv(UUID_TYPE_128,  uuid, PRIMARY_SERVICE, 10,
                          &envSensServHandle);
  if (ret != BLE_STATUS_SUCCESS) goto fail;

  /* Temperature Characteristic */
  COPY_TEMP_CHAR_UUID(uuid);
  ret =  aci_gatt_add_char(envSensServHandle, UUID_TYPE_128, uuid, 2,
                           CHAR_PROP_READ, ATTR_PERMISSION_NONE,
                           GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                           16, 0, &tempCharHandle);
  if (ret != BLE_STATUS_SUCCESS) goto fail;

  charFormat.format = FORMAT_SINT16;
  charFormat.exp = -1;
  charFormat.unit = UNIT_TEMP_CELSIUS;
  charFormat.name_space = 0;
  charFormat.desc = 0;

  uuid16 = CHAR_FORMAT_DESC_UUID;

  ret = aci_gatt_add_char_desc(envSensServHandle,
                               tempCharHandle,
                               UUID_TYPE_16,
                               (uint8_t *)&uuid16,
                               7,
                               7,
                               (void *)&charFormat,
                               ATTR_PERMISSION_NONE,
                               ATTR_ACCESS_READ_ONLY,
                               0,
                               16,
                               FALSE,
                               &descHandle);
  if (ret != BLE_STATUS_SUCCESS) goto fail;

  /* Pressure Characteristic */
  if(1){ //FIXME
    COPY_PRESS_CHAR_UUID(uuid);
    ret =  aci_gatt_add_char(envSensServHandle, UUID_TYPE_128, uuid, 3,
                             CHAR_PROP_READ, ATTR_PERMISSION_NONE,
                             GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                             16, 0, &pressCharHandle);
    if (ret != BLE_STATUS_SUCCESS) goto fail;

    charFormat.format = FORMAT_SINT24;
    charFormat.exp = -5;
    charFormat.unit = UNIT_PRESSURE_BAR;
    charFormat.name_space = 0;
    charFormat.desc = 0;

    uuid16 = CHAR_FORMAT_DESC_UUID;

    ret = aci_gatt_add_char_desc(envSensServHandle,
                                 pressCharHandle,
                                 UUID_TYPE_16,
                                 (uint8_t *)&uuid16,
                                 7,
                                 7,
                                 (void *)&charFormat,
                                 ATTR_PERMISSION_NONE,
                                 ATTR_ACCESS_READ_ONLY,
                                 0,
                                 16,
                                 FALSE,
                                 &descHandle);
    if (ret != BLE_STATUS_SUCCESS) goto fail;
  }
  /* Humidity Characteristic */
  if(1){   //FIXME
    COPY_HUMIDITY_CHAR_UUID(uuid);
    ret =  aci_gatt_add_char(envSensServHandle, UUID_TYPE_128, uuid, 2,
                             CHAR_PROP_READ, ATTR_PERMISSION_NONE,
                             GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                             16, 0, &humidityCharHandle);
    if (ret != BLE_STATUS_SUCCESS) goto fail;

    charFormat.format = FORMAT_UINT16;
    charFormat.exp = -1;
    charFormat.unit = UNIT_UNITLESS;
    charFormat.name_space = 0;
    charFormat.desc = 0;

    uuid16 = CHAR_FORMAT_DESC_UUID;

    ret = aci_gatt_add_char_desc(envSensServHandle,
                                 humidityCharHandle,
                                 UUID_TYPE_16,
                                 (uint8_t *)&uuid16,
                                 7,
                                 7,
                                 (void *)&charFormat,
                                 ATTR_PERMISSION_NONE,
                                 ATTR_ACCESS_READ_ONLY,
                                 0,
                                 16,
                                 FALSE,
                                 &descHandle);
    if (ret != BLE_STATUS_SUCCESS) goto fail;
  }
  PRINTF("Service ENV_SENS added. Handle 0x%04X, TEMP Charac handle: 0x%04X, PRESS Charac handle: 0x%04X, HUMID Charac handle: 0x%04X\n",envSensServHandle, tempCharHandle, pressCharHandle, humidityCharHandle);
  return BLE_STATUS_SUCCESS;

fail:
  PRINTF("Error while adding ENV_SENS service.\n");
  return BLE_STATUS_ERROR ;

}

tBleStatus Add_LED_Service(void)
{

#define COPY_LED_SERVICE_UUID(uuid_struct)  COPY_UUID_128(uuid_struct,0xaf,0xce,0xb8,0xe0,0x03,0x77,0x11,0xe0,0xa5,0xc2,0x00,0x02,0xa5,0xd5,0xc5,0x1b)
#define COPY_LED_UUID(uuid_struct)          COPY_UUID_128(uuid_struct,0xa4,0xc3,0xff,0xc1,0xaa,0x17,0x11,0xe0,0x5a,0xba,0x00,0x02,0xa5,0xd5,0xc5,0x1b)
  tBleStatus ret;
  uint8_t uuid[16];

  /* copy "LED service UUID" defined above to 'uuid' local variable */
  COPY_LED_SERVICE_UUID(uuid);
  /*
   * now add "LED service" to GATT server, service handle is returned
   * via 'ledServHandle' parameter of aci_gatt_add_serv() API.
   * Please refer to 'BlueNRG Application Command Interface.pdf' for detailed
   * API description
  */
  ret = aci_gatt_add_serv(UUID_TYPE_128, uuid, PRIMARY_SERVICE, 7,
                          &ledServHandle);
  if (ret != BLE_STATUS_SUCCESS) goto fail;

  /* copy "LED button characteristic UUID" defined above to 'uuid' local variable */
  COPY_LED_UUID(uuid);
  /*
   * now add "LED button characteristic" to LED service, characteristic handle
   * is returned via 'ledButtonCharHandle' parameter of aci_gatt_add_char() API.
   * This characteristic is writable, as specified by 'CHAR_PROP_WRITE' parameter.
   * Please refer to 'BlueNRG Application Command Interface.pdf' for detailed
   * API description
  */
  ret =  aci_gatt_add_char(ledServHandle, UUID_TYPE_128, uuid, 4,
                           CHAR_PROP_WRITE | CHAR_PROP_WRITE_WITHOUT_RESP, ATTR_PERMISSION_NONE, GATT_NOTIFY_ATTRIBUTE_WRITE,
                           16, 1, &ledButtonCharHandle);
  if (ret != BLE_STATUS_SUCCESS) goto fail;

  PRINTF("Service LED BUTTON added. Handle 0x%04X, LED button Charac handle: 0x%04X\n",ledServHandle, ledButtonCharHandle);
  return BLE_STATUS_SUCCESS;

fail:
  PRINTF("Error while adding LED service.\n");
  return BLE_STATUS_ERROR;
}

void Attribute_Modified_CB(uint16_t handle, uint8_t data_length, uint8_t *att_data)
{
  /* If GATT client has modified 'LED button characteristic' value, toggle LED2 */
  if(handle == ledButtonCharHandle + 1){
      BSP_LED_Toggle(LED2);
  }
}
// TEMP, PRESS, HUMIDITY UPDATE
tBleStatus Temp_Update(int16_t temp)
{
  tBleStatus ret;

  ret = aci_gatt_update_char_value(envSensServHandle, tempCharHandle, 0, 2,
                                   (uint8_t*)&temp);

  if (ret != BLE_STATUS_SUCCESS){
    PRINTF("Error while updating TEMP characteristic.\n") ;
    return BLE_STATUS_ERROR ;
  }
  return BLE_STATUS_SUCCESS;

}

/**
 * @brief  Update pressure characteristic value.
 * @param  int32_t Pressure in mbar
 * @retval tBleStatus Status
 */
tBleStatus Press_Update(int32_t press)
{
  tBleStatus ret;

  ret = aci_gatt_update_char_value(envSensServHandle, pressCharHandle, 0, 3,
                                   (uint8_t*)&press);

  if (ret != BLE_STATUS_SUCCESS){
    PRINTF("Error while updating TEMP characteristic.\n") ;
    return BLE_STATUS_ERROR ;
  }
  return BLE_STATUS_SUCCESS;

}

/**
 * @brief  Update humidity characteristic value.
 * @param  uint16_thumidity RH (Relative Humidity) in thenths of %
 * @retval tBleStatus      Status
 */
tBleStatus Humidity_Update(uint16_t humidity)
{
  tBleStatus ret;

  ret = aci_gatt_update_char_value(envSensServHandle, humidityCharHandle, 0, 2,
                                   (uint8_t*)&humidity);

  if (ret != BLE_STATUS_SUCCESS){
    PRINTF("Error while updating TEMP characteristic.\n") ;
    return BLE_STATUS_ERROR ;
  }
  return BLE_STATUS_SUCCESS;

}


