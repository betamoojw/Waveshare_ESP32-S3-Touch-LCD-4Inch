#include "ModbusConfig.h"
#include "LittleFS.h"
#include <Arduino.h>  // for Serial functions

// Define the constants
const size_t JSON_DOC_SIZE = 512; // Adjust as needed
const char* CONFIG_FILE = "/config/modbus-config.json";


bool saveModbusConfig(const char* key, const char* value) {
    DynamicJsonDocument doc(JSON_DOC_SIZE);
    File file = LittleFS.open(CONFIG_FILE, "r+");
    if (!file) {
        return false;
    }
    DeserializationError error = deserializeJson(doc, file);
    if (error) {
        file.close();
        return false;
    }
    doc[key] = value;
    file.seek(0);
    serializeJson(doc, file);
    file.close();
    return true;
}

String getModbusConfig(const char* key) {
    DynamicJsonDocument doc(JSON_DOC_SIZE);
    File file = LittleFS.open(CONFIG_FILE, "r");
    if (!file) {
        return String("");
    }
    DeserializationError error = deserializeJson(doc, file);
    if (error) {
        file.close();
        return String("");
    }
    file.close();
    if (doc.containsKey(key)) {
        return doc[key].as<String>();
    } else {
        return String("");
    }
}
