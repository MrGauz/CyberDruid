#ifndef TELEGRAM_ALERTS_HPP
#define TELEGRAM_ALERTS_HPP

#include <Wire.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#include "config.hpp"

unsigned long lastAlert = 0;

void sendAlert(int moisturePercentage) {
  if ((lastAlert && lastAlert + ALERT_COOLDOWN > millis()) || WiFi.status() != WL_CONNECTED) {
    return;
  }

  Serial.println(F("Sending alert: ") + PLANT_NAME + F(" is at ") + moisturePercentage + F("%"));
  String msg = F("🪴 ") + PLANT_NAME + F("'s soil moisture is at ") + moisturePercentage + F("% — please water it.");
  msg.replace(" ", "%20");

  String url = F("/bot") + BOT_TOKEN + F("/sendMessage?chat_id=") + CHAT_ID + F("&text=") + msg;
  String request = F("POST ") + url + F(" HTTP/1.1\r\nHost: ") + API_HOST + F("\r\nConnection: close\r\n\r\n");

  WiFiClientSecure client;
  client.setInsecure(); // Disable SSL certificate verification

  if (!client.connect(API_HOST, API_PORT)) {
    Serial.println(F("Failed to connect to ") + API_HOST);
    client.stop();
    return;
  }

  const int delayMs = 500;
  int attempts = 0;
  client.print(request);
  while (!client.available() && attempts < CONNECTION_TIMEOUT / delayMs) {
    attempts++;
    delay(delayMs);
  }

  if (client.available()) {
    lastAlert = millis();
  } else {
    Serial.println(F("Failed to send alert after ") + String(CONNECTION_TIMEOUT / 1000) + F(" seconds"));
  }
  client.stop();
}

#endif  // TELEGRAM_ALERTS_HPP
