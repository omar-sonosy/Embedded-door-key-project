/*
 * uart.h
 *
 *  Created on: Oct 1, 2020
 *      Author: user
 */

#ifndef UART_H_
#define UART_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"


#define MODE ASYNCHRONOUS_DOUBLE_SPEED

#define ASYNCHRONOUS_DOUBLE_SPEED 0
#define ASYNCHRONOUS_NORMAL_MODE 1
#define SYNCHRONOUS_MASTER 2


#if (MODE == 0)
    #define double_speed  1
	#define mode_bit  0
	#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 8UL))) - 1)
#elif (MODE == 1)
    #define double_speed  0
	#define mode_bit  0
	#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#else
    #define double_speed  0
	#define mode_bit  1
	#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 2UL))) - 1)
#endif


#define USART_BAUDRATE 9600


typedef enum
{
	BIT_5, BIT_6, BIT_7, BIT_8, BIT_9=7
}number_of_data_bits;

typedef enum
{
	DISABLE, _, EVEN, ODD
}parity_type;

typedef enum
{
	STOP_BIT_1, STOP_BIT_2
}stop_bit_type;

typedef enum
{
	ASYNCHRONOUS, SYNCHRONOUS
}operating_mode;

typedef struct
{
	number_of_data_bits data_bits;
	parity_type parity;
	stop_bit_type stop_bit;
}UART_config;


void uart_init(const UART_config * cofig_Ptr);
void UART_SendByte(uint8 data);
uint8 UART_RecieveByte(void);
void uart_sendString(const uint8 *str);
void uart_recieveString(uint8 *str);


#endif /* UART_H_ */
