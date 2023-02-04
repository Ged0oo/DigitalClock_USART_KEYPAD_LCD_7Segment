/* 
 * File:   ecu_dc_motor.h
 * Author: Ahmed.Elghafar
 * https://www.linkedin.com/in/ahmedabdelghafarmohammed/
 * Created on January 8, 2021, 10:48 AM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

/* ----------------- Includes -----------------*/
#include "ecu_dc_motor_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* ----------------- Macro Declarations -----------------*/
#define DC_MOTOR_ON_STATUS  0x01U
#define DC_MOTOR_OFF_STATUS 0x00U

#define DC_MOTOR_PIN1 0x00U
#define DC_MOTOR_PIN2 0x01U

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef struct{
    pin_config_t dc_motor_pin[2];
}dc_motor_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType dc_motor_initialize(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_move_left(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor);

#endif	/* ECU_DC_MOTOR_H */

