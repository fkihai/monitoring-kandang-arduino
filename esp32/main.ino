
String data;
String jsonData = "{\"NH3_Sensor1\": 342, \"NO2_Sensor1\": 344, \"NH3_Sensor2\": 360, \"NO2_Sensor2\": 365, \"NH3_Sensor3\": 339, \"NO2_Sensor3\": 346, \"NH3_Sensor4\": 308, \"NO2_Sensor4\": 338, \"NH3_Sensor5\": 269, \"NO2_Sensor5\": 289, \"NH3_Sensor6\": 326, \"NO2_Sensor6\": 268, \"NH3_Sensor7\": 304, \"NO2_Sensor7\": 380, \"NH3_Sensor8\": 279, \"NO2_Sensor8\": 303, \"Hum_Sensor1\": 0, \"Temp_Sensor1\": 0, \"Hum_Sensor2\": 0, \"Temp_Sensor2\": 0, \"Hum_Sensor3\": 0, \"Temp_Sensor3\": 0, \"Hum_Sensor4\": 0, \"Temp_Sensor4\": 0}";

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("ESP8266 sudah terkoneksi dengan WiFi!");
  Serial.println("IP address ESP8266: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (Serial.available()) {
    data = Serial.readStringUntil('\n');
    sendToServer(data);
  }
}

void sendToServer(String jsonData) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(jsonData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Data berhasil dikirim!");
      Serial.println("Respons: " + String(httpResponseCode));
    } else {
      Serial.println("Terjadi kesalahan saat mengirim data.");
      Serial.println("Status Kode: " + String(httpResponseCode));
      String response = http.getString();
      Serial.println("Respons: " + response);
    }
    http.end();
  } else {
    Serial.println("Koneksi Wi-Fi tidak tersedia.");
  }
}

