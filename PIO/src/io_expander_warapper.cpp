#include <Arduino.h>
#include "io_expander_warapper.h"
#include "HWCDC.h"

extern HWCDC USBSerial; // Declaration of the external USBSerial object

void io_expander_init(ESP_IOExpander *expander)
{
    expander = new IO_EXPANDER_CHIP_CLASS(IO_EXPANDER_CHIP_NAME,
                                      (i2c_port_t)IO_EXPANDER_I2C_NUM, ESP_IO_EXPANDER_I2C_TCA9554_ADDRESS_000,
                                      IO_EXPANDER_I2C_SCL_PIN, IO_EXPANDER_I2C_SDA_PIN);

    expander->init();
    expander->begin();
    USBSerial.println("IO Expander initialized successfully.");


    USBSerial.println("IO Expander Original status:");
    expander->printStatus();
    expander->pinMode(EXP_IO_BEE_EN, OUTPUT);
    expander->digitalWrite(EXP_IO_BEE_EN, HIGH);
    expander->pinMode(EXP_IO_TP_RST, OUTPUT);
    expander->digitalWrite(EXP_IO_TP_RST, LOW);
    expander->pinMode(EXP_IO_LCD_RST, OUTPUT);
    expander->digitalWrite(EXP_IO_LCD_RST, LOW);
    expander->printStatus();
    delay(200);
    expander->digitalWrite(EXP_IO_BEE_EN, LOW);
    expander->digitalWrite(EXP_IO_LCD_RST, HIGH);
    expander->digitalWrite(EXP_IO_TP_RST, HIGH);
    expander->printStatus();
}