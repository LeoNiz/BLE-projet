#include "ele410_ptototype.h"
#include "link_layer.h"
#include "gp_timer.h"
#include "debug.h"

static tClockTime time;

void ELE410_Prototype_Init(void)
{

}

void ELE410_Prototype_Process(void)
{

}

void Button_Button_Long_Pressed_CB(void)
{

	BLE_Common_Set_Discoverable();
	gp_timer_t timer;
		//Timer_Set(&timer,interval);
		tClockTime interval = 10000;
		int delay = (int) (Clock_Time()-time);
	DEBUG_LINE("reste : %d",(int)delay);
	//if(delay>interval)
		DEBUG_LINE("reste : %d",(int)delay);
		//aci_gap_set_undirected_connectable(PUBLIC_ADDR,ADV_IND);
		//aci_gap_set_undirected_connectable(NO_WHITE_LIST_USE ,PUBLIC_ADDR);
		aci_gap_set_undirected_connectable(0x03,0x00);

}
