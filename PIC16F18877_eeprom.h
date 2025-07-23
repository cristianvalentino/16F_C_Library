#ifndef PIC16F8877_eeprom_H
#define PIC16F8877_eeprom_H

	void EEPROM_Write(uint16_t addr, uint8_t data);
	uint8_t EEPROM_Read(uint16_t addr);

#endif