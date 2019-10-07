#include <Arduino.h>
#include "wifi.h"
#include "metrics.h"
#include "warp10.h"
#include "led.h"
#include "communication.h"
#include <Wire.h>
#include <Ticker.h>

#define READ_BUFFER_SIZE 200
#define WRITE_BUFFER_SIZE 50


char resultBuffer[WRITE_BUFFER_SIZE];
char resultBufferLength = 0;

volatile long globalTimestamp = 0;

WifiConnect* myWifi;
Metrics* metrics;
Warp10* warp10;
Ticker timestampTicker;

void tickTimestamp() {
  globalTimestamp++;
}


void setup() {

  myWifi = new WifiConnect("metrics");
  metrics = new Metrics();
  warp10 = new Warp10();

  Wire.begin(I2C_ADDRESS);
  Wire.onReceive(receiveEvent);
  
  Serial.begin(9600);

  timestampTicker.attach(1, tickTimestamp);
  
}

int wireRead(char* buf, int len) {
  int cursor = 0;
  while ((Wire.available()>0) && (cursor < len)) {
    buf[cursor++] = Wire.read();
  }
  return cursor;
}

void receiveEvent(int howMany) {
  char buffer[READ_BUFFER_SIZE];
  char command = 0;

  if (Wire.available() > 0) {
    // Read Command Byte
    int command = Wire.read();

    // Read body command
    int length = wireRead(buffer, READ_BUFFER_SIZE);
    
    switch(command) {

      case COMMAND_WIFI_CONNECT:
        Serial.println("Wifi connect");
        bool wifiResult = myWifi->startWPSPBC();
        resultBuffer[0] = wifiResult ? 1 : 0;
        resultBufferLength = 1;
        break;

      case COMMAND_REQUEST_TIMESTAMP:
        Serial.println("Request timestamp");
        globalTimestamp = warp10->getTimestamp();
        // Continue ...
      
      case COMMAND_GET_TIMESTAMP:
        char *buf = (char*)&globalTimestamp;
        for(int i=0; i<4; i++) {
          resultBuffer[i] = buf[i];
        }
        resultBufferLength = 4;
        break;
      
      case COMMAND_METRICS_FLUSH:
        int httpCode = metrics->flushData();
        char *buf = (char*)&httpCode;
        for(int i=0; i<2; i++) {
          resultBuffer[i] = buf[i];
        }
        resultBufferLength = 2;
        break;

      default:
        Serial.print("Unknown command ");
        Serial.println(command);
        return;
    }


  } else {
    for(int i=0; i<resultBufferLength; i++) {
      Wire.write(resultBuffer[i]);
    }
  }

}


void loop() {


}
