 /* 
 * File:   application.c
 * Author: Mohamed_Nagy
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on January 27, 2022, 8:41 PM
 */


#include "application.h"
void SegmentsUpdate();
void TimesUpdate();
void usartTxHandeler();

Std_ReturnType ret = E_NOT_OK;


uint8 hour=20, min=45, sec=50;
uint8 counter;
uint8 keypad_val, keypad_pressed=0;

segment_t seg =
{
    .segment_pins[0].port = PORTB_INDEX,
    .segment_pins[0].pin = GPIO_PIN0,
    .segment_pins[0].logic = GPIO_LOW,
    .segment_pins[0].direction = GPIO_DIRECTION_OUTPUT,
    
    .segment_pins[1].port = PORTB_INDEX,
    .segment_pins[1].pin = GPIO_PIN1,
    .segment_pins[1].logic = GPIO_LOW,
    .segment_pins[1].direction = GPIO_DIRECTION_OUTPUT,
    
    .segment_pins[2].port = PORTB_INDEX,
    .segment_pins[2].pin = GPIO_PIN2,
    .segment_pins[2].logic = GPIO_LOW,
    .segment_pins[2].direction = GPIO_DIRECTION_OUTPUT,
    
    .segment_pins[3].port = PORTB_INDEX,
    .segment_pins[3].pin = GPIO_PIN3,
    .segment_pins[3].logic = GPIO_LOW,
    .segment_pins[3].direction = GPIO_DIRECTION_OUTPUT,
};



usart_t usart_1 = 
{
    .baudrate = 9600,
    .baudrate_gen_gonfig = BAUDRATE_ASYN_8BIT_lOW_SPEED,
            
    .usart_tx_cfg.usart_tx_enable = EUSART_ASYNCHRONOUS_TX_ENABLE,
    .usart_tx_cfg.usart_tx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE,
    .usart_tx_cfg.usart_tx_9bit_enable = EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE,
    
    .usart_rx_cfg.usart_rx_enable = EUSART_ASYNCHRONOUS_RX_ENABLE,
    .usart_rx_cfg.usart_rx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE,
    .usart_rx_cfg.usart_rx_9bit_enable = EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE,    
    
    .EUSART_RxDefaultInterruptHandler = NULL,
    .EUSART_FramingErrorHandler = NULL,
    .EUSART_OverrunErrorHandler = NULL,
    .EUSART_TxDefaultInterruptHandler = usartTxHandeler
};



int main()
{ 
    application_intialize();
    while(1)
    {
        SegmentsUpdate();
        TimesUpdate();       
    }
    return (EXIT_SUCCESS);
}

void application_intialize(void)
{
    ret = gpio_port_direction_intialize(PORTD_INDEX, 0xC0);
    ret = seven_segement_intialize(&seg);
    ret = EUSART_ASYNC_Init(&usart_1);
}



void usartTxHandeler()
{
    uint8 timeRxArray[4];
    USART_Read_string(&timeRxArray , 4);
    hour = timeRxArray[0] - '0';
    min  = timeRxArray[1] - '0';
    sec  = timeRxArray[2] - '0';
}



void TimesUpdate()
{  
    sec++;
    if(sec==60)
    {
        min++;
        sec=0;
    }
    if(min==60)
    {
        hour++;
        min=0;
    }
    if(hour==24)
    {
        hour=0;
    }
}


void SegmentsUpdate()
{
    for(counter=0 ; counter<34 ; counter++)
    {
        ret = gpio_port_write_logic(PORTD_INDEX, 1);
        ret = seven_segement_write_number(&seg, (uint8)(hour/10) );
        __delay_ms(5);

        ret = gpio_port_write_logic(PORTD_INDEX, 2);
        ret = seven_segement_write_number(&seg, (uint8)(hour%10 ) );
        __delay_ms(5);

        ret = gpio_port_write_logic(PORTD_INDEX, 4);
        ret = seven_segement_write_number(&seg, (uint8)(min/10) );
        __delay_ms(5);

        ret = gpio_port_write_logic(PORTD_INDEX, 8);
        ret = seven_segement_write_number(&seg, (uint8)(min%10) );
        __delay_ms(5);

        ret = gpio_port_write_logic(PORTD_INDEX, 16);
        ret = seven_segement_write_number(&seg, (uint8)(sec/10) );
        __delay_ms(5);

        ret = gpio_port_write_logic(PORTD_INDEX, 32);
        ret = seven_segement_write_number(&seg, (uint8)(sec%10) );
        __delay_ms(5);
    }
}