#ifndef ALARM_H
#define ALARM_H

#include <Arduino.h>

#define BUZZER_PIN 9

void setupBuzzer();

void buzzerOn(uint16_t Hz);

void buzzerOff();

#endif
