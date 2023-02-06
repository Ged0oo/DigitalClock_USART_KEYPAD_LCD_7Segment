/* 
 * File:   ecu_seven_segment.c
 * Author: Mohamed_Nagy
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on January 27, 2022, 8:41 PM
 */
 

#ifndef ULTRASONIC_H
#define	ULTRASONIC_H

#include "Ultrasonic_Cfg.h"

#define SOUND_SPEED_CM_SECOND       34000

typedef struct{
    pin_config_t Trigger_Pin;
    pin_config_t Echo_Pin; 
}ultrasonic_t;

Std_ReturnType Ultrasonic_Init(const ultrasonic_t *_config);
Std_ReturnType Ultrasonic_Calculate_Distance(const ultrasonic_t *_config, uint16 *Distance);

#endif	/* ULTRASONIC_H */

