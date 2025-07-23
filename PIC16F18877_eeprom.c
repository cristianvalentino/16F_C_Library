#include "../../system/system.h"

// Direccion fisica de la EEPROM (0x00-0xFF) pero accedida como 0xF000-0xF0FF
#define EEPROM_START_ADDR  0xF000  
#define EEPROM_END_ADDR    0xF0FF

void EEPROM_Write(uint16_t addr, uint8_t data) {
    // 1. Configurar direccion (16 bits, aunque solo se usan 8 para EEPROM)
	NVMADRL = (uint8_t)((EEPROM_START_ADDR + addr ) & 0xFF);   // Parte baja (0x00–0xFF)
	NVMADRH = (uint8_t)((EEPROM_START_ADDR + addr ) >> 8);     // Parte alta (0x0F para 0xF000–0xF0FF)
	
	// 2. Escribir dato
	NVMDATL = data;                     // Dato a guardar
	
	// 3. Configurar operacion: escritura en EEPROM
	NVMCON1bits.NVMREGS = 0;            // Acceder a EEPROM (no Flash)
	NVMCON1bits.WREN = 1;               // Habilitar escritura
	
	// 4. Deshabilitar interrupciones
	INTCONbits.GIE = 0;
	
	// 5. Secuencia de seguridad (obligatoria)
	NVMCON2 = 0x55;
	NVMCON2 = 0xAA;
	
	// 6. Iniciar escritura
	NVMCON1bits.WR = 1;
	while (NVMCON1bits.WR);             // Esperar a que termine (~4ms)
	
	// 7. Limpiar y restaurar
	NVMCON1bits.WREN = 0;               // Deshabilitar escritura
	INTCONbits.GIE = 1;                 // Rehabilitar interrupciones
}

uint8_t EEPROM_Read(uint16_t addr){
	// 1. Configurar direccion
	NVMADRL = (uint8_t)((EEPROM_START_ADDR + addr ) & 0xFF);
	NVMADRH = (uint8_t)((EEPROM_START_ADDR + addr ) >> 8);
	
	// 2. Configurar operacion: lectura de EEPROM
	NVMCON1bits.NVMREGS = 0;            // Acceder a EEPROM
	NVMCON1bits.RD = 1;                 // Iniciar lectura
	
	// 3. Devolver dato leído
	return NVMDATL;
}