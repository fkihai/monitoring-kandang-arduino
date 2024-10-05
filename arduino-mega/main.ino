
// #define development
#define production

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  Wire.begin();
  for (int i = 0; i < 4; i++) {
    tca9548a_select(channel[i]);
    sht[i] = Adafruit_SHT31();
    if (!sht[i].begin(0x44)) {
      Serial.print("Couldn't find SHT31 sensor ");
      Serial.println(i + 1);
    }
  }
}

void loop() {

#ifdef development
  // debugSensorSHT();
  debugSensorGas();
#endif

#ifdef production
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    readSensorGas();
    readSensorSHT();
    sendDataToEsp();
    previousMillis = currentMillis;
  }
  debugSerialEsp();
#endif

}


void tca9548a_select(uint8_t channel) {
  Wire.beginTransmission(TCA9548A_ADDR);
  Wire.write(1 << channel);
  Wire.endTransmission();
}


void debugSerialEsp() {
  if (Serial3.available()) {
    Serial.println(Serial3.readString());
  }
}
