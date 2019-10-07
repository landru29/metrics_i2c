#ifndef __METRICS_SERVER__H__
#define __METRICS_SERVER__H__

#include "wifi-connect.h"
#include "metrics.h"
#include "warp10.h"
#include <Ticker.h>

#define READ_BUFFER_SIZE 200
#define WRITE_BUFFER_SIZE 50


// void initMetrics(const char* hostname);

class MetricsServer {
    public:
        static void initMetrics();
    
    private:
        static WifiConnect* wifi;
        static Metrics* metrics;
        static Warp10* warp10;
        static Ticker* timestampTicker;
        static char resultBuffer[WRITE_BUFFER_SIZE];
        static char resultBufferLength;
        static long timestamp;

        static void tickTimestamp();
        static void registerTsTicker();
        static int wireRead(char* buf, int len);
        static void receiveEvent(int howMany);
        static void registerI2C();


};


#endif