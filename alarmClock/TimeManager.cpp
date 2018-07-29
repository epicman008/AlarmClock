#include "TimeManager.h"

void setupTime() {
  Wire.begin();
}

byte bcdToDec(byte val)
{
  return ( (val / 16 * 10) + (val % 16) );
}

byte decToBcd(byte val)
{
  return ( (val / 10 * 16) + (val % 10) );
}

void setTime(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
{
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}

void getTime(byte tempTime[7])
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  tempTime[0] = bcdToDec(Wire.read() & 0x7f);
  tempTime[1] = bcdToDec(Wire.read());
  tempTime[2] = bcdToDec(Wire.read() & 0x3f);
  tempTime[3] = bcdToDec(Wire.read());
  tempTime[4] = bcdToDec(Wire.read());
  tempTime[5] = bcdToDec(Wire.read());
  tempTime[6] = bcdToDec(Wire.read());
}

void getFutureTime(TimeValues value, uint8_t nrOf, byte tempTime[7]) {
  byte _time = 0;
  switch (value) {
    case SECONDS:
      _time = tempTime[0];
      tempTime[0] = (_time + nrOf) % 60;
      tempTime[1] += ((_time + nrOf) / 60) % 60;
      break;
    case MINUTES:
      _time = tempTime[1];
      tempTime[1] = (_time + nrOf) % 60;
      tempTime[2] = ((_time + nrOf) / 60) % 24;
      break;
  }
}

void parseTime(String timeString, byte tempTime[7]) {
  char c = 0;
  String t;
  uint8_t nrOf = 0;
  for (int i = 0; i <= timeString.length(); ++i) {
    c = timeString.charAt(i);
    if (c == SEPARATION_CHARACTER || c == 0) {
      if (nrOf == 6) {
        tempTime[nrOf] = t.substring(2, 4).toInt();
      }
      else {
        tempTime[nrOf] = t.toInt();
      }
      t = "";
      nrOf++;
      if (nrOf == 3) {
        nrOf++;
      }
    } else {
      t += c;
    }
  }
}

void printTime(byte tempTime[7]){
  for(uint8_t i=0;i<7;++i){
    Serial.print(tempTime[i]);
    if(i!=7-1){
      Serial.print(F("-"));
    }
  }
  Serial.println();
}

bool equalTime(byte firstTime[7], byte secondTime[7],uint8_t start,uint8_t End){
  for(uint8_t i=start;i<End;++i){
    if(firstTime[i]!=secondTime[i]){
      return false;
    }
  }
  return true;
}

