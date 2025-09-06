#ifndef WIFI_SETUP_HPP
#define WIFI_SETUP_HPP

#include <ESP8266WiFi.h>

#include "config.hpp"

void connectToWiFi(Adafruit_SSD1306 &oled) {
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  String msg = F("Connecting to WiFi:\n") + String(WIFI_SSID);
  oled.setCursor(0, 0);
  oled.print(msg);
  oled.display();
  Serial.print(msg);

  const int delayMs = 500;
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < CONNECTION_TIMEOUT / delayMs) {
    oled.print(F("."));
    oled.display();
    Serial.print(F("."));
    attempts++;
    delay(delayMs);
  }

  Serial.println();
  oled.clearDisplay();
  oled.setCursor(0, 0);

  if (WiFi.status() != WL_CONNECTED) {
    msg = F("Failed to connect to WiFi. Telegram alerts\ndisabled. Stopping\nafter ")
        + String(CONNECTION_TIMEOUT / 1000) + F(" seconds.\nRestart or fix\ncredentials.");
    oled.print(msg);
    Serial.println(msg);
  } else {
    String ip = WiFi.localIP().toString();
    msg = F("Connected to WiFi:\n")+ String(WIFI_SSID) + F(".\nIP address:\n") + ip
        + F(".\nTelegram alerts\nenabled.");
    oled.print(msg);
    Serial.println(msg);
  }

  oled.display();
  delay(10000);
}

#endif  // WIFI_SETUP_HPP