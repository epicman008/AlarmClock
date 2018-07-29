#ifndef SSD1306_H
#define SSD1306_H

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
#define TIME_DELIMITER ":"
#define DATE_DELIMITER "-"

#define CLOCK_START_POS 0,10
#define SEC_START_POS 90,24

void setupSSD1306();

void updateInterface(bool alarmSet,uint8_t alarmMin, uint8_t alarmHour, uint8_t cSec, uint8_t cMin, uint8_t cHour, uint8_t cDay, uint8_t cMonth,uint8_t cYear);

#endif
