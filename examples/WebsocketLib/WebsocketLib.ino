#include "WebSocket.h"

void setup() {
  
  Serial.begin(115200);
  Serial2.begin(115200);
  WiFi.begin("Z U S A N 4G", "12345678");
  initWebSocket();
}

void loop() {
clientscleanup();
}
