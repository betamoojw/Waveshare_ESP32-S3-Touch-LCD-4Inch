#ifndef MODBUS_CONFIG_H
#define MODBUS_CONFIG_H

#include "ArduinoJson.h"

bool saveModbusConfig(const char* key, const char* value);
String getModbusConfig(const char* key);

#endif // MODBUS_CONFIG_H
