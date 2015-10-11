/*
 * motion.h
 *
 *  Created on: Sep 25, 2015
 *      Author: maxime
 */

#ifndef MOTION_H_
#define MOTION_H_

void Motion_Init(void);
void Motion_Process(void);

void Motion_InclinationLeftRightAxisNone_CB(void);
void Motion_InclinationLeftRightAxisLeftMedium_CB(void);
void Motion_InclinationLeftRightAxisLeftHigh_CB(void);
void Motion_InclinationLeftRightAxisRightMedium_CB(void);
void Motion_InclinationLeftRightAxisRightHigh_CB(void);
void Motion_InclinationBackFrontAxisNone_CB(void);
void Motion_InclinationBackFrontAxisBackMedium_CB(void);
void Motion_InclinationBackFrontAxisBackHigh_CB(void);
void Motion_InclinationBackFrontAxisFrontMedium_CB(void);
void Motion_InclinationBackFrontAxisFrontHigh_CB(void);

void Motion_MoveUp_CB(void);
void Motion_MoveDown_CB(void);

#endif /* MOTION_H_ */
