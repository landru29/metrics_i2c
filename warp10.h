#ifndef __WARP_TEN__H__
#define __WARP_TEN__H__

#include <Arduino.h>
#include <string.h>


class Warp10 {
  public:
    Warp10();

    String execScript(String warpScript);
    String execScript(const char* warpScript);
    unsigned long getTimestamp();

  private:
    static const char* url;
};

#endif