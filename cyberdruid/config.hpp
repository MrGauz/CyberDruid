#ifndef CONFIG_HPP
#define CONFIG_HPP

// Screen config
const uint8_t SCREEN_WIDTH   = 128;
const uint8_t SCREEN_HEIGHT  = 64;
const int     OLED_RESET     = -1;
const uint8_t SCREEN_ADDRESS = 0x3C;
const uint8_t SDA_PIN        = D2;
const uint8_t SCL_PIN        = D1;

// Plant config
const String  PLANT_NAME         = "Basilikum";
const uint8_t MOISTURE_THRESHOLD = 50;
const uint8_t IMAGE_HEIGHT       = 40;
const uint8_t IMAGE_WIDTH        = 40;

// Sensor config
const int SENSOR_DRY_VALUE = 395;
const int SENSOR_WET_VALUE = 260;
const int SENSOR_ADDRESS   = A0;

// Network config
const unsigned long CONNECTION_TIMEOUT = 30000UL; // 30 seconds
const String        API_HOST           = "api.telegram.org";
const int           API_PORT           = 443;
const unsigned long ALERT_COOLDOWN     = (6UL * 60 * 60 * 1000); // 6 hours

// Secrets
// TODO: change to your WiFi and Telegram bot credentials
const String WIFI_SSID   = "Your WiFi SSID";
const char   WIFI_PASS[] = "XXX";
const String BOT_TOKEN   = "0000000000:AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
const String CHAT_ID     = "123456789";

#endif  // CONFIG_HPP