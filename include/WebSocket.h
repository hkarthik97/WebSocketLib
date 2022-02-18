#ifndef __WEBSOCKET_H_
#define __WEBSOCKET_H_



#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <ESPAsyncWebServer.h>
#define SerialMonitor 301
int sendDataSerial(String uartData);
const int ledPin = 2;
void notifyClients(String ardData);
void notifyClientsReceived(String ardData);
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
           void *arg, uint8_t *data, size_t len);
void initWebSocket();
String processor(const String& var);
void clientscleanup();
#endif
