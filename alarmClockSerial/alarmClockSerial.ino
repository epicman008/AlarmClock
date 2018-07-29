void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    String temp = Serial.readStringUntil('\n');
    if (temp=="A") {
      Serial.print("ALARMSET 0-30-12\n");
    }else if(temp=="T"){
      //TODO
    }
  }

}
