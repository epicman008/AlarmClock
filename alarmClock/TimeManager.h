#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <Arduino.h>
#include <Wire.h>

#define DS3231_I2C_ADDRESS 0x68

#define SEPARATION_CHARACTER '-'

enum TimeValues {SECONDS, MINUTES, HOURS,DAYOFWEEK, DAYS, MONTHS, YEARS};

void setupTime();

void setTime(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year);

void getTime(byte tempTime[7]);

void getFutureTime(TimeValues value, uint8_t nrOf, byte tempTime[7]);

void parseTime(String timeString, byte tempTime[7]);//"01-29-20-21-04-2018" "s-m-h-D-M-Y"

void printTime(byte tempTime[7]);

bool equalTime(byte firstTime[7],byte secondTime[7],uint8_t start=0,uint8_t End=7);

#endif
