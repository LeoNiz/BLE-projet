#include "led.h"
#include "gp_timer.h"
#include "debug.h"

gp_timer_t led_blink_period_timer;
gp_timer_t led_blink_duration_timer;
uint16_t led_blink_duration_ms;
uint8_t led_blink_enabled;
uint8_t led_blink_state;

void Led_Init(void)
{
	// TODO : implement this function to initialize the Nucleo board's LED
	BSP_LED_Init(LED2);
	led_blink_enabled = 0;
}

void Led_On(void)
{
	// TODO : implement this function to turn on the LED
	BSP_LED_On(LED2);
}

void Led_Off(void)
{
	// TODO : implement this function to turn off the LED
	BSP_LED_Off(LED2);
	led_blink_enabled = 0;
}

void Led_Blink(uint16_t period_ms, uint16_t duration_ms)
{
	// TODO : implement this function to start the LED blinking process for the required period and duration
	if (period_ms)
	{
		led_blink_enabled = 1;
		led_blink_state = 0;
		Timer_Set(&led_blink_period_timer, period_ms);
		led_blink_duration_ms = duration_ms;
		Timer_Set(&led_blink_duration_timer, led_blink_duration_ms);
	}
	else
	{
		Led_On();
	}
}

void Led_Process(void)
{
	/* TODO : implement this function which will be called by main as often as possible.
	 * This allows us to implement a led blinking in a "threaded" way, allowing us to do some other stuff in other App modules.
	 * This function should return as quickly as possible
	 */
	if (led_blink_enabled)
	{
		if (!led_blink_duration_ms || !Timer_Expired(&led_blink_duration_timer))
		{
			if (Timer_Expired(&led_blink_period_timer))
			{
				Timer_Restart(&led_blink_period_timer);
				if (led_blink_state)
				{
					led_blink_state = 0;
					BSP_LED_Off(LED2);
				}
				else
				{
					led_blink_state = 1;
					BSP_LED_On(LED2);
				}
			}
		}
		else
		{
			Led_Off();
		}
	}

}
