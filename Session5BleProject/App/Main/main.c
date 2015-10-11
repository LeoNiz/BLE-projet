/* Includes ------------------------------------------------------------------*/
#include "cube_hal.h"
#include "stm32_bluenrg_ble.h"
#include "debug.h"
#include "led.h"
#include "button.h"
#include "ble_common.h"
#include "mems.h"
#include "motion.h"

int main(void)
{
	HAL_Init();
	SystemClock_Config();

	/* Initialize LED manager*/
	Led_Init();
	/* Initialize Button manager*/
	Button_Init();
	/* Initialize BLE manager*/
	BLE_Common_Init();
	/* Initialize Sensors MEMS manager*/
	Mems_Init();
	/* Initialize Motion Manager */
	Motion_Init();
	/* Initialize ELE 410 Application logic Manager */
	ELE410_Prototype_Init();

	while (1)
	{
		BLE_Common_Process();
		Button_Process();
		Led_Process();
		Mems_Process();
		Motion_Process();
		ELE410_Prototype_Process();
	}
}
