#ifndef DS3231_H
#define DS3231_H

#define DS3132			0xD0


#define DOMINGO			1
#define LUNES			2
#define MARTES			3
#define MIERCOLES		4
#define JUEVES			5
#define VIERNES			6
#define SABADO			7

typedef struct{
	uint8_t	sec;
	uint8_t	min;
	uint8_t	hour;
	uint8_t	weekday;
	uint8_t	day;
	uint8_t	month;
	uint8_t year;
	float   temperature; // Temperatura en grados Celsius
}tTime;

extern tTime Time;


void DS3231_Read(void);
void DS3231_Set(void);
#endif