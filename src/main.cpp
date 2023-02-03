#include <Arduino.h>

#define WIFI_SSID         ""
#define WIFI_PASS         ""
#define BLYNK_TEMPLATE_ID ""
#define BLYNK_DEVICE_NAME ""
#define BLYNK_AUTH_TOKEN  ""

#if ARDUINO_ARCH_ESP32
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <WiFiClient.h>
#elif ARDUINO_ARCH_ESP8266
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#else
#error "Unsupported ARDUINO architecture"
#endif

#define BLYNK_PRINT Serial

BlynkTimer timer;

void Event_UpdateElapsedTime()
{
  Blynk.virtualWrite(V1, millis() / 1000);
}

BLYNK_WRITE(V0)
{
  int pinValue = param.asInt();
  digitalWrite(LED_BUILTIN, pinValue);
}

void setup()
{
  // Initialize Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);

  // Post Blynk inits.
  pinMode(LED_BUILTIN, OUTPUT);
  timer.setInterval(1000L, Event_UpdateElapsedTime);
}

void loop()
{
  // Loop to update Blynk state.
  Blynk.run();
  timer.run();
}
