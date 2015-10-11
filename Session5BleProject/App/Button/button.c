#include "gp_timer.h"
#include "button.h"
#include "debug.h"
#include "stm32f4xx_nucleo.h"

static gp_timer_t button_read_timer;
static gp_timer_t button_hold_timer;
static button_event_t button_last_event;

void Button_Init(void)
{
	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);
    Timer_Set(&button_read_timer, 10);
	button_last_event = buttonNone;
}

__weak void Button_Button_Pressed_CB(void)
{
	DEBUG_LINE("Button Pressed");
}

__weak void Button_Button_Released_CB(void)
{
	DEBUG_LINE("Button Released");
}

__weak void Button_Button_Pressed_And_Released_CB(void)
{
	DEBUG_LINE("Button Pressed and Released");
}

__weak void Button_Button_Long_Pressed_CB(void)
{
	DEBUG_LINE("Button Long Pressed");
}

button_event_t Button_Get_Last_Event(void)
{
	return button_last_event;
}

void Button_Process(void)
{
    if (Timer_Expired(&button_read_timer))
    {
        Timer_Restart(&button_read_timer);
		//Button is active low
		if (BSP_PB_GetState(BUTTON_KEY) == SET)
		{
			if (button_last_event != buttonReleased && button_last_event != buttonPressedReleased)
			{
				if (button_last_event == buttonPressed)
				{
					button_last_event = buttonPressedReleased;
					Button_Button_Pressed_And_Released_CB();
				}
				else
				{
					button_last_event = buttonReleased;
					Button_Button_Released_CB();
				}
			}
		}
		else
		{
			switch (button_last_event)
			{
			case buttonReleased:
			case buttonPressedReleased:
				button_last_event = buttonPressed;
				Timer_Set(&button_hold_timer, LONG_PERIOD);
				Button_Button_Pressed_CB();
				break;
			case buttonPressed:
				if (Timer_Time(&button_hold_timer) > LONG_PERIOD)
				{
					button_last_event = buttonLongPressed;
					Button_Button_Long_Pressed_CB();
				}

				break;
			default:
				break;
			}
		}
	}
}
