#include "warp10.h"
#include "config.h"
#include "malloc.h"
#include <ESP8266HTTPClient.h>

#define URL "/api/v0/exec"

const char* Warp10::url = "/api/v0/exec";

Warp10::Warp10() {

}

String Warp10::execScript(const char* warpScript) {
  return this->execScript(String(warpScript));
}

String Warp10::execScript(String warpScript) {
  HTTPClient http;

  Serial.println("Requesting Timestamp");
  int beginResult = http.begin(String("https://") + WARP10_HOST + this->url, FINGERPRINT);
  http.addHeader("Content-Type", "application/json");
  
  int httpCode = http.POST(warpScript);
  String response = http.getString();

  Serial.print("beginResult: ");
  Serial.print(beginResult);
  Serial.println();
  
  Serial.print("http: ");
  Serial.print(httpCode);
  Serial.println();
  
  Serial.print("response: ");
  Serial.println(response);
  Serial.println();
  
  http.end();

  return response;
}

unsigned long Warp10::getTimestamp() {
  String response = this->execScript("NOW");

  int responseLength =  response.length();
  char* timestampStr = (char*)malloc(responseLength-6);
  timestampStr[responseLength-6] = 0;
  response.substring(1, responseLength-7).toCharArray(timestampStr, responseLength - 7);

  long result = atol(timestampStr);
  free(timestampStr);
  return result;
}
