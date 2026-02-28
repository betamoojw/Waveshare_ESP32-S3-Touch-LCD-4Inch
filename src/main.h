#ifndef MAIN_H
#define MAIN_H

// version code in format yyyymmddb (b = daily build)
#define VERSION 202503160

// uncomment this if you have a "my_config.h" file you'd like to use
// #define SMARTPANEL_USE_MY_CONFIG

// GLOBAL VARIABLES
// both declared and defined in header (solution from http://www.keil.com/support/docs/1868.htm)
//
// e.g. byte test = 2 becomes SMARTPANEL_GLOBAL byte test _INIT(2);
//     int arr[]{0,1,2} becomes SMARTPANEL_GLOBAL int arr[] _INIT_N(({0,1,2}));

#ifndef SMARTPANEL_DEFINE_GLOBAL_VARS
#define SMARTPANEL_GLOBAL extern
#define _INIT(x)
#define _INIT_N(x)
#define _INIT_PROGMEM(x)
#else
#define SMARTPANEL_GLOBAL
#define _INIT(x)         = x
// needed to ignore commas in array definitions
#define UNPACK(...)      __VA_ARGS__
#define _INIT_N(x)       UNPACK x
#define _INIT_PROGMEM(x) PROGMEM = x
#endif

#define STRINGIFY(X) #X
#define TOSTRING(X)  STRINGIFY(X)

#ifndef SMARTPANEL_VERSION
#define SMARTPANEL_VERSION "Dev"
#endif

#ifndef SMARTPANEL_RELEASE_NAME
#define SMARTPANEL_RELEASE_NAME "Custom"
#endif

// Global Variable definitions
SMARTPANEL_GLOBAL char versionString[] _INIT(TOSTRING(SMARTPANEL_VERSION));
SMARTPANEL_GLOBAL char releaseString[] _INIT(
    SMARTPANEL_RELEASE_NAME); // must include the quotes when defining, e.g -D SMARTPANEL_RELEASE_NAME=\"ESP32_MULTI_USREMODS\"
#define SMARTPANEL_CODENAME "Great Wall"

#define TP_INT_PIN 16 // TP_INT for Touch Panel int

// IO Expander
#define IO_EXPANDER_CHIP_NAME   TCA95xx_8bit
#define IO_EXPANDER_I2C_NUM     (1)
#define IO_EXPANDER_I2C_SCL_PIN (7)
#define IO_EXPANDER_I2C_SDA_PIN (15)

// Extend IO Pin define
#define EXP_IO_TP_RST  0 // TP_RST for Touch Panel reset
#define EXP_IO_LCD_BL  1 // BL_EN for Backlight enable
#define EXP_IO_LCD_RST 2 // LCD_RST for LCD reset
#define EXP_IO_SD_CS   3 // SD_CS for SD Card
#define EXP_IO_PIN     4 // Not used
#define EXP_IO_BEE_EN  5 // BEE_EN for Buzzer ena
#define EXP_IO_RTC_INT 6 // RTC_INT for RTC alarm
#define EXP_IO_IRQ     7 // IRQ for OTS

#define _IO_EXPANDER_CHIP_CLASS(name, ...) ESP_IOExpander_##name(__VA_ARGS__)
#define IO_EXPANDER_CHIP_CLASS(name, ...)  _IO_EXPANDER_CHIP_CLASS(name, ##__VA_ARGS__)

// GPIO43 is RS485_RXD, GPIO44 is RS485_TXD
#define RS485_RXD_PIN 43
#define RS485_TXD_PIN 44

#ifndef SMARTPANEL_DISABLE_RS485
#define SMARTPANEL_ENABLE_RS485

// GPIO43 is RS485_RXD, GPIO44 is RS485_TXD
#define RS485_RXD_PIN 43
#define RS485_TXD_PIN 44
#endif

#ifndef SMARTPANEL_DISABLE_CAN
#define SMARTPANEL_ENABLE_CAN

// GPIO0 is CAN_RXD, GPIO6 is CAN_TXD
#define CAN_RXD_PIN 0
#define CAN_TXD_PIN 6
#endif

#ifndef SMARTPANEL_DISABLE_CLI
#define SMARTPANEL_ENABLE_CLI
#endif

#endif // MAIN_H