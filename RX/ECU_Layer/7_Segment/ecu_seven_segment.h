/* 
 * File:   ecu_seven_segment.h
 * Author: Ahmed.Elghafar
 *
 * Created on December 27, 2020, 5:47 PM
 */

#ifndef ECU_SEVEN_SEGMENT_H
#define	ECU_SEVEN_SEGMENT_H

/* Section : Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_seven_segment_cfg.h"

/* Section: Macro Declarations */
#define SEGEMENT_PIN0 0
#define SEGEMENT_PIN1 1
#define SEGEMENT_PIN2 2
#define SEGEMENT_PIN3 3

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */
typedef enum{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE
}segment_type_t;

typedef struct{
    pin_config_t segment_pins[4];
    segment_type_t segment_type;
}segment_t;

/* Section: Function Declarations */
Std_ReturnType seven_segement_intialize(const segment_t *seg);
Std_ReturnType seven_segement_write_number(const segment_t *seg, uint8 number);

#endif	/* ECU_SEVEN_SEGMENT_H */
