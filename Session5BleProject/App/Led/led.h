#ifndef LED_H_
#define LED_H_

#include "stm32f4xx_nucleo.h"

void Led_Init(void);
void Led_On(void);
void Led_Off(void);
void Led_Blink(uint16_t period_ms, uint16_t duration_ms);
void Led_Process(void);

#endif /* LED_H_ */
