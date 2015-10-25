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

  #define COPY_ACC_SERVICE_UUID(uuid_struct)    COPY_UUID_128(uuid_struct,0x02,0x36,0x6e,0x80, 0xcf,0x3a, 0x11,0xe1, 0x9a,0xb4, 0x00,0x02,0xa5,0xd5,0xc5,0x1b)
  #define COPY_ACC_UUID(uuid_struct)          COPY_UUID_128(uuid_struct,0x34,0x0a,0x1b,0x80, 0xcf,0x4b, 0x11,0xe1, 0xac,0x36, 0x00,0x02,0xa5,0xd5,0xc5,0x1b)

  #define COPY_ENV_SENS_SERVICE_UUID(uuid_struct)  COPY_UUID_128(uuid_struct,0x42,0x82,0x1a,0x40, 0xe4,0x77, 0x11,0xe2, 0x82,0xd0, 0x00,0x02,0xa5,0xd5,0xc5,0x1b)
  #define COPY_TEMP_CHAR_UUID(uuid_struct)         COPY_UUID_128(uuid_struct,0xa3,0x2e,0x55,0x20, 0xe4,0x77, 0x11,0xe2, 0xa9,0xe3, 0x00,0x02,0xa5,0xd5,0xc5,0x1b)
  #define COPY_PRESS_CHAR_UUID(uuid_struct)        COPY_UUID_128(uuid_struct,0xcd,0x20,0xc4,0x80, 0xe4,0x8b, 0x11,0xe2, 0x84,0x0b, 0x00,0x02,0xa5,0xd5,0xc5,0x1b)
  #define COPY_HUMIDITY_CHAR_UUID(uuid_struct)     COPY_UUID_128(uuid_struct,0x01,0xc5,0x0b,0x60, 0xe4,0x8c, 0x11,0xe2, 0xa0,0x73, 0x00,0x02,0xa5,0xd5,0xc5,0x1b)

  // Time service: uuid = 0x08, 0x36, 0x6e, 0x80, 0xcf, 0x3a, 0x11, 0xe1, 0x9a, 0xb4, 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b
  //      straight uuid = 0x08366e80cf3a11e19ab40002a5d5c51b
  /*#define COPY_TIME_SERVICE_UUID(uuid_struct)  COPY_UUID_128(uuid_struct,0x08,0x36,0x6e,0x80, 0xcf,0x3a, 0x11,0xe1, 0x9a,0xb4, 0x00,0x02,0xa5,0xd5,0xc5,0x1b)
  #define COPY_TIME_UUID(uuid_struct)          COPY_UUID_128(uuid_struct,0x09,0x36,0x6e,0x80, 0xcf,0x3a, 0x11,0xe1, 0x9a,0xb4, 0x00,0x02,0xa5,0xd5,0xc5,0x1b)
  #define COPY_MINUTE_UUID(uuid_struct)        COPY_UUID_128(uuid_struct,0x0a,0x36,0x6e,0x80, 0xcf,0x3a, 0x11,0xe1, 0x9a,0xb4, 0x00,0x02,0xa5,0xd5,0xc5,0x1b)
*/
  #define COPY_COUNT_SERVICE_UUID(uuid_struct) COPY_UUID_128(uuid_struct,0xc6,0x09,0xb3,0xc3,0x09,0xf8,0x11,0xe7,0x53,0x9a,0x00,0x02,0xa5,0xd5,0xc5,0x1b)
  #define COPY_COUNT_UUID(uuid_struct) 		   COPY_UUID_128(uuid_struct,0x9a,0xb6,0x73,0x9c,0x00,0x65,0x11,0xe7,0x11,0xd7,0x00,0x02,0xa5,0xd5,0xc5,0x1b)

  #define COPY_LED_SERVICE_UUID(uuid_struct)  COPY_UUID_128(uuid_struct,0xaf,0xce,0xb8,0xe0,0x03,0x77,0x11,0xe0,0xa5,0xc2,0x00,0x02,0xa5,0xd5,0xc5,0x1b)
  #define COPY_LED_UUID(uuid_struct)          COPY_UUID_128(uuid_struct,0xa4,0xc3,0xff,0xc1,0xaa,0x17,0x11,0xe0,0x5a,0xba,0x00,0x02,0xa5,0xd5,0xc5,0x1b)

  #define COPY_MOTION_SERVICE_UUID(uuid_struct) COPY_UUID_128(uuid_struct,0xac,0x59,0xaf,0x24,0x78,0x19,0x11,0xe3,0x9c,0x62,0x00,0x02,0xa5,0xd5,0xc5,0x1b)
  #define COPY_INC_UUID(uuid_struct) 		COPY_UUID_128(uuid_struct,0x53,0xfc,0xb3,0x92,0x10,0x29,0x11,0xe3,0x63,0x90,0x00,0x02,0xa5,0xd5,0xc5,0x1b)
  #define COPY_UPDOWN_UUID(uuid_struct) 	COPY_UUID_128(uuid_struct,0xfb,0x35,0x09,0x7d,0x67,0x23,0x11,0xe3,0xf4,0x56,0x00,0x02,0xa5,0xd5,0xc5,0x1b)

/* Store Value into a buffer in Little Endian Format */
#define STORE_LE_16(buf, val)    ( ((buf)[0] =  (uint8_t) (val)    ) , \
                                   ((buf)[1] =  (uint8_t) (val>>8) ) )

/* Private variables ---------------------------------------------------------*/
int connected = FALSE;
volatile uint8_t set_connectable = 1;
volatile uint16_t connection_handle = 0;
AxesRaw_t axes_data;
uint16_t sampleServHandle, TXCharHandle, RXCharHandle;
uint16_t accServHandle, accCharHandle;
uint16_t envSensServHandle, tempCharHandle, pressCharHandle, humidityCharHandle;
uint16_t countServHandle, countCharHandle;
uint16_t ledServHandle, ledButtonCharHandle;
uint16_t motionServHandle, incCharHandle, updownCharHandle;
uint8_t ledState = 0;
tClockTime notifyTime = 0;
tClockTime notifyMotion = 0;
int countAv = 0;

/////////////////////////////////////////////////////////////////////
/////////////////////////SERVICES////////////////////////////////////
/////////////////////////////////////////////////////////////////////
tBleStatus Add_Acc_Service(void)
{
  tBleStatus ret;

  uint8_t uuid[16];

  COPY_ACC_SERVICE_UUID(uuid);
  ret = aci_gatt_add_serv(UUID_TYPE_128,  uuid, PRIMARY_SERVICE, 7,
                          &accServHandle);
  if (ret != BLE_STATUS_SUCCESS) goto fail;

  COPY_ACC_UUID(uuid);
  ret =  aci_gatt_add_char(accServHandle, UUID_TYPE_128, uuid, 6,
		  CHAR_PROP_READ|CHAR_PROP_NOTIFY,
                           ATTR_PERMISSION_NONE,
                           GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                           16, 0, &accCharHandle);
  if (ret != BLE_STATUS_SUCCESS) goto fail;

  PRINTF("Service ACC added. Handle 0x%04X, Acc Charac handle: 0x%04X\n",accServHandle, accCharHandle);
  return BLE_STATUS_SUCCESS;

fail:
  PRINTF("Error while adding ACC service.\n");
  return BLE_STATUS_ERROR ;

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

  tBleStatus ret;
  uint8_t uuid[16];

  /* copy "LED service UUID" defined above to 'uuid' local variable */
  COPY_LED_SERVICE_UUID(uuid);
  /*
   * now add "LED service" to GATT server, service handle is returned
   * via 'ledServHandle' parameter of aci_gatt_add_serv() API.
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
  */
  ret =  aci_gatt_add_char(ledServHandle, UUID_TYPE_128, uuid, 1,
		  CHAR_PROP_READ|CHAR_PROP_WRITE, ATTR_PERMISSION_NONE, GATT_NOTIFY_ATTRIBUTE_WRITE|GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                           16, 0, &ledButtonCharHandle);
  if (ret != BLE_STATUS_SUCCESS) goto fail;

  PRINTF("Service LED BUTTON added. Handle 0x%04X, LED button Charac handle: 0x%04X\n",ledServHandle, ledButtonCharHandle);
  return BLE_STATUS_SUCCESS;

fail:
  PRINTF("Error while adding LED service.\n");
  return BLE_STATUS_ERROR;
}

tBleStatus Add_Motion_Service(void)
{

  tBleStatus ret;
  uint8_t uuid[16];

  COPY_MOTION_SERVICE_UUID(uuid);

  ret = aci_gatt_add_serv(UUID_TYPE_128, uuid, PRIMARY_SERVICE, 7,
                          &motionServHandle);
  if (ret != BLE_STATUS_SUCCESS) goto fail;

  COPY_INC_UUID(uuid);
  ret =  aci_gatt_add_char(motionServHandle, UUID_TYPE_128, uuid, 4,
		  CHAR_PROP_READ|CHAR_PROP_NOTIFY, ATTR_PERMISSION_NONE, GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                           16, 0, &incCharHandle);
  if (ret != BLE_STATUS_SUCCESS) goto fail;

  COPY_UPDOWN_UUID(uuid);
   ret =  aci_gatt_add_char(motionServHandle, UUID_TYPE_128, uuid, 1,
		   CHAR_PROP_NOTIFY, ATTR_PERMISSION_NONE, GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                            16, 0, &updownCharHandle);
   if (ret != BLE_STATUS_SUCCESS) goto fail;

  PRINTF("Service MOTION added. Handle 0x%04X, inclinaison Charac handle: 0x%04X\n, updown Charac handle: 0x%04X\n",motionServHandle, incCharHandle, updownCharHandle);
  return BLE_STATUS_SUCCESS;

fail:
  PRINTF("Error while adding MOTION service.\n");
  return BLE_STATUS_ERROR;
}

tBleStatus Add_Count_Service(void)
{
  tBleStatus ret;

  uint8_t uuid[16];

  COPY_COUNT_SERVICE_UUID(uuid);
  ret = aci_gatt_add_serv(UUID_TYPE_128,  uuid, PRIMARY_SERVICE, 7,
                          &countServHandle);
  if (ret != BLE_STATUS_SUCCESS) goto fail;

  COPY_COUNT_UUID(uuid);
  ret =  aci_gatt_add_char(countServHandle, UUID_TYPE_128, uuid, 2,
                           CHAR_PROP_NOTIFY|CHAR_PROP_READ,
                           ATTR_PERMISSION_NONE,
                           GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                           16, 0, &countCharHandle);
  if (ret != BLE_STATUS_SUCCESS) goto fail;

  PRINTF("Service COUNT added. Handle 0x%04X, Count Charac handle: 0x%04X\n",countServHandle, countCharHandle);
  return BLE_STATUS_SUCCESS;

fail:
  PRINTF("Error while adding COUNT service.\n");
  return BLE_STATUS_ERROR ;

}
////////////////////////////////////////////////////////////////////
///////////////////////BLE FUNCTIONS////////////////////////////////
////////////////////////////////////////////////////////////////////
void BLE_Common_Init(void)
{
	const char *name = "Team2";
	//This avoid to clear the cache on some Android device
#ifdef BLUENRG_MS
	uint8_t SERVER_BDADDR[] =
	{	0x12, 0x34, 0x00, 0xE1, 0x80, 0x02};
#else
	uint8_t SERVER_BDADDR[] = { 0xCC, 0x45, 0x4C, 0x45, 0x00, 0x02 };
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
	if (ret) {
		DEBUG_LINE("Setting BD_ADDR failed.\n");
	}

	ret = aci_gatt_init();
	if (ret) {
		DEBUG_LINE("GATT_Init failed.\n");
	}

#ifdef BLUENRG_MS
	ret = aci_gap_init(GAP_PERIPHERAL_ROLE, 0, 0x07, &service_handle, &dev_name_char_handle, &appearance_char_handle);
#else
	ret = aci_gap_init(GAP_PERIPHERAL_ROLE, &service_handle,
			&dev_name_char_handle, &appearance_char_handle);
#endif

	if (ret != BLE_STATUS_SUCCESS) {
		DEBUG_LINE("GAP_Init failed.\n");
	}

	ret = aci_gatt_update_char_value(service_handle, dev_name_char_handle, 0,
			strlen(name), (uint8_t *) name);

	if (ret) {
		DEBUG_LINE("aci_gatt_update_char_value failed.\n");
		while (1)
			;
	}

	ret = aci_gap_set_auth_requirement(MITM_PROTECTION_REQUIRED,
	OOB_AUTH_DATA_ABSENT,
	NULL, 7, 16,
	USE_FIXED_PIN_FOR_PAIRING, 123456,
	BONDING);
	if (ret == BLE_STATUS_SUCCESS) {
		DEBUG_LINE("BLE Stack Initialized.\n");
	}

	DEBUG_LINE("SERVER: BLE Stack Initialized\n");

	/* Instantiate Accelerometer Service */
	ret = Add_Acc_Service();
	if (ret == BLE_STATUS_SUCCESS)
		DEBUG_LINE("Acc service added successfully.\n");
	else
		DEBUG_LINE("Error while adding Acc service.\n");

	/* Instantiate Environmental Service */
	ret = Add_Environmental_Sensor_Service();
	if (ret == BLE_STATUS_SUCCESS)
		DEBUG_LINE("Environmental Sensor service added successfully.\n");
	else
		DEBUG_LINE("Error while adding Environmental Sensor service.\n");

	/* Instantiate LED Service */
	ret = Add_LED_Service();
	if (ret == BLE_STATUS_SUCCESS)
		DEBUG_LINE("LED service added successfully.\n");
	else
		DEBUG_LINE("Error while adding LED service.\n");

	/* Instantiate Count Service */
		ret = Add_Count_Service();
		if (ret == BLE_STATUS_SUCCESS)
		DEBUG_LINE("COUNT service added successfully.\n");
	else
		DEBUG_LINE("Error while adding Count service.\n");

	/* Instantiate Motion Service */
	ret = Add_Motion_Service();
	if (ret == BLE_STATUS_SUCCESS)
		DEBUG_LINE("MOTION service added successfully.\n");
	else
		DEBUG_LINE("Error while adding Motion service.\n");

	/* Set output power level */
	ret = aci_hal_set_tx_power_level(1, 4);
}

void BLE_Common_Process(void)
{
	HCI_Process();
	Notify_Process(&axes_data);
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
	/* réinitialisation nb de fois appui bouton */
	count = 0;

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
	if (handle == accCharHandle + 1) {
		Mems_StartReadSensors(100, ACCELEROMETER_SENSOR);
		(&axes_data)->AXIS_X = acc_xn;
		(&axes_data)->AXIS_Y = acc_yn;
		(&axes_data)->AXIS_Z = acc_zn;
		DEBUG_LINE("ACC: X=%6d Y=%6d Z=%6d\r\n", (&axes_data)->AXIS_X,
				(&axes_data)->AXIS_Y, (&axes_data)->AXIS_Z);
		Acc_Update((AxesRaw_t*) &axes_data);
	} else if (handle == tempCharHandle + 1) {
		Mems_StartReadSensors(100, TEMPERATURE_SENSOR);
		DEBUG_LINE("Temperature : %d.%02d C", (int )temp1n, (int )temp2n);
		int temp1 = (int) temp1n;
		int temp2 = (int) temp2n;
		int16_t data;
		data = (int16_t) (temp1 * 100 + temp2);
		Temp_Update(data);
	} else if (handle == pressCharHandle + 1) {
		Mems_StartReadSensors(100, PRESSURE_SENSOR);
		DEBUG_LINE("Pression : %d.%02d hPa", (int ) press1n, (int ) press2n);
		int press1 = (int) press1n;
		int press2 = (int) press2n;
		int32_t data;
		data = (int32_t) (press1 * 100 + press2);
		Press_Update(data);
	} else if (handle == humidityCharHandle + 1) {
		Mems_StartReadSensors(100, HUMIDITY_SENSOR);
		DEBUG_LINE("HUM: %d.%02d", (int ) hum1n, (int ) hum2n);
		int hum1 = (int) hum1n;
		int hum2 = (int) hum2n;
		uint16_t data;
		data = (uint16_t) (hum1 * 100 + hum2);
		Humidity_Update(data);
	} else if (handle == ledButtonCharHandle + 1) {
		if(ledState==0) DEBUG_LINE("Read Led : %d => 0xFF", (int)ledState);
		else DEBUG_LINE("Read Led : %d => 0x7F", (int)ledState);
		Led_Update(ledState);
	}else if (handle == countCharHandle + 1){
		DEBUG_LINE("Read Count : %d",(int)count);
		Count_Update(count);
	}else if(handle == incCharHandle + 1){
		//byte 1 : left/right axis inclination side (none: 0, left: 1 , right: 2)
		//byte 2 : left/right axis inclination degree (none: 0, medium: 1 , high: 2)
		//byte 3 : back/front axis inclination side (none: 0, back: 1 , front: 2)
		//byte 4 : back/front axis inclination degree (none: 0, medium: 1 , high: 2)
		uint32_t inc;
		Mems_StartReadSensors(100, ACCELEROMETER_SENSOR);
		if(fabs(acc_yn)<167) inc = 0;
		else if(fabs(acc_yn-333)<167 || fabs(acc_yn+333)<167) inc = 1;
		else inc = 2;
		inc = inc<<8;
		if(fabs(acc_yn)<167) inc = inc + 0;
		else if(acc_yn>167) inc = inc + 1;
		else inc = inc + 2;
		inc = inc<<8;
		if(fabs(acc_xn)<167) inc = inc + 0;
		else if(fabs(acc_xn-333)<167 || fabs(acc_xn+333)<167) inc = inc + 1;
		else inc = inc + 2;
		inc = inc<<8;
		if(fabs(acc_xn)<167) inc = inc + 0;
		else if(acc_xn>167) inc = inc + 1;
		else inc = inc + 2;
		DEBUG_LINE("Read Motion : %d", inc);
		Inc_Update(inc);
	}

	//EXIT:
	if (connection_handle != 0)
		aci_gatt_allow_read(connection_handle);
}

void Write_Request_CB(uint16_t handle, uint8_t *data, uint16_t length)
{
	//This Callback is called when a GATT Client wants to write an attribute
	DEBUG_LINE("Write test");
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


/////////////////////////////////////////////////////////////////////
/////////////////////////////UPDATE//////////////////////////////////
/////////////////////////////////////////////////////////////////////
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

void Led_Update(uint8_t led)
{
  tBleStatus ret;

  ret = aci_gatt_update_char_value(ledServHandle, ledButtonCharHandle, 0, 1,
                                   (uint8_t*)&led);

  if (ret != BLE_STATUS_SUCCESS){
    PRINTF("Error while updating Led characteristic.\n") ;

  }

}

void Count_Update(uint16_t count)
{
  tBleStatus ret;

  ret = aci_gatt_update_char_value(countServHandle, countCharHandle, 0, 2,
                                   (uint8_t*)&count);

  if (ret != BLE_STATUS_SUCCESS){
    PRINTF("Error while updating Count characteristic.\n") ;

  }

}

void Attribute_Modified_CB(uint16_t handle, uint8_t data_length, uint8_t *att_data)
{
  /* Writing a value on this characteristic changes the state of the LED (on or off) */
  if(handle == ledButtonCharHandle + 1){
      BSP_LED_Toggle(LED2);
      DEBUG_LINE("Led Toggle");
      if(ledState == 0) ledState = 1;
      else ledState = 0;
  }
}

void Inc_Update(uint32_t inc)
{
  tBleStatus ret;

  ret = aci_gatt_update_char_value(motionServHandle, incCharHandle, 0, 4,
                                   (uint8_t*)&inc);

  if (ret != BLE_STATUS_SUCCESS){
    PRINTF("Error while updating Inclination characteristic.\n") ;

  }

}

/////////////////////////////////////////////////////////////////////
/////////////////////////OTHER FUNCTIONS/////////////////////////////
/////////////////////////////////////////////////////////////////////
void Notify_Process(AxesRaw_t* p_axes) {
	if (connected && (int) (Clock_Time() - notifyTime) > 500) {
		notifyTime = Clock_Time();
		Mems_StartReadSensors(500, ACCELEROMETER_SENSOR);
		p_axes->AXIS_X = acc_xn;
		p_axes->AXIS_Y = acc_yn;
		p_axes->AXIS_Z = acc_zn;
		Acc_Update(p_axes);
	}

	if(connected && countAv<count){
		countAv = count;
		DEBUG_LINE("Notify Count : %d",count);
		Count_Update(count);
	}
	if (connected && (int) (Clock_Time() - notifyMotion) > 500) {
		notifyMotion = Clock_Time();
		//byte 1 : left/right axis inclination side (none: 0, left: 1 , right: 2)
		//byte 2 : left/right axis inclination degree (none: 0, medium: 1 , high: 2)
		//byte 3 : back/front axis inclination side (none: 0, back: 1 , front: 2)
		//byte 4 : back/front axis inclination degree (none: 0, medium: 1 , high: 2)
		uint32_t inc;
		Mems_StartReadSensors(500, ACCELEROMETER_SENSOR);
		if (fabs(acc_yn) < 167)
			inc = 0;
		else if (fabs(acc_yn - 333) < 167 || fabs(acc_yn + 333) < 167)
			inc = 1;
		else
			inc = 2;
		inc = inc << 8;
		if (fabs(acc_yn) < 167)
			inc = inc + 0;
		else if (acc_yn > 167)
			inc = inc + 1;
		else
			inc = inc + 2;
		inc = inc << 8;
		if (fabs(acc_xn) < 167)
			inc = inc + 0;
		else if (fabs(acc_xn - 333) < 167 || fabs(acc_xn + 333) < 167)
			inc = inc + 1;
		else
			inc = inc + 2;
		inc = inc << 8;
		if (fabs(acc_xn) < 167)
			inc = inc + 0;
		else if (acc_xn > 167)
			inc = inc + 1;
		else
			inc = inc + 2;
		Inc_Update(inc);
	}
}
