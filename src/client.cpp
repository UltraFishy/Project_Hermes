#include <WiFi.h>
#include <WiFiClient.h>

const char *ssid = "ESP32-AP"; // SSID of the AP
const char *password = "123456789"; // Password of the AP
const char *host = "192.168.4.1"; // IP address of the TCP server (AP)

void setup() {
  Serial.begin(115200);

  // Connect to the AP
  Serial.println("Connecting to AP...");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to AP...");
  }

  Serial.println("Connected to AP");
}

void loop() {
  if (Serial.available()) {
    // Read data from serial and send to server
    char c = Serial.read();
    WiFiClient client;
    if (client.connect(host, 80)) {
      client.write(c);
      client.stop();
    } else {
      Serial.println("Connection failed");
    }
  }
}
