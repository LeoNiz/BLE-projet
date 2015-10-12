/*
 * motion.c
 *
 *  Created on: Sep 25, 2015
 *      Author: maxime
 */

#include "motion.h"
#include "debug.h"
#include "stm32f4xx_nucleo.h"
#include "mems.h"

void Motion_Init(void) {
	Mems_StartReadSensors(10, ACCELEROMETER_SENSOR);
}

void Motion_Process(void) {

}

void Mems_Acc_CB(int32_t acc_x, int32_t acc_y, int32_t acc_z) {
	int angle30 = 1000/3;
	int angle60 = 1000/3*2;
	int dec = 100;
	/*Inclinaison gauche/droite*/
	if(fabs(acc_x)<dec) Motion_InclinationLeftRightAxisNone_CB();
	if (fabs(acc_x-angle30)<dec) Motion_InclinationLeftRightAxisLeftMedium_CB();
	if (fabs(acc_x-angle60)<dec) Motion_InclinationLeftRightAxisLeftHigh_CB();
	if (fabs(acc_x+angle30)<dec) Motion_InclinationLeftRightAxisRightMedium_CB();
	if (fabs(acc_x+angle60)<dec) Motion_InclinationLeftRightAxisRightHigh_CB();
	/*Inclinaison avant/arrière*/
	if (fabs(acc_y)<dec) Motion_InclinationBackFrontAxisNone_CB();
	if (fabs(acc_y-angle30)<dec) Motion_InclinationBackFrontAxisBackMedium_CB();
	if (fabs(acc_y-angle60)<dec) Motion_InclinationBackFrontAxisBackHigh_CB();
	if (fabs(acc_y+angle30)<dec) Motion_InclinationBackFrontAxisFrontMedium_CB();
	if (fabs(acc_y+angle60)<dec) Motion_InclinationBackFrontAxisFrontHigh_CB();
}

__weak void Motion_InclinationLeftRightAxisNone_CB(void) {
	DEBUG_LINE("Inclination axis left right : none");
}

__weak void Motion_InclinationLeftRightAxisLeftMedium_CB(void) {
	DEBUG_LINE("Inclination axis left right : left medium");
}

__weak void Motion_InclinationLeftRightAxisLeftHigh_CB(void) {
	DEBUG_LINE("Inclination axis left right : left high");
}

__weak void Motion_InclinationLeftRightAxisRightMedium_CB(void) {
	DEBUG_LINE("Inclination axis left right : right medium");
}

__weak void Motion_InclinationLeftRightAxisRightHigh_CB(void) {
	DEBUG_LINE("Inclination axis left right : right high");
}

__weak void Motion_InclinationBackFrontAxisNone_CB(void) {
	DEBUG_LINE("Inclination axis back front : none");
}

__weak void Motion_InclinationBackFrontAxisBackMedium_CB(void) {
	DEBUG_LINE("Inclination axis back front : back medium");
}

__weak void Motion_InclinationBackFrontAxisBackHigh_CB(void) {
	DEBUG_LINE("Inclination axis back front : back high");
}

__weak void Motion_InclinationBackFrontAxisFrontMedium_CB(void) {
	DEBUG_LINE("Inclination axis back front : front medium");
}

__weak void Motion_InclinationBackFrontAxisFrontHigh_CB(void) {
	DEBUG_LINE("Inclination axis back front : front High");
}

__weak void Motion_MoveUp_CB(void) {
	DEBUG_LINE("Motion : Move Up");
}

__weak void Motion_MoveDown_CB(void) {
	DEBUG_LINE("Motion : Move Down");
}
