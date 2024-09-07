//
// Created by peter on 2024.09.06..
//

#include "hardware/pwm.h"
#include "stdio.h"
#include "pico/stdlib.h"

#ifndef OS_MOTOR_CONTROL_H
#define OS_MOTOR_CONTROL_H

#endif //OS_MOTOR_CONTROL_H


void forward(int second);


/**
 * Sets the GPIOs related to the motor controllers
 * number of gpio | number of pin | purpose
 * front
 * gpio 0 (1)-> front speed control with pwm(ENA)
 * gpio 28 (34) -> front speed control with pwm(ENB)
 *
 * in1 = 1; in2=0 -> forward
 * in1 = 0; in2=1 -> backward
 *
 * gpio 4 (6) -> front directionA(in1)
 * gpio 5 (7) -> front directionA(in2)
 * gpio 27 (32) -> front directionB(in3)
 * gpio 26 (31) -> front directionB(in4)
 *
 * Rear
 * gpio 17 (22) -> Rear speed control with pwm(ENA)
 * gpio 15 (20) -> Rear speed control with pwm(ENB)
 *
 * in1 = 1; in2=0 -> forward
 * in1 = 0; in2=1 -> backward
 *
 *  gpio 16 (21)-> Rear directionA(in1)
 *  gpio 18 (24) -> Rear directionA(in2)
 *  gpio 14 (19) -> Rear directionB(in3)
 *  gpio 13 (17) -> Rear directionB(in4)
 */
void setup_motor_controll_gpio();


/**
 * Makes the robot turn right by spinning the wheels into the opposite direction on each side
 */
void turn_right();