#ifndef __HTTP__H__
#define __HTTP__H__

typedef struct Sensor Sensor;
struct Sensor
{
    int oven;
    int ambient;
    long timestamp;
};

class Metrics {
  public:
    Metrics();
    void addValue(int oven, int ambient, long timestamp);
    int flushData();
    void addValueAndFlush(int val, int ambient, long timestamp);
    int getBufferSize();

  private:
    Sensor* sensor;
    int bufferSize;

    static const char* url;
};

#endif
