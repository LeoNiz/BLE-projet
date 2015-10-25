#include "ele410_ptototype.h"
#include "link_layer.h"
#include "gp_timer.h"
#include "debug.h"
#include "ble_common.h"

static tClockTime time;
int bleActive;
const int DELAY = 120000;

void ELE410_Prototype_Init(void)
{
	/*Initialement le BLE n'est pas actif*/
	bleActive=0;
	count = 0;
}

void ELE410_Prototype_Process(void)
{
	Disable_BLE();
}

///////////////////////////////////////////////////////////////
////////////////////////CONNEXION BLE//////////////////////////
///////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////
////////////////////////BUTTON/////////////////////////////////
///////////////////////////////////////////////////////////////
void Button_Button_Pressed_CB(void)
{
	count=count+1;
}

void Button_Button_Long_Pressed_CB(void)
{
	time = Clock_Time();
	/*Lance le discoverable mode*/
	BLE_Common_Set_Discoverable();
	/*BLE maintenant actif*/
	bleActive = 1;
	DEBUG_LINE("VOUS AVEZ %d s POUR VOUS CONNECTER", (int) DELAY/1000);
}

///////////////////////////////////////////////////////////////
///////////////////////REDEFINITION MEMS///////////////////////
///////////////////////////////////////////////////////////////
//Les fonctions mems recuperent les datas qui sont reinjectees dans les datas du ble_common.h
void Mems_Acc_CB(int32_t acc_x, int32_t acc_y, int32_t acc_z) {
	//DEBUG_LINE("ACC_X: %d, ACC_Y: %d, ACC_Z: %d\n", (int ) acc_x, (int ) acc_y,
			//(int ) acc_z);
	acc_xn = acc_x;
	acc_yn = acc_y;
	acc_zn = acc_z;
}

void Mems_Gyr_CB(int32_t gyr_x, int32_t gyr_y, int32_t gyr_z) {
	//DEBUG_LINE("GYR_X: %d, GYR_Y: %d, GYR_Z: %d\n", (int ) gyr_x, (int ) gyr_y,
			//(int ) gyr_z);
	gyr_xn = gyr_x;
	gyr_yn = gyr_y;
	gyr_zn = gyr_z;
}

void Mems_Mag_CB(int32_t mag_x, int32_t mag_y, int32_t mag_z) {
	DEBUG_LINE("MAG_X: %d, MAG_Y: %d, MAG_Z: %d\n", (int ) mag_x, (int ) mag_y,
			(int ) mag_z);
	mag_xn = mag_x;
	mag_yn = mag_y;
	mag_zn = mag_z;

}

void Mems_Pressure_CB(int32_t d1, int32_t d2) {
	//DEBUG_LINE("Pressure: %d.%02d\n", (int ) d1, (int ) d2);
	press1n = d1;
	press2n = d2;
}

void Mems_Hum_CB(int32_t d1, int32_t d2) {
	//DEBUG_LINE("HUM: %d.%02d\n", (int ) d1, (int ) d2);
	hum1n = d1;
	hum2n = d2;
}

void Mems_Temp_CB(int32_t d1, int32_t d2) {
	//DEBUG_LINE("TEMP: %d.%02d\n", (int ) d1, (int ) d2);
	temp1n = d1;
	temp2n = d2;
}
