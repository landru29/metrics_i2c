
#ifndef __COMMUNICATION__H__
#define __COMMUNICATION__H__

#define I2C_ADDRESS 0x1357

#define COMMAND_WIFI_CONNECT 0x01
#define COMMAND_GET_TIMESTAMP 0x02
#define COMMAND_METRICS_FLUSH 0x03


class Communication {
    Communication();

  public:
    bool wifiConnect();
    long getTimestamp();
    int flushMetrics();
};


#endif