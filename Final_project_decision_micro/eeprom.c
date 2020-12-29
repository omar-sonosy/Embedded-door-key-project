/*
 * eeprom.c
 *
 *  Created on: Oct 3, 2020
 *      Author: user
 */

#include "eeprom.h"
#include "i2c.h"

void EEPROM_init(void)
{
	TWI_init ();

}
uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data)
{
	TWI_start();
	if (TWI_getStatus() != TW_START )
		return ERROR;

	TWI_write((uint8)(0xA0 | ((u16addr & 0x700) >> 7))) ;  //device address (salve) EEPROM
	if (TWI_getStatus() != TW_MT_SLA_W_ACK )
		return ERROR;

	TWI_write((uint8)u16addr); // memory location in EEPROM
	if (TWI_getStatus() != TW_MT_DATA_ACK )
		return ERROR;

	TWI_write(u8data); // data
	if (TWI_getStatus() != TW_MT_DATA_ACK )
		return ERROR;

	TWI_stop ();

	return SUCCESS;
}


uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data)
{
	TWI_start();
	if (TWI_getStatus() != TW_START )
		return ERROR;

	TWI_write((uint8)(0xA0 | ((u16addr & 0x700) >> 7))) ;  //device address (salve) EEPROM
	if (TWI_getStatus() != TW_MT_SLA_W_ACK )
		return ERROR;

	TWI_write((uint8)u16addr); // memory location in EEPROM
	if (TWI_getStatus() != TW_MT_DATA_ACK )
		return ERROR;

	TWI_start();  // repeat start bit (because we switch from write to read)
	if (TWI_getStatus() != TW_REP_START)
		return ERROR;

	TWI_write((uint8)(0xA0 | ((u16addr & 0x700) >> 7)|1)) ;  //device address (salve) EEPROM // read mode
	if (TWI_getStatus() != TW_MT_SLA_R_ACK)
		return ERROR;

	*u8data = TWI_readWithNACK();
	if (TWI_getStatus() != TW_MR_DATA_NACK )
		return ERROR;

	TWI_stop();

	return SUCCESS;
}
