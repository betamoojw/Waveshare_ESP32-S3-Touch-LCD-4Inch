#ifndef __TWAI_PORT_H
#define __TWAI_PORT_H
#pragma once

#include "driver/twai.h"
#include <Arduino.h>

// Intervall:
#define POLLING_RATE_MS 1000

bool twai_init();
void twai_receive();
void twai_transmit();
void twai_task();

#endif