#include "metrics-client.h"
#include <Wire.h>
#include <Arduino.h>


MetricsClient::MetricsClient() {

}

bool MetricsClient::waitForData() {
    int counter = 0;
    int wait = 200;
    while(!Wire.available() && wait * counter / 1000 < TIMEOUT) {
        delay(wait);
        counter++;
    }
    return !!Wire.available();
}

bool MetricsClient::wifiConnect() {
    Wire.beginTransmission(I2C_ADDRESS);
    Wire.write(COMMAND_WIFI_CONNECT);
    Wire.endTransmission();
    Wire.requestFrom(I2C_ADDRESS, 1);
    this->waitForData();
    if (Wire.available() == 1) {
        return !!Wire.read();
    }
    return false;
}


long MetricsClient::requestTimestamp() {
    Wire.beginTransmission(I2C_ADDRESS);
    Wire.write(COMMAND_REQUEST_TIMESTAMP);
    Wire.endTransmission();
    Wire.requestFrom(I2C_ADDRESS, 4);
    this->waitForData();
    if (Wire.available() == 4) {
        char buf[4] = {0, 0, 0, 0};
        for(int i=0; i<4; i++) {
            buf[i] = Wire.read();
        }
        long *result;
        result = (long*)buf;
        return *result;
    }
    return 0L;

}

long MetricsClient::getTimestamp() {
    Wire.beginTransmission(I2C_ADDRESS);
    Wire.write(COMMAND_GET_TIMESTAMP);
    Wire.endTransmission();
    Wire.requestFrom(I2C_ADDRESS, 4);
    this->waitForData();
    if (Wire.available() == 4) {
        char buf[4] = {0, 0, 0, 0};
        for(int i=0; i<4; i++) {
            buf[i] = Wire.read();
        }
        long *result;
        result = (long*)buf;
        return *result;
    }
    return 0L;

}

int MetricsClient::flushMetrics() {
    Wire.beginTransmission(I2C_ADDRESS);
    Wire.write(COMMAND_METRICS_FLUSH);
    Wire.endTransmission();
    Wire.requestFrom(I2C_ADDRESS, 2);
    this->waitForData();
    if (Wire.available() == 2) {
        char buf[2] = {0, 0};
        for(int i=0; i<2; i++) {
            buf[i] = Wire.read();
        }
        int *result;
        result = (int*)buf;
        return *result;
    }
    return 0;
}