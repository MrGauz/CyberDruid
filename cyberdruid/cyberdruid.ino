#include <Wire.h>

#include "config.hpp"
#include "display.hpp"
#include "wifiSetup.hpp"
#include "telegramAlerts.hpp"

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int pastReadings[10] = {0};

void setup() {
  Serial.begin(115200);

  Wire.begin(SDA_PIN, SCL_PIN);
  initDisplay(oled);

  connectToWiFi(oled);
}

void loop() {
  int moisturePercentage = readMoisturePercentage();
  updateDisplay(oled, moisturePercentage);

  if (moisturePercentage < MOISTURE_THRESHOLD) {
    sendAlert(moisturePercentage);
    isInverted = !isInverted;
    oled.invertDisplay(isInverted);
  } else {
    isInverted = false;
    oled.invertDisplay(isInverted);
  }

  oled.display();
  delay(1000);
}

int readMoisturePercentage() {
  int rawSensorValue = analogRead(SENSOR_ADDRESS);
  int moisturePercentage = map(rawSensorValue, SENSOR_DRY_VALUE, SENSOR_WET_VALUE, 0, 100);
  moisturePercentage = constrain(moisturePercentage, 0, 100);
  
  // Shift past readings & save new value
  memmove(pastReadings, pastReadings + 1, 9 * sizeof(pastReadings[0]));
  pastReadings[9] = moisturePercentage;

  // Sum non-zero entries and count them
  int sum = 0, count = 0;
  for (int v : pastReadings) {
    if (v) { sum += v; ++count; }
  }

  int avg = count ? sum / count : 0;

  Serial.print(F("Raw ADC Value, 1-1024: "));
  Serial.print(rawSensorValue);
  Serial.print(F(" | Soil Moisture, %: "));
  Serial.print(moisturePercentage);
  Serial.print(F(" | Rolling Average, %: "));
  Serial.println(avg);

  return avg;
}