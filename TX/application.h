 /* 
 * File:   application.h
 * Author: Mohamed_Nagy
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on January 27, 2022, 8:41 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* Section : Includes */
#include "ECU_Layer/ecu_layer_init.h"
#include "MCAL_Layer/usart/hal_usart.h"
#include "MCAL_Layer/usart/hal_usart_cfg.h"
#include "MCAL_Layer/Interrupt/mcal_external_interrupt.h"
#include "MCAL_Layer/EEPROM/hal_eeprom.h"
#include "MCAL_Layer/ADC/hal_adc.h"
#include "MCAL_Layer/CCP/ccp_cfg.h"
#include "MCAL_Layer/CCP/hal_ccp.h"
#include "MCAL_Layer/Timer0/hal_timr0.h"
#include "MCAL_Layer/Timer1/hal_timr1.h"
#include "MCAL_Layer/Timer2/hal_timr2.h"
#include "MCAL_Layer/Timer3/hal_timr3.h"

/* Section: Macro Declarations */

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */

/* Section: Function Declarations */
void application_intialize(void);

#endif	/* APPLICATION_H */

