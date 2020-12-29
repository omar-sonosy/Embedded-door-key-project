/*
 * motor.c
 *
 *  Created on: 10/10/2020
 *      Author: Omar Hany
 */




#include "motor.h"

void MOTOR_init(){
	MOTOR_ctl |=(1<<DIR1)|(1<<DIR2);
	PWM_Timer0_Init(255);
}

void MOTOR_stop(){
	CLEAR_BIT(MOTOR_R,DIR1);
	CLEAR_BIT(MOTOR_R,DIR2);
}

void MOTOR_clockwise(){
	CLEAR_BIT(MOTOR_R,DIR1);
	SET_BIT(MOTOR_R,DIR2);
}
void MOTOR_anticlockwise(){
	CLEAR_BIT(MOTOR_R,DIR2);
	SET_BIT(MOTOR_R,DIR1);
}
void MOTOR_toggle(){
	if(!((BIT_IS_CLEAR(MOTOR_R,DIR1)) && (BIT_IS_CLEAR(MOTOR_R,DIR2)))){
		TOGGLE_BIT(MOTOR_R,DIR1);
		TOGGLE_BIT(MOTOR_R,DIR2);
	}
}
