#include "communication.h"
#include "Wire.h"


Communication::Communication() {

}

bool Communication::wifiConnect() {
    Wire.beginTransmission(I2C_ADDRESS);
    Wire.write(COMMAND_WIFI_CONNECT);
    Wire.endTransmission();
    Wire.requestFrom(I2C_ADDRESS, 1);
    if (Wire.available() == 1) {
        return !!Wire.read();
    }
    return false;
}


long Communication::getTimestamp() {
    Wire.beginTransmission(I2C_ADDRESS);
    Wire.write(COMMAND_GET_TIMESTAMP);
    Wire.endTransmission();
    Wire.requestFrom(COMMAND_GET_TIMESTAMP, 4);
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

int Communication::flushMetrics() {
    Wire.beginTransmission(I2C_ADDRESS);
    Wire.write(COMMAND_METRICS_FLUSH);
    Wire.endTransmission();
    Wire.requestFrom(COMMAND_GET_TIMESTAMP, 2);
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