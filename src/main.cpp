#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <SoftwareSerial.h>


#ifndef ETH_PHY_MDC
#define ETH_PHY_TYPE ETH_PHY_LAN8720
#if CONFIG_IDF_TARGET_ESP32
#define ETH_PHY_ADDR  1
#define ETH_PHY_MDC   23
#define ETH_PHY_MDIO  18
#define ETH_PHY_POWER 16
#define ETH_CLK_MODE  ETH_CLOCK_GPIO17_OUT
#elif CONFIG_IDF_TARGET_ESP32P4
#define ETH_PHY_ADDR  0
#define ETH_PHY_MDC   31
#define ETH_PHY_MDIO  52
#define ETH_PHY_POWER 51
#define ETH_CLK_MODE  EMAC_CLK_EXT_IN
#endif
#endif

#include <ETH.h>
#include "const.h"
#include "function.h"


void setup() {
  Serial.begin(9600);
  pinMode(relay1, OUTPUT);
  digitalWrite(relay1, LOW);
  pinMode(relay2, OUTPUT);
  digitalWrite(relay2, LOW);
  pinMode(relay3, OUTPUT);
  digitalWrite(relay3, LOW);
  pinMode(relay4, OUTPUT);
  digitalWrite(relay4, LOW);
  ETH.begin();
  delay(2000);
  if (ETH.config(staticIP, gateway, subnet, dns1, secondaryDNS)) {
      //Serial.printf("Статична IP-конфігурація встановлена.\n");
  } else {
      //Serial.printf("Помилка встановлення статичної IP-конфігурації.\n");
  }
  delay(2000);
  WiFi.onEvent(onEvent);
  cmdUdp.begin(localPort);
}
void loop() {
  handle_custom_commands();  // UDP команди приходять миттєво
  update_relay_timers();    // Таймери перевіряються кожну ітерацію loop
}
