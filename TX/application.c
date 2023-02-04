 /* 
 * File:   application.c
 * Author: Mohamed_Nagy
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on January 27, 2022, 8:41 PM
 */


#include "application.h"
Std_ReturnType ret = E_NOT_OK;
void application_intialize();
void WelcomingMessage();
void TimeValidation();
void calcTime();
void getHoures();
void getMinutes();
void getSeconds();
void usartSend();


uint8 hour=47 , min=47 , sec=47 , KeypadPressed=47 ;
uint8 time[6]={47 ,47 ,47 ,47 ,47 ,47 } ;
uint8 pressFlag = 0;


chr_lcd_4bit_t lcd_1 =
{
	.lcd_rs.port=PORTD_INDEX,
	.lcd_rs.pin=GPIO_PIN0,
	.lcd_rs.direction=GPIO_DIRECTION_OUTPUT,
	.lcd_rs.logic=GPIO_LOW,
	
    .lcd_en.port=PORTD_INDEX,
	.lcd_en.pin=GPIO_PIN1,
	.lcd_en.direction=GPIO_DIRECTION_OUTPUT,
	.lcd_en.logic=GPIO_LOW,
	
    .lcd_data[0].port=PORTD_INDEX,
	.lcd_data[0].pin=GPIO_PIN2,
	.lcd_data[0].direction=GPIO_DIRECTION_OUTPUT,
	.lcd_data[0].logic=GPIO_LOW,
	
    .lcd_data[1].port=PORTD_INDEX,
	.lcd_data[1].pin=GPIO_PIN3,
	.lcd_data[1].direction=GPIO_DIRECTION_OUTPUT,
	.lcd_data[1].logic=GPIO_LOW,
	
    .lcd_data[2].port=PORTD_INDEX,
	.lcd_data[2].pin=GPIO_PIN4,
	.lcd_data[2].direction=GPIO_DIRECTION_OUTPUT,
	.lcd_data[2].logic=GPIO_LOW,
	
    .lcd_data[3].port=PORTD_INDEX,
	.lcd_data[3].pin=GPIO_PIN5,
	.lcd_data[3].direction=GPIO_DIRECTION_OUTPUT,
	.lcd_data[3].logic=GPIO_LOW,
	
};


keypad_t keypad_1 =
{
	.keypad_row_pins[0].port=PORTB_INDEX,
	.keypad_row_pins[0].pin=GPIO_PIN0,
	.keypad_row_pins[0].direction=GPIO_DIRECTION_OUTPUT,
	.keypad_row_pins[0].logic=GPIO_LOW,	
	
    .keypad_row_pins[1].port=PORTB_INDEX,
	.keypad_row_pins[1].pin=GPIO_PIN1,
	.keypad_row_pins[1].direction=GPIO_DIRECTION_OUTPUT,
	.keypad_row_pins[1].logic=GPIO_LOW,
	
    .keypad_row_pins[2].port=PORTB_INDEX,
	.keypad_row_pins[2].pin=GPIO_PIN2,
	.keypad_row_pins[2].direction=GPIO_DIRECTION_OUTPUT,
	.keypad_row_pins[2].logic=GPIO_LOW,
	
    .keypad_row_pins[3].port=PORTB_INDEX,
	.keypad_row_pins[3].pin=GPIO_PIN3,
	.keypad_row_pins[3].direction=GPIO_DIRECTION_OUTPUT,
	.keypad_row_pins[3].logic=GPIO_LOW,
	
    .keypad_columns_pins[0].port=PORTB_INDEX,
	.keypad_columns_pins[0].pin=GPIO_PIN4,
	.keypad_columns_pins[0].direction=GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[0].logic=GPIO_LOW,
	
    .keypad_columns_pins[1].port=PORTB_INDEX,
	.keypad_columns_pins[1].pin=GPIO_PIN5,
	.keypad_columns_pins[1].direction=GPIO_DIRECTION_INPUT,
	.keypad_columns_pins[1].logic=GPIO_LOW,
	
    .keypad_columns_pins[2].port=PORTB_INDEX,
	.keypad_columns_pins[2].pin=GPIO_PIN6,
	.keypad_columns_pins[2].direction=GPIO_DIRECTION_INPUT,
	.keypad_columns_pins[2].logic=GPIO_LOW,
	
    .keypad_columns_pins[3].port=PORTB_INDEX,
	.keypad_columns_pins[3].pin=GPIO_PIN7,
	.keypad_columns_pins[3].direction=GPIO_DIRECTION_INPUT,
	.keypad_columns_pins[3].logic=GPIO_LOW,				
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
    .EUSART_TxDefaultInterruptHandler = NULL
};



int main()
{ 
    application_intialize();
    WelcomingMessage();
    while(1)
    {
        ret = lcd_4bit_send_string_pos(&lcd_1, 1, 1, "Press 1 To Set the  Time : ");
        ret = keypad_get_value(&keypad_1, &KeypadPressed);
        if(KeypadPressed != 47)
        {
            ret = lcd_4bit_send_char_data_pos(&lcd_1, 3, 8, KeypadPressed);
            __delay_ms(500);
            ret = lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
        
            if(KeypadPressed == '1')
            {
                pressFlag = 1;
                getHoures();
                getMinutes();
                getSeconds();    
            }
            else
            {
                ret = lcd_4bit_send_string_pos(&lcd_1, 2, 2, "Wrong Choice !");
                __delay_ms(500);   
                ret = lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
            }
            if(pressFlag == 1)
            {
                calcTime();
                TimeValidation();
                pressFlag = 0;
            }
            KeypadPressed = 47;
        }     
    }
    return (EXIT_SUCCESS);
}


void calcTime()
{
    hour = time[0]*10 + time[1] ;
    min  = time[2]*10 + time[3] ; 
    sec  = time[4]*10 + time[5] ; 
}


void TimeValidation()
{
    if((hour>24) || (min>60) || (sec>60))
    {
        ret = ret = lcd_4bit_send_string_pos(&lcd_1, 2, 2, "Wrong Timing !");
        __delay_ms(2000);   
        ret = lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
    }
    else
    {
        usartSend();
        ret = ret = lcd_4bit_send_string_pos(&lcd_1, 2, 2, "Done.");
        __delay_ms(2000);   
        ret = lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
    }
}




void getHoures()
{
    KeypadPressed = 47;
    ret = lcd_4bit_send_string_pos(&lcd_1, 1, 1, "Houres : "); 
    do
    {
        ret = keypad_get_value(&keypad_1, &KeypadPressed);
        __delay_ms(200);
    }
    while(KeypadPressed == 47);
    ret = lcd_4bit_send_char_data_pos(&lcd_1, 1, 11, KeypadPressed);
    time[0] = KeypadPressed-48;
    KeypadPressed = 47;
    do
    {
        ret = keypad_get_value(&keypad_1, &KeypadPressed);
        __delay_ms(200);
    }
    while(KeypadPressed == 47);
    ret = lcd_4bit_send_char_data_pos(&lcd_1, 1, 12, KeypadPressed);
    __delay_ms(300);
    time[1] = KeypadPressed-48;
    KeypadPressed = 47;
    ret = lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
}


void getMinutes()
{
    KeypadPressed = 47;
    ret = lcd_4bit_send_string_pos(&lcd_1, 1, 1, "Minutes : "); 
    do
    {
        ret = keypad_get_value(&keypad_1, &KeypadPressed);
        __delay_ms(200);
    }
    while(KeypadPressed == 47);
    ret = lcd_4bit_send_char_data_pos(&lcd_1, 1, 12, KeypadPressed);
    time[2] = KeypadPressed-48;
    KeypadPressed = 47;
    do
    {
        ret = keypad_get_value(&keypad_1, &KeypadPressed);
        __delay_ms(200);
    }
    while(KeypadPressed == 47);
    ret = lcd_4bit_send_char_data_pos(&lcd_1, 1, 13, KeypadPressed);
    __delay_ms(300);
    time[3] = KeypadPressed-48;
    KeypadPressed = 47;
    ret = lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
}


void getSeconds()
{
    KeypadPressed = 47;
    ret = lcd_4bit_send_string_pos(&lcd_1, 1, 1, "Seconds : "); 
    do
    {
        ret = keypad_get_value(&keypad_1, &KeypadPressed);
        __delay_ms(200);
    }
    while(KeypadPressed == 47);
    ret = lcd_4bit_send_char_data_pos(&lcd_1, 1, 12, KeypadPressed);
    time[4] = KeypadPressed-48;
    KeypadPressed = 47;
    do
    {
        ret = keypad_get_value(&keypad_1, &KeypadPressed);
        __delay_ms(200);
    }
    while(KeypadPressed == 47);
    ret = lcd_4bit_send_char_data_pos(&lcd_1, 1, 13, KeypadPressed);
    __delay_ms(300);
    time[5] = KeypadPressed-48;
    KeypadPressed = 47;
    ret = lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
}

void WelcomingMessage()
{
    ret = lcd_4bit_send_string_pos(&lcd_1, 2, 7, "Welcome.");
    __delay_ms(1000);
    ret = lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
}

void application_intialize()
{
    ret = lcd_4bit_intialize(&lcd_1);
    ret = keypad_initialize(&keypad_1);
    ret = EUSART_ASYNC_Init(&usart_1);
}


void usartSend()
{
    uint8 arrayTime[4];
    arrayTime[0] = hour + '0';
    arrayTime[1] = min  + '0';
    arrayTime[2] = sec  + '0';
    arrayTime[3] = '\0'      ;
    ret = EUSART_ASYNC_WriteStringBlocking(&arrayTime, 4);
}
