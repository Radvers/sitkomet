static bool eth_connected = false;
void onEvent(arduino_event_id_t event) {
  switch (event) {
    case ARDUINO_EVENT_ETH_START:
      Serial.println("ETH Started");
      // The hostname must be set after the interface is started, but needs
      // to be set before DHCP, so set it from the event handler thread.
      ETH.setHostname("esp32-ethernet");
      break;
    case ARDUINO_EVENT_ETH_CONNECTED: Serial.println("ETH Connected"); break;
    case ARDUINO_EVENT_ETH_GOT_IP:
      Serial.println("ETH Got IP");
      Serial.println(ETH.localIP());
      eth_connected = true;
      break;
    case ARDUINO_EVENT_ETH_DISCONNECTED:
      Serial.println("ETH Disconnected");
      eth_connected = false;
      break;
    case ARDUINO_EVENT_ETH_STOP:
      Serial.println("ETH Stopped");
      eth_connected = false;
      break;
    default: break;
  }
}
void handle_custom_commands() {
    int packetSize = cmdUdp.parsePacket();
    if (packetSize) {
        char packetBuffer[255];
        int len = cmdUdp.read(packetBuffer, 255);
        if (len > 0) packetBuffer[len] = 0;

        String command = String(packetBuffer);
        command.trim();

        // ОБРОБКА КОМАНДИ А (Реле 2)
        if (command == "CMD_A") {
            digitalWrite(relay1, HIGH);
            r1StartTime = millis();
            r1Active = true;
            Serial.println("Relay 1: ON (Timer started)");
        }
        // ОБРОБКА КОМАНДИ Б (Реле 1)
        else if (command == "CMD_B") {
            digitalWrite(relay2, HIGH);
            r2StartTime = millis();
            r2Active = true;
            Serial.println("Relay 2: ON (Timer started)");
        }
        // ОБРОБКА КОМАНДИ C (Реле 3)
        else if (command == "CMD_C") {
            digitalWrite(relay3, HIGH);
            r3StartTime = millis();
            r3Active = true;
            Serial.println("Relay 3: ON (Timer started)");
        }
        // ОБРОБКА КОМАНДИ D (Реле 4)
        else if (command == "CMD_D") {
            digitalWrite(relay4, HIGH);
            r4StartTime = millis();
            r4Active = true;
            Serial.println("Relay 4: ON (Timer started)");
        }
    }
}
// Функція оновлення станів (викликається в loop)
void update_relay_timers() {
    unsigned long currentMillis = millis();

    // Перевірка для Реле 1
    if (r1Active && (currentMillis - r1StartTime >= r1Duration)) {
        r1Active = false;
        Serial.println("Relay 1: OFF (Auto)");
        digitalWrite(relay1, LOW);
    }

    // Перевірка для Реле 2
    if (r2Active && (currentMillis - r2StartTime >= r2Duration)) {
        r2Active = false;
        Serial.println("Relay 2: OFF (Auto)");
        digitalWrite(relay2, LOW);
    }

    // Перевірка для Реле 3
    if (r3Active && (currentMillis - r3StartTime >= r3Duration)) {
        r3Active = false;
        Serial.println("Relay 3: OFF (Auto)");
        digitalWrite(relay3, LOW);
    }

    // Перевірка для Реле 4
    if (r4Active && (currentMillis - r4StartTime >= r4Duration)) {
        r4Active = false;
        Serial.println("Relay 4: OFF (Auto)");
        digitalWrite(relay4, LOW);
    }
}