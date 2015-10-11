/*
 * motion.c
 *
 *  Created on: Sep 25, 2015
 *      Author: maxime
 */

#include "motion.h"
#include "debug.h"
#include "stm32f4xx_nucleo.h"

void Motion_Init(void) {

}

void Motion_Process(void) {

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
