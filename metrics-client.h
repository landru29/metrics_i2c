#ifndef __METRICS_CLIENT__H__
#define __METRICS_CLIENT__H__

#define I2C_ADDRESS 0x1357

#define TIMEOUT 10

#define COMMAND_WIFI_CONNECT        0x01
#define COMMAND_REQUEST_TIMESTAMP   0x02
#define COMMAND_GET_TIMESTAMP       0x03
#define COMMAND_METRICS_FLUSH       0x04


class MetricsClient {
    MetricsClient();

  public:
    bool wifiConnect();
    long getTimestamp();
    long requestTimestamp();
    int flushMetrics();
  private:
    bool waitForData();
};


#endif