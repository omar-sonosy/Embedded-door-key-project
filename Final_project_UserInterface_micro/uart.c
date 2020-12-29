/*
 * uart.c
 *
 *  Created on: Oct 1, 2020
 *      Author: user
 */

#include "uart.h"


void uart_init(const UART_config * cofig_Ptr)
{

	UCSRB |= (1 << RXEN) | (1 << TXEN); // enable Tx, Rx
	UCSRC |= (1 << URSEL) ;

	/*double speed*/
	UCSRA = (UCSRA & 0xFD) | (double_speed << 1); // double speed

	//UCSRC |=  (1 << UCSZ1) | (1 << UCSZ0); // 8 bit data
	UCSRC = (UCSRC & 0xF9) | ((cofig_Ptr->data_bits & 0x03)<<1);
	UCSRB = (UCSRB & 0xFB) | (cofig_Ptr->data_bits & 0x04);

	/*parity*/
	UCSRC = (UCSRC & 0xCF) | (cofig_Ptr->parity << 4);

	/* stop_bit*/
	UCSRC = (UCSRC & 0xF7) | (cofig_Ptr->stop_bit << 3);

	/*mode*/
	UCSRC = (UCSRC & 0xBF) | (mode_bit << 6);

	UBRRL = BAUD_PRESCALE;
	UBRRH = BAUD_PRESCALE >> 8;
}


void UART_SendByte(uint8 data)
{
	while (BIT_IS_CLEAR(UCSRA ,UDRE)){};
	UDR = data;
}

uint8 UART_RecieveByte(void)
{
	while (BIT_IS_CLEAR(UCSRA ,RXC)){};
	return UDR;
}

void uart_sendString(const uint8 *str)
{
	uint8 i = 0;
	while (str[i] != '\0')
	{
		UART_SendByte(str[i]);
		i++;
	}
}

void uart_recieveString(uint8 *str)
{
	uint8 i = 0;
	str[i] = UART_RecieveByte();
	while (str[i] != '#')
	{
		i++;
		str[i] = UART_RecieveByte();
	}
	str[i] = '\0';
}
