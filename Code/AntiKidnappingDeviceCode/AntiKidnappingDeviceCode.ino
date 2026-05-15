#include <WiFi.h>
#include "esp_wifi.h"
#include "esp_pm.h"

const char* ssid = "ESP32-Beacon";  // Wi-Fi SSID
const char* password = "";          // Open network

void setup() {
  // Reduce CPU frequency to save power
  setCpuFrequencyMhz(80);  // 80 MHz instead of 160/240

  //Enable Wi-Fi AP mode only
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  //reduce transmit power (default is 78; 20 is lowest)
  esp_wifi_set_max_tx_power(20); // units = 0.25 dBm (20 = 5 dBm)

  // Enable Wi-Fi modem sleep (saves power between beacons)
  esp_wifi_set_ps(WIFI_PS_MIN_MODEM);
}

void loop() {
  // Minimal loop to let hardware sleep where possible
  delay(1000);
}