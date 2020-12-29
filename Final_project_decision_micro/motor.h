/*
 * motor.h
 *
 *  Created on: 10/10/2020
 *      Author: Omar Hany
 */




#ifndef MOTOR_H_
#define MOTOR_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"
#include "pwm.h"


#define DIR1 PB0
#define DIR2 PB1
#define PWM PB3
#define MOTOR_R PORTB
#define MOTOR_ctl DDRB

void MOTOR_stop();
void MOTOR_clockwise();
void MOTOR_anticlockwise();
void MOTOR_toggle();
void MOTOR_init();













#endif
