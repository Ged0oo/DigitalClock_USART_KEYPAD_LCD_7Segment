/* 
 * File:   ecu_dc_motor.c
 * Author: Ahmed.Elghafar
 * https://www.linkedin.com/in/ahmedabdelghafarmohammed/
 * Created on January 8, 2021, 10:48 AM
 */

#include "ecu_dc_motor.h"

/**
 * @brief Initialize the assigned pins to be OUTPUT and turn the motor OFF or ON.
 * @param _dc_motor pointer to the motor configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_initialize(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
        ret = E_NOT_OK;
    }
    else{    
        gpio_pin_intialize(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]));
        gpio_pin_intialize(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]));
    }
    return ret;
}

/**
 * @brief Move the motor to the right direction
 * @param _dc_motor pointer to the motor configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_HIGH);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_LOW);
    }
    return ret;
}

/**
 * @brief Move the motor to the left direction
 * @param _dc_motor pointer to the motor configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_move_left(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_LOW);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_HIGH);
    }
    return ret;
}

/**
 * @brief stop the motor movement
 * @param _dc_motor pointer to the motor configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_LOW);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_LOW);
    }
    return ret;
}
