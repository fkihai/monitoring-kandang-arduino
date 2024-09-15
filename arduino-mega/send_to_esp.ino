void sendDataToEsp() {
  DynamicJsonDocument doc(1024);

  for (int i = 0; i < 8; i++) {
    doc[String("NH3_Sensor") + (i + 1)] = sensorData.getNH3(i);
    doc[String("NO2_Sensor") + (i + 1)] = sensorData.getNO2(i);
  }

  for (int i = 0; i < 4; i++) {
    doc[String("Hum_Sensor") + (i + 1)] = sensorData.getHUM(i);
    doc[String("Temp_Sensor") + (i + 1)] = sensorData.getTEMP(i);
  }

  String requestBody;
  serializeJson(doc, requestBody);
  Serial3.println(requestBody);
}
