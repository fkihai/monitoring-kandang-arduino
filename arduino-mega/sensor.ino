void readSensorGas() {
  for (int i = 0; i < 8; i++) {
    sensorData.setNO2(i, analogRead(NO2_PINS[i]));
    sensorData.setNH3(i, analogRead(NH3_PINS[i]));
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
