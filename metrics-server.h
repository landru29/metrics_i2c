
#ifndef __METRICS_SERVER__H__
#define __METRICS_SERVER__H__

#include "wifi.h"
#include "metrics.h"
#include "warp10.h"
#include <Ticker.h>

#define READ_BUFFER_SIZE 200
#define WRITE_BUFFER_SIZE 50


void initMetrics(const char* hostname);


#endif