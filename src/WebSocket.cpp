#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include "home_page.h"
#include "login_page.h"
#include "WebSocket.h"
#include "sd_card.h"
#define SerialUart Serial2
int Wifi_check_count = 1;
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
bool ledState = 0;
int sendDataSerial(String uartData){
  SerialUart.println(uartData);
}

void notifyClients(String ardData) {
  ws.textAll("Sent : "+ardData);
}

void notifyClientsReceived(String ardData) {
  ws.textAll("Received : "+ardData);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    if (strcmp((char*)data, "toggle") == 0) {
      ledState = !ledState;
//      notifyClients();
    }
      else{
        Serial.println(String((char*)data));
        String receivedData = String((char*)data);
        notifyClients(receivedData);
        sendDataSerial(receivedData);
        
      }
    }
  }


void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}
String processor(const String& var) {
  if (var == "STATE") {
    if (ledState) {
      return "ON";
    }
    else {
      return "OFF";
    }
  }
  return String();
}
void initWebSocket() {
  
  // Connect to Wi-Fi
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
   

  // Print ESP Local IP Address
  
 
  Serial.println(WiFi.localIP());
  ws.onEvent(onEvent);
  server.addHandler(&ws);
  server.on("/home", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", home_page, processor);
  });
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", login_page, processor);
  });
  server.on("/sdcard", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD, "/log.txt", "text/html");
  });
  AsyncElegantOTA.begin(&server);
  // Start server
  server.begin();
  
}
void clientscleanup(){
  ws.cleanupClients();
}
