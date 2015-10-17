#include "ele410_ptototype.h"
#include "link_layer.h"
#include "gp_timer.h"
#include "debug.h"
#include "ble_common.h"

static tClockTime time;
static bleActive;
static int connect;
const DELAY = 10000;

void ELE410_Prototype_Init(void)
{
	bleActive = 0;
	connect = 0;
}

void ELE410_Prototype_Process(void)
{
	Disable_BLE();
}

void Button_Button_Long_Pressed_CB(void)
{
	connect = 0;
	bleActive = 1;
	time = Clock_Time();
	/*Lance le discoverable mode*/
	BLE_Common_Set_Discoverable();
}

void Disable_BLE(void)
{
	if(bleActive==1 && connect==0 && Clock_Time()-time>DELAY){
			bleActive=0;
			BLE_Common_Init();
		}
}
