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

static int accAv = -1;

void Motion_Init(void) {
	//Mems_StartReadSensors(10, ACCELEROMETER_SENSOR);
}

void Motion_Process(void) {

}

void CHANGE_Mems_Acc_CB(int32_t acc_x, int32_t acc_y, int32_t acc_z) {


	/*Variables*/
	int acc;
	int angle30 = 1000/3;
	int angle60 = 1000/3*2;
	int dec = 100;
	/*Immobilité par rapport au sol*/
	if(fabs(acc_x)<dec && fabs(acc_y)<dec) acc=0;
	/*Inclinaison gauche/droite*/
	else if (fabs(acc_x-angle30)<dec) acc=1;
	else if (fabs(acc_x-angle60)<dec) acc=2;
	else if (fabs(acc_x+angle30)<dec) acc=3;
	else if (fabs(acc_x+angle60)<dec) acc=4;
	/*Inclinaison avant/arrière*/
	else if (fabs(acc_y-angle30)<dec) acc=6;
	else if (fabs(acc_y-angle60)<dec) acc=7;
	else if (fabs(acc_y+angle30)<dec) acc=8;
	else if (fabs(acc_y+angle60)<dec) acc=9;
	else acc = accAv;

	/*Si le device change d'inclinaison*/
	if(acc!=accAv){
		accAv = acc;
		switch(acc){
		case 0 : Motion_InclinationLeftRightAxisNone_CB();
		Motion_InclinationBackFrontAxisNone_CB(); break;
		case 1 : Motion_InclinationLeftRightAxisLeftMedium_CB(); break;
		case 2 : Motion_InclinationLeftRightAxisLeftHigh_CB(); break;
		case 3 : Motion_InclinationLeftRightAxisRightMedium_CB(); break;
		case 4 : Motion_InclinationLeftRightAxisRightHigh_CB();break;
		case 6 : Motion_InclinationBackFrontAxisBackMedium_CB(); break;
		case 7 : Motion_InclinationBackFrontAxisBackHigh_CB(); break;
		case 8 : Motion_InclinationBackFrontAxisFrontMedium_CB(); break;
		case 9 : Motion_InclinationBackFrontAxisFrontHigh_CB(); break;
		}

	}

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
