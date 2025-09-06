#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "config.hpp"
#include "bitmaps.hpp"

bool isInverted = false;

void initDisplay(Adafruit_SSD1306 &oled) {
  if (!oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);  // Loop indefinitely
  }

  oled.clearDisplay();
  oled.setTextColor(SSD1306_WHITE);
  oled.display();
}

void updateDisplay(Adafruit_SSD1306 &oled, int moisturePercentage) {
  oled.clearDisplay();
  oled.drawBitmap(1, 25, BASIL_BITMAP, IMAGE_WIDTH, IMAGE_HEIGHT, SSD1306_WHITE);

  oled.setTextSize(2);
  oled.setCursor(1, 1);
  oled.print(PLANT_NAME);

  oled.setTextSize(1);
  oled.setCursor(43, 25);
  oled.print(F("Soil moisture:"));

  oled.setTextSize(3);
  oled.setCursor(48, 40);
  oled.print(moisturePercentage);
  oled.setTextSize(2);
  oled.print(F("%"));
}

#endif  // DISPLAY_HPP