/* 
 * File:   ecu_relay.c
 * Author: Ahmed.Elghafar
 * https://www.linkedin.com/in/ahmedabdelghafarmohammed/
 * Created on January 7, 2021, 10:22 PM
 */

#include "ecu_relay.h"

/**
 * @brief Initialize the assigned pin to be OUTPUT and turn the relay OFF or ON.
 * @param _relay pointer to the relay module configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType relay_initialize(const relay_t *_relay){
    Std_ReturnType ret = E_OK;
    if(NULL == _relay){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {.port = _relay->relay_port, .pin = _relay->relay_pin,
                                .direction = GPIO_DIRECTION_OUTPUT, .logic = _relay->relay_status};
        gpio_pin_intialize(&pin_obj);
    }
    return ret;
}

/**
 * @brief Turn the relay on
 * @param _relay pointer to the relay module configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType relay_turn_on(const relay_t *_relay){
    Std_ReturnType ret = E_OK;
    if(NULL == _relay){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {.port = _relay->relay_port, .pin = _relay->relay_pin,
                                .direction = GPIO_DIRECTION_OUTPUT, .logic = _relay->relay_status};
        gpio_pin_write_logic(&pin_obj , GPIO_HIGH);
    }
    return ret;
}

/**
 * @brief Turn the relay off
 * @param _relay pointer to the relay module configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType relay_turn_off(const relay_t *_relay){
    Std_ReturnType ret = E_OK;
    if(NULL == _relay){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {.port = _relay->relay_port, .pin = _relay->relay_pin,
                                .direction = GPIO_DIRECTION_OUTPUT, .logic = _relay->relay_status};
        gpio_pin_write_logic(&pin_obj , GPIO_LOW);
    }
    return ret;
}
