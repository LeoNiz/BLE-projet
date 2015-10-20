#ifndef ELE410_PROTOTYPE_H_
#define ELE410_PROTOTYPE_H_

#include "stm32f4xx_nucleo.h"



void ELE410_Prototype_Init(void);
void ELE410_Prototype_Process(void);
void Button_Button_Long_Pressed_CB(void);
/*Desactive la decouverte au bout d'un certain temps (120s)*/
void Disable_BLE(void);

#endif //ELE410_PROTOTYPE_H_
