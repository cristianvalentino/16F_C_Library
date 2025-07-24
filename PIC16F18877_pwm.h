//#ifndef PIC16F18877_pwm_H
//#define PIC16F18877_pwm_H

	void Create_PWM6(volatile unsigned char *port);
	void DutyValue_PWM6(uint16_t dutyValue);
	void Stop_PWM6(void);
	void Start_PWM6(void);

	void Create_PWM7(volatile unsigned char *port);
	void DutyValue_PWM7(uint16_t dutyValue);
	void Stop_PWM7(void);
	void Start_PWM7(void);

//#endif