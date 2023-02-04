
#include "Ultrasonic.h"

Std_ReturnType Ultrasonic_Init(const ultrasonic_t *_config){
    Std_ReturnType ret = E_OK;
    
    if(NULL == _config){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_intialize(&(_config->Trigger_Pin));
        ret &= gpio_pin_intialize(&(_config->Echo_Pin));
    }
    
    return ret;
}

Std_ReturnType Ultrasonic_Calculate_Distance(const ultrasonic_t *_config, uint16 *Distance){
    Std_ReturnType ret = E_OK;
    uint16 Timer0_Value = 0;
    logic_t EchoPinLogic = GPIO_LOW;
    
    if(NULL == _config){
        ret = E_NOT_OK;
    }
    else{
        /* Send Trigger Signal to the Ultrasonic Trigger Pin */
        ret = gpio_pin_write_logic(&(_config->Trigger_Pin), GPIO_HIGH);
        __delay_us(10);
        ret = gpio_pin_write_logic(&(_config->Trigger_Pin), GPIO_LOW);
        
        /* Wait the Echo pin to be High */
        while(GPIO_LOW == EchoPinLogic){
            ret = gpio_pin_read_logic(&(_config->Echo_Pin), &EchoPinLogic);
        }
        
        /* Clear Timer0 Ticks -> Already Enabled */
        //ret = Timer0_Write_Value(&timer0_timer_obj, 0);

        /* Wait the Echo pin to be Low */
        while(GPIO_HIGH == EchoPinLogic){
            ret = gpio_pin_read_logic(&(_config->Echo_Pin), &EchoPinLogic);
        }
        
        /* Read the time */
        //ret = Timer0_Read_Value(&timer0_timer_obj, &Timer0_Value);
        
        /* Calculate the distance */
        *Distance = (uint16)(Timer0_Value / 58.8f);
    }
    
    return ret;
}
