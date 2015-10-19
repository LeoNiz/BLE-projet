#include "ele410_ptototype.h"
#include "link_layer.h"
#include "gp_timer.h"
#include "debug.h"
#include "ble_common.h"

static tClockTime time;
static bleActive;
const int DELAY = 120000;

void ELE410_Prototype_Init(void)
{
	/*Initialement le BLE n'est pas actif*/
	bleActive=0;
}

void ELE410_Prototype_Process(void)
{
	//Disable_BLE();
}

void Button_Button_Long_Pressed_CB(void)
{
	//time = Clock_Time();
	/*Lance le discoverable mode*/
	//BLE_Common_Set_Discoverable();
	/*BLE maintenant actif*/
	//bleActive = 1;
	//DEBUG_LINE("VOUS AVEZ %d s POUR VOUS CONNECTER", (int) DELAY/1000);
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
