#include "buzzer.h"

const int8_t DiaSemTbl[7][10]={"DOMINGO  ","LUNES    ","MARTES   ","MIERCOLES","JUEVES   ","VIERNES  ","SABADO   "};



tTime Time;

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void DS3231_Read(void) {
// 1. Leer registros 0x00-0x06 (hora y fecha)
	I2C_Start();
	I2C_Write(DS3132);												// Dirección + escritura
	I2C_Write(0x00);												// Empezar desde el registro 0x00 (segundos)
	I2C_Stop();
	
	I2C_Start();													// Reiniciar comunicación
	I2C_Write(DS3132+1);												// Dirección + lectura
	Time.sec = I2C_Read();		I2C_Ack();
	Time.min = I2C_Read();		I2C_Ack();
	Time.hour = I2C_Read();		I2C_Ack();
	Time.weekday = I2C_Read();	I2C_Ack();
	Time.day = I2C_Read();		I2C_Ack();
	Time.month = I2C_Read();	I2C_Ack();
	Time.year = I2C_Read();		I2C_Nack();
	
//	2. Leer temperatura (registros 0x11-0x12)
	I2C_Start();
	I2C_Write(0xD0);
	I2C_Write(0x11);
	I2C_Start();
	I2C_Write(0xD1);
	uint8_t temp_high = I2C_Read();	I2C_Ack();						// Parte entera (ACK)
	uint8_t temp_low  = I2C_Read();	I2C_Nack();						// Parte fraccionaria (NACK)
	I2C_Stop();
	
	Time.temperature = temp_high + ((temp_low >> 6) * 0.25);		// Ej: 25.75°C
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void DS3231_Set(void) {
	I2C_Start();
	I2C_Write(0xD0);												// Dirección + escritura
	I2C_Write(0x00);												// Empezar en registro 0x00
	I2C_Write(Time.sec);
	I2C_Write(Time.min);
	I2C_Write(Time.hour);
	I2C_Write(Time.weekday);
	I2C_Write(Time.day);
	I2C_Write(Time.month);
	I2C_Write(Time.year);
	
	I2C_Stop();
}