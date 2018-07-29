#include "Alarm.h"

void setupBuzzer(){
  pinMode(BUZZER_PIN, OUTPUT);
}


void buzzerOn(uint16_t Hz){
  tone(BUZZER_PIN,Hz);
}

void buzzerOff(){
  noTone(BUZZER_PIN);
}

