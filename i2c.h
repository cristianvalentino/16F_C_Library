#ifndef i2c_H
#define i2c_H

    void I2C_Initialize(void);
    void I2C_Start(void);
    void I2C_ReStart(void);
    void I2C_Stop(void);
    uint8_t I2C_Read(void);
    void I2C_Ack(void);
    void I2C_Nack(void);
    void I2C_Write(uint8_t data);

#endif