#include "TimeManager.h"
#include "Alarm.h"
#include "SSD1306.h"

#define INTERRUPT_PIN 2
#define BAUDRATE_SERIAL 9600
#define SET_TIME_KEYWORD "TIME"
#define SET_ALARM_KEYWORD "ALARMSET"
#define NOT_SET_ALARM "ALARMOFF"
#define KEYWORD_DELIMITER ' '
#define SET_ENDING '\n'
#define BUZZER_TONE 2000
#define ALARM_REQUEST "A\n"
#define TIME_REQUEST "T\n"

#define TIME_REQUEST_DELAY 20  //Days
#define ALARM_REQUEST_DELAY 10 //Minutes

#define TIME_ARRAY_LENGHT 7

uint8_t tempTime[TIME_ARRAY_LENGHT];
uint8_t alarm[3] = {0, 0, 0};

bool alarmOn = false;
uint8_t previousAlarmDate[TIME_ARRAY_LENGHT];

bool alarmRequest = false;
bool timeRequest = false;

bool alarmSet = false;

void setup() {
  setupTime();
  setupBuzzer();
  setupSSD1306();
  Serial.begin(BAUDRATE_SERIAL);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), interrupt, RISING);
  Serial.println(F("To set the time or alarm type: TIME/ALARMSET s-m-h-D-M-Y and end it with a \\n\nTo turn off the alarm type ALARMOFF*space*\\n"));
}

void interrupt() {
  alarmOn = false;
}

void loop() {
  getTime(tempTime);
  if (Serial.available()) {
    String setSort = Serial.readStringUntil(KEYWORD_DELIMITER);

    if (setSort == F(SET_TIME_KEYWORD)) {
      String timeString = Serial.readStringUntil(SET_ENDING);
      parseTime(timeString, tempTime);
      setTime(tempTime[SECONDS], tempTime[MINUTES], tempTime[HOURS], 0, tempTime[DAYS], tempTime[MONTHS], tempTime[YEARS]);
      Serial.print(F("Time is set: "));
      printTime(tempTime);

    } else if (setSort == F(SET_ALARM_KEYWORD)) {
      alarmSet = true;
      String alarmString = Serial.readStringUntil(SET_ENDING);
      Serial.print(F("Alarm is set: "));

      for (uint8_t i = 0; i < TIME_ARRAY_LENGHT; ++i) {
        previousAlarmDate[i] = 0;
      }
      
      if (alarmString != "") {
        parseTime(alarmString, alarm);
        printTime(alarm);
      }

    } else if (setSort == F(NOT_SET_ALARM)) {
      Serial.println("Alarm is turned off");
      alarmSet = false;
    }

  }

  updateInterface(alarmSet, alarm[MINUTES], alarm[HOURS], tempTime[SECONDS], tempTime[MINUTES], tempTime[HOURS], tempTime[DAYS], tempTime[MONTHS], tempTime[YEARS]);

  if (tempTime[MINUTES] % ALARM_REQUEST_DELAY == 0 && !alarmRequest) {
    alarmRequest = true;
    Serial.print(F(ALARM_REQUEST));
  } else if (tempTime[MINUTES] % ALARM_REQUEST_DELAY != 0) {
    alarmRequest = false;
  }

  if (tempTime[DAYS] % TIME_REQUEST_DELAY == 0 && !timeRequest) {
    timeRequest = true;
    Serial.print(F(TIME_REQUEST));
  } else if (tempTime[DAYS] % TIME_REQUEST_DELAY != 0) {
    timeRequest = false;
  }

  //Check if the alarm has to go off
  if (equalTime(tempTime, alarm, 1, 3) && alarmSet && !equalTime(tempTime, previousAlarmDate, 4)) {
    alarmOn = true;
    copyArray(previousAlarmDate, tempTime, TIME_ARRAY_LENGHT);
  }

  if (alarmOn) {
    playBuzzer();
  } else {
    buzzerOff();
  }
}

void playBuzzer() {
  if (tempTime[SECONDS] % 2 == 0) {
    buzzerOn(BUZZER_TONE);
  } else {
    buzzerOff();
  }
}

void copyArray(uint8_t a[], uint8_t b[], uint8_t l) {
  for (uint8_t i = 0; i < l; ++i) {
    a[i] = b[i];
  }
}

