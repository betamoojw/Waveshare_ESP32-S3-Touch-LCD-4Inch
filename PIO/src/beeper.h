#ifndef BEEPER_H
#define BEEPER_H

#include <ESP_IOExpander_Library.h>
#include "main.h"

extern void playTone(ESP_IOExpander *expander, int tone, int duration);

#endif