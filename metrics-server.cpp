#include <Arduino.h>
#include "metrics-server.h"
#include "metrics-client.h"
#include <Wire.h>


WifiConnect* MetricsServer::wifi = new WifiConnect("metrics");
Metrics* MetricsServer::metrics = new Metrics();
Warp10* MetricsServer::warp10 = new Warp10();
Ticker* MetricsServer::timestampTicker = new Ticker();
char MetricsServer::resultBuffer[WRITE_BUFFER_SIZE] = "";
char MetricsServer::resultBufferLength = 0;
long MetricsServer::timestamp = 0;

void MetricsServer::tickTimestamp() {
  timestamp++;
}

void MetricsServer::registerTsTicker() {
  timestampTicker->attach(1, tickTimestamp);
}

int MetricsServer::wireRead(char* buf, int len) {
  int cursor = 0;
  while ((Wire.available()>0) && (cursor < len)) {
    buf[cursor++] = Wire.read();
  }
  return cursor;
}

void MetricsServer::receiveEvent(int howMany) {
  char buffer[READ_BUFFER_SIZE];
  char command = 0;

  if (Wire.available() > 0) {
    // Read Command Byte
    int command = Wire.read();

    // Read body command
    int length = wireRead(buffer, READ_BUFFER_SIZE);
    
    switch(command) {

      case COMMAND_WIFI_CONNECT: {
        Serial.println("Wifi connect");
        bool wifiResult = wifi->startWPSPBC();
        resultBuffer[0] = wifiResult ? 1 : 0;
        resultBufferLength = 1;
        break;
      }

      case COMMAND_REQUEST_TIMESTAMP:{
        Serial.println("Request timestamp");
        timestamp = warp10->getTimestamp();
        // Continue ...
      }
      
      case COMMAND_GET_TIMESTAMP:{
        char *buf = (char*)&timestamp;
        for(int i=0; i<4; i++) {
          resultBuffer[i] = buf[i];
        }
        resultBufferLength = 4;
        break;
      }
      
      case COMMAND_METRICS_FLUSH: {
        int httpCode = metrics->flushData();
        char *buf = (char*)&httpCode;
        for(int i=0; i<2; i++) {
          resultBuffer[i] = buf[i];
        }
        resultBufferLength = 2;
        break;
      }

      case COMMAND_PING: {
        resultBuffer[0] = 1;
        resultBufferLength = 2;
        break;
      }

      default: {
        Serial.print("Unknown command ");
        Serial.println(command);
        return;
      }
    }
  } else {
    for(int i=0; i<resultBufferLength; i++) {
      Wire.write(resultBuffer[i]);
    }
  }

}

void MetricsServer::registerI2C() {
    Wire.begin(I2C_ADDRESS);
    Wire.onReceive(receiveEvent);
}


void MetricsServer::initMetrics() {
    registerI2C();
    registerTsTicker();
}
