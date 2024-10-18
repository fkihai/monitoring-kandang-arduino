#include <Wire.h>
#include <Adafruit_SHT31.h>
#include <ArduinoJson.h>

#define NO2_P1 A0
#define NH3_P1 A1

#define NO2_P2 A2
#define NH3_P2 A3

#define NO2_P3 A4
#define NH3_P3 A5

#define NO2_P4 A6
#define NH3_P4 A7

#define NO2_P5 A8
#define NH3_P5 A9

#define NO2_P6 A10
#define NH3_P6 A11

#define NO2_P7 A12
#define NH3_P7 A13

#define NO2_P8 A14
#define NH3_P8 A15

#define RELAY 7
#define BUTTON 11
#define TCA9548A_ADDR 0x70

Adafruit_SHT31 sht[4];

const int channel[] = { 3, 4, 5, 7 };
const int NO2_PINS[] = { NO2_P1, NO2_P2, NO2_P3, NO2_P4, NO2_P5, NO2_P6, NO2_P7, NO2_P8 };
const int NH3_PINS[] = { NH3_P1, NH3_P2, NH3_P3, NH3_P4, NH3_P5, NH3_P6, NH3_P7, NH3_P8 };


unsigned long previousMillis = 0;
const long interval = 60000;

bool overThreshold = false;

/* Initialize var sensor */
class SensorData {

private:
  float NH3[8];
  float NO2[8];
  float HUM[4];
  float TEMP[4];

public:
  SensorData() {
    for (int i = 0; i < 8; i++) {
      NH3[i] = 0.0;
      NO2[i] = 0.0;
    }
    for (int i = 0; i < 4; i++) {
      HUM[i] = 0.0;
      TEMP[i] = 0.0;
    }
  }

  void setNH3(int index, float value) {
    if (index >= 0 && index < 8) {
      NH3[index] = value;
    }
  }

  float getNH3(int index) {
    if (index >= 0 && index < 8) {
      return NH3[index];
    }
    return 0.0;
  }

  void setNO2(int index, float value) {
    if (index >= 0 && index < 8) {
      NO2[index] = value;
    }
  }

  float getNO2(int index) {
    if (index >= 0 && index < 8) {
      return NO2[index];
    }
    return 0.0;
  }

  void setHUM(int index, float value) {
    if (index >= 0 && index < 4) {
      HUM[index] = value;
    }
  }

  float getHUM(int index) {
    if (index >= 0 && index < 4) {
      return HUM[index];
    }
    return 0.0;
  }

  void setTEMP(int index, float value) {
    if (index >= 0 && index < 4) {
      TEMP[index] = value;
    }
  }

  float getTEMP(int index) {
    if (index >= 0 && index < 4) {
      return TEMP[index];
    }
    return 0.0;
  }
};

SensorData sensorData;




