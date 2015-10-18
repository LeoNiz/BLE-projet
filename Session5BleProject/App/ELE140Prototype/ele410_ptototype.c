#include "ele410_ptototype.h"
#include "link_layer.h"
#include "gp_timer.h"
#include "debug.h"
#include "ble_common.h"

#include "bluenrg_gatt_server.h"
#include "bluenrg_gap.h"

static tClockTime time;
static bleActive;
const DELAY = 120000;
int conn = 0;

uint16_t accServHandle, freeFallCharHandle, accCharHandle;
typedef struct {
  int AXIS_X;
  int AXIS_Y;
  int AXIS_Z;
} AxesRaw_t;
extern AxesRaw_t axes_data = {0,0,0};

void ELE410_Prototype_Init(void)
{
	/*Initialement le BLE n'est pas actif*/
	bleActive=0;
	//Add_Acc_Service();
}

void ELE410_Prototype_Process(void)
{
	Disable_BLE();
	User_Process(&axes_data);
}

void Button_Button_Long_Pressed_CB(void)
{
	time = Clock_Time();
	/*Lance le discoverable mode*/
	BLE_Common_Set_Discoverable();
	int conn=1;
	/*BLE maintenant actif*/
	bleActive = 1;
	DEBUG_LINE("VOUS AVEZ %d s POUR VOUS CONNECTER", (int) DELAY/1000);
}

void Disable_BLE(void)
{
	int tempsEcoulee = (int) Clock_Time()-time;
	/*Si le BLE est activé et que le délai de connexion est expiré,
	 * la découverte est désactivé*/
	if(bleActive==1 && tempsEcoulee>DELAY){
		DEBUG_LINE("J'ESPERE QUE VOUS ETES DEJA CONNECTE");
		aci_gap_set_non_discoverable();
		bleActive = 0;
		}
}

tBleStatus Add_Acc_Service(void)
{
  tBleStatus ret;

  uint8_t uuid[16];

  COPY_ACC_SERVICE_UUID(uuid);
  ret = aci_gatt_add_serv(UUID_TYPE_128,  uuid, PRIMARY_SERVICE, 7,
                          &accServHandle);
  if (ret != BLE_STATUS_SUCCESS) goto fail;

  COPY_FREE_FALL_UUID(uuid);
  ret =  aci_gatt_add_char(accServHandle, UUID_TYPE_128, uuid, 1,
                           CHAR_PROP_NOTIFY, ATTR_PERMISSION_NONE, 0,
                           16, 0, &freeFallCharHandle);
  if (ret != BLE_STATUS_SUCCESS) goto fail;

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
  /*if(set_connectable){
    setConnectable();
    set_connectable = FALSE;
  }*/

  /* Check if the user has pushed the button */
  if(BSP_PB_GetState(BUTTON_KEY) == RESET)
  {
    while (BSP_PB_GetState(BUTTON_KEY) == RESET);

    //BSP_LED_Toggle(LED2); //used for debugging (BSP_LED_Init() above must be also enabled)

    //if(connected)
    if(conn==1)
    {
      /* Update acceleration data */
      p_axes->AXIS_X += 100;
      p_axes->AXIS_Y += 100;
      p_axes->AXIS_Z += 100;
      //DEBUG_LINE("ACC: X=%6d Y=%6d Z=%6d\r\n", p_axes->AXIS_X, p_axes->AXIS_Y, p_axes->AXIS_Z);
      //Acc_Update(p_axes);
    }
  }
}

/*tBleStatus Acc_Update(AxesRaw_t *data)
{
  tBleStatus ret;
  uint8_t buff[6];

  STORE_LE_16(buff,data->AXIS_X);
  STORE_LE_16(buff+2,data->AXIS_Y);
  STORE_LE_16(buff+4,data->AXIS_Z);

  ret = aci_gatt_update_char_value(accServHandle, accCharHandle, 0, 6, buff);

  if (ret != BLE_STATUS_SUCCESS){
    PRINTF("Error while updating ACC characteristic.\n") ;
    //return BLE_STATUS_ERROR ;
  }
  //return BLE_STATUS_SUCCESS;
}*/

void Update_Time_Characteristics(void) {
  /* update "seconds and minutes characteristics" of time service */
  Seconds_Update();
  Minutes_Notify();
}


