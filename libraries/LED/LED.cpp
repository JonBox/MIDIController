#include "LED.h"
LED::LED(int pin)
{
  _pin=pin;
  //sets the LED pin to deliever output data
  pinMode(_pin, OUTPUT);
};
void LED::turnOn()
{
  //set output voltage on LED pin to 5v
  digitalWrite(_pin, HIGH);
};
void LED::turnOff()
{
  //set output voltage on LED pin to 0v
  digitalWrite(_pin, LOW);
};