#include "SSD1306.h"

Adafruit_SSD1306 SSD1306(OLED_RESET);

void setupSSD1306() {
  SSD1306.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  SSD1306.display();
  SSD1306.clearDisplay();
  SSD1306.setTextColor(WHITE);
  SSD1306.setCursor(0, 0);
  SSD1306.println(F("Setup correct"));
  SSD1306.display();
}


//HELPING FUNCTIONS FOR UPDATEINTERFACE
bool printZero(uint8_t val) {
  if (val < 10) {
    SSD1306.print(F("0"));
    return true;
  }
  return false;
}

void updateAlDa(bool alarmSet, uint8_t alarmMin, uint8_t alarmHour, uint8_t cDay, uint8_t cMonth, uint8_t cYear) {
  SSD1306.setCursor(0, 0);
  SSD1306.setTextSize(1);

  SSD1306.print(F("Al "));
  if (alarmSet) {
    printZero(alarmHour);
    SSD1306.print(alarmHour);

    SSD1306.print(F(TIME_DELIMITER));
    printZero(alarmMin);
    SSD1306.print(alarmMin);
  } else {
    SSD1306.print(F("-----"));
  }



  SSD1306.print(F("  Da "));
  printZero(cDay);
  SSD1306.print(cDay);
  SSD1306.print(F(DATE_DELIMITER));

  printZero(cMonth);
  SSD1306.print(cMonth);
  SSD1306.print(F(DATE_DELIMITER));
  SSD1306.print(cYear);
}

void updateTime(uint8_t cSec, uint8_t cMin, uint8_t cHour) {
  SSD1306.setCursor(CLOCK_START_POS);
  SSD1306.setTextSize(3);
  printZero(cHour);
  SSD1306.print(cHour);
  SSD1306.print(F(TIME_DELIMITER));
  printZero(cMin);
  SSD1306.print(cMin);
  SSD1306.setTextSize(1);
  SSD1306.setCursor(SEC_START_POS);
  SSD1306.print(F(TIME_DELIMITER));
  printZero(cSec);
  SSD1306.print(cSec);
}

//THE UPDATEINTERFACE FUNCTION THAT MAKES USE OF THE HELPER FUNCTIONS
void updateInterface(bool alarmSet, uint8_t alarmMin, uint8_t alarmHour, uint8_t cSec, uint8_t cMin, uint8_t cHour, uint8_t cDay, uint8_t cMonth, uint8_t cYear) {
  SSD1306.clearDisplay();
  updateAlDa(alarmSet, alarmMin, alarmHour, cDay, cMonth, cYear);
  updateTime(cSec, cMin, cHour);
  SSD1306.display();
}
