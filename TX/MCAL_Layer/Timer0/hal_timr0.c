/* 
 * File:   hal_timr0.c
 * Author: Ahmed Abd El-Ghafar
 * https://www.linkedin.com/in/ahmedabdelghafarmohammed/
 * Created on April 6, 2021, 8:53 PM
 */

#include "hal_timr0.h"

#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (*TMR0_InterruptHandler)(void) = NULL;
#endif
static uint16 timer0_preload = ZERO_INIT;

static inline void Timer0_Prescaler_Config(const timer0_t *_timer);
static inline void Timer0_Mode_Select(const timer0_t *_timer);
static inline void Timer0_Register_Size_Config(const timer0_t *_timer);

Std_ReturnType Timer0_Init(const timer0_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER0_MODULE_DISABLE();
        Timer0_Prescaler_Config(_timer);
        Timer0_Mode_Select(_timer);
        Timer0_Register_Size_Config(_timer);
        TMR0H = (_timer->timer0_preload_value) >> 8;
        TMR0L = (uint8)(_timer->timer0_preload_value);
        timer0_preload = _timer->timer0_preload_value;
/* Interrupt Configurations */        
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER0_InterruptEnable();
        TIMER0_InterruptFlagClear();
        TMR0_InterruptHandler = _timer->TMR0_InterruptHandler;

/* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
        INTERRUPT_PriorityLevelsEnable();
        if(INTERRUPT_HIGH_PRIORITY == _timer->priority){
            /* Enables all high-priority interrupts */
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER0_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == _timer->priority){
            /* Enables all unmasked peripheral interrupts */
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER0_LowPrioritySet();
        }
        else{ /* Nothing */ }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        
#endif
        TIMER0_MODULE_ENABLE();
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType Timer0_DeInit(const timer0_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER0_MODULE_DISABLE();
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER0_InterruptDisable();
#endif
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType Timer0_Write_Value(const timer0_t *_timer, uint16 _value){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TMR0H = (_value) >> 8;
        TMR0L = (uint8)(_value);
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType Timer0_Read_Value(const timer0_t *_timer, uint16 *_value){
    Std_ReturnType ret = E_NOT_OK;
    uint8 l_tmr0l = ZERO_INIT, l_tmr0h = ZERO_INIT;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        l_tmr0l = TMR0L;
        l_tmr0h = TMR0H;
        *_value = (uint16)((l_tmr0h << 8) + l_tmr0l);
        ret = E_OK;
    }
    return ret;
}

void TMR0_ISR(void){
    TIMER0_InterruptFlagClear();
    TMR0H = (timer0_preload) >> 8;
    TMR0L = (uint8)(timer0_preload);
    if(TMR0_InterruptHandler){
        TMR0_InterruptHandler();
    }
}

static inline void Timer0_Prescaler_Config(const timer0_t *_timer){
    if(TIMER0_PRESCALER_ENABLE_CFG == _timer->prescaler_enable){
        TIMER0_PRESCALER_ENABLE();
        T0CONbits.T0PS = _timer->prescaler_value;
    }
    else if(TIMER0_PRESCALER_DISABLE_CFG == _timer->prescaler_enable){
        TIMER0_PRESCALER_DISABLE();
    }
    else{ /* Nothing */ }
}

static inline void Timer0_Mode_Select(const timer0_t *_timer){
    if(TIMER0_TIMER_MODE == _timer->timer0_mode){
        TIMER0_TIMER_MODE_ENABLE();
    }
    else if(TIMER0_COUNTER_MODE == _timer->timer0_mode){
        TIMER0_COUNTER_MODE_ENABLE();
        if(TIMER0_COUNTER_RISING_EDGE_CFG == _timer->timer0_counter_edge){
            TIMER0_RISING_EDGE_ENABLE();
        }
        else if(TIMER0_COUNTER_FALLING_EDGE_CFG == _timer->timer0_counter_edge){
            TIMER0_FALLING_EDGE_ENABLE();
        }
        else{ /* Nothing */ }
    }
    else{ /* Nothing */ }
}

static inline void Timer0_Register_Size_Config(const timer0_t *_timer){
    if(TIMER0_8BIT_REGISTER_MODE == _timer->timer0_register_size){
        TIMER0_8BIT_REGISTER_MODE_ENABLE();
    }
    else if(TIMER0_16BIT_REGISTER_MODE == _timer->timer0_register_size){
        TIMER0_16BIT_REGISTER_MODE_ENABLE();
    }
    else{ /* Nothing */ }
}