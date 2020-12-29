/*
 * eeprom.h
 *
 *  Created on: Oct 3, 2020
 *      Author: user
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

#define ERROR 0
#define SUCCESS 1

void EEPROM_init(void);
uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);

#endif /* EEPROM_H_ */
