void readSensorGas() {
  overThreshold = false;
  for (int i = 0; i < 8; i++) {
    int no2Raw = analogRead(NO2_PINS[i]);
    int nh3Raw = analogRead(NH3_PINS[i]);

    float no2Mapped = (no2Raw * (10.0 - 0.05) / 1023.0) + 0.05;
    int nh3Mapped = map(nh3Raw, 0, 1023, 0, 500);

    sensorData.setNO2(i, no2Mapped);
    sensorData.setNH3(i, nh3Mapped);

    if (nh3Mapped > 400) {
      overThreshold = true;
    }
  }
}

void fanAction() {
  if (overThreshold) {
    digitalWrite(RELAY, HIGH);  // Set output HIGH
  } else {
    digitalWrite(RELAY, LOW);   // Set output LOW
  }
}


void readSensorSHT() {
  for (int i = 0; i < 4; i++) {
    tca9548a_select(channel[i]);
    sensorData.setTEMP(i, isnan(sht[i].readTemperature()) ? 0 : sht[i].readTemperature());
    sensorData.setHUM(i, isnan(sht[i].readHumidity()) ? 0 : sht[i].readHumidity());
  }
}

void debugSensorGas() {
  readSensorGas();
  for (int i = 0; i < 8; i++) {
    Serial.print("NO2_P" + String(i + 1));
    Serial.print(" : ");
    Serial.println(sensorData.getNO2(i));
    Serial.print("NH3_P" + String(i + 1));
    Serial.print(" : ");
    Serial.println(sensorData.getNH3(i));
    Serial.println("");
    delay(500);
  }
}

void debugSensorSHT() {
  readSensorSHT();
  for (int i = 0; i < 4; i++) {
    Serial.print("TEMP_" + String(i + 1));
    Serial.print(" : ");
    Serial.println(sensorData.getTEMP(i));
    Serial.print("HUM_" + String(i + 1));
    Serial.print(" : ");
    Serial.println(sensorData.getHUM(i));
    Serial.println("");
    delay(1000);
  }
}

void testRelay() {
  String data = Serial.readStringUntil('\n');
  if (data == "a"  ) {
    digitalWrite(RELAY, HIGH);
    Serial.println("HIDUP");
  } if (data == "b") {
    digitalWrite(RELAY, LOW);
    Serial.println("MATI");
  }
}

