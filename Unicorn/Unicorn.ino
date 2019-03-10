#include <SBUS.h>
#include <FastLED.h>

#define LED_COUNT 20
#define LED_PIN 6

CRGB leds[LED_COUNT];
SBUS sbus(Serial);

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  sbus.begin(false);
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, LED_COUNT);
}

void loop()
{
  sbus.process();
  int throttle = map(sbus.getNormalizedChannel(3), -85, 85, 40, 255);
  int ledctrl = map(sbus.getNormalizedChannel(11), -85, 85, 0, 255);
  int failsafe;

  if (sbus.getFailsafeStatus() == SBUS_FAILSAFE_ACTIVE) {
    failsafe = true;
  }
  else {
    failsafe = false;
  }
  
  if (sbus.getLastTime() < millis() +100) {
    failsafe = true;
  } 

  if (ledctrl > 10) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
  }
  updateleds(ledctrl, throttle, failsafe);
}

void updateleds(int ledctrl, int throttle, int failsafe) {
   FastLED.clear();
  CRGB ledref;
  if (ledctrl < 5) {
    //black
    ledref = CRGB(0, 0, 0);
  }
  else if (ledctrl < 45) {
    // red
    ledref = CRGB(throttle, 0, 0);
  }
  else if (ledctrl < 63) {
    // orange
    ledref = CRGB(throttle, throttle / 2, 0);
  }
  else if (ledctrl < 120) {
    // yellow
    ledref = CRGB(throttle, throttle, 0);
  }
  else if (ledctrl < 158) {
    // green
    ledref = CRGB(0, throttle, 0);
  }
  else if (ledctrl < 245) {
    // cyan
    ledref = CRGB(0, throttle, throttle);
  }
  else if (ledctrl < 245) {
    // blue
    ledref = CRGB(0, 0, throttle);
  }

  if (failsafe == true) {
    ledref = CRGB(255, 20, 147);
  }
  leds[1] = ledref;
  leds[2] = ledref;
  leds[3] = ledref;
  leds[4] = ledref;
  leds[5] = ledref;
  leds[6] = ledref;
  leds[7] = ledref;
  leds[8] = ledref;
  leds[9] = ledref;
  leds[10] = ledref;
  leds[11] = ledref;
  leds[12] = ledref;
  leds[13] = ledref;
  leds[14] = ledref;
  leds[15] = ledref;
  leds[16] = ledref;
  leds[17] = ledref;
  leds[18] = ledref;
  leds[19] = ledref;
  leds[20] = ledref;


  FastLED.show();
  delay(10);


}
