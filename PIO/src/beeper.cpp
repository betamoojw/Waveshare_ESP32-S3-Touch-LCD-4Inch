#include <Arduino.h>
#include "main.h"
#include "io_expander_warapper.h"
#include "pitches.h"
#include "beeper.h"

// notes in the melody:
static const int melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = { 4, 8, 8, 4, 4, 4, 4, 4};

void playTone(ESP_IOExpander *expander, int tone, int duration)
{
    for (long i = 0; i < duration * 1000L; i += tone * 2)
    {
        expander->digitalWrite(EXP_IO_BEE_EN, HIGH);
        delayMicroseconds(tone);
        expander->digitalWrite(EXP_IO_BEE_EN, LOW);
        delayMicroseconds(tone);
    }
}