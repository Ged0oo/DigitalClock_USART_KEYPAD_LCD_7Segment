/* 
 * File:   ecu_keypad.h
 * Author: Ahmed.Elghafar
 * https://www.linkedin.com/in/ahmedabdelghafarmohammed/
 * Created on February 6, 2021, 2:23 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/* ----------------- Includes -----------------*/
#include "ecu_keypad_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* ----------------- Macro Declarations -----------------*/
#define ECU_KEYPAD_ROWS    4
#define ECU_KEYPAD_COLUMNS 4 

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef struct{
    pin_config_t keypad_row_pins[ECU_KEYPAD_ROWS];
    pin_config_t keypad_columns_pins[ECU_KEYPAD_COLUMNS];
}keypad_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType keypad_initialize(const keypad_t *_keypad_obj);
Std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *value);

#endif	/* ECU_KEYPAD_H */

