#ifndef LED_h
#define LED_h
#include "Bounce2.h"
#include "Arduino.h"
class LED
{
  public:
    LED(int ppin);
    void turnOn();
    void turnOff();
  private:
    int _pin;
};
#endif