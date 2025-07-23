#ifndef buzzer_H
#define buzzer_H

#define		BUZZER_INIT									0
#define		BUZZER_NORMAL								200
#define 	BUZZER_ENCODER								10
#define		BUZZER_KEY									20
#define 	BUZZER_NORMAL_WAIT							30
#define		BUZZER_ERROR								40
#define		BUZZER_ERROR_LOOP							41

void Buzzer_Main(void);
void Buzzer_Set(uint8_t state);

#endif