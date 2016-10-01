#ifndef Button_h
#define Button_h
#include "Bounce2.h"
#include "Arduino.h"
#include "LED.h"
class Button
{
  public:
    Button(int ppin,int cc);
    void checkState(LED led);

  protected:
    Bounce _button;
    // midi channel
    int _channel = 1;
    int _pin;
    int _cc;
    // cc values
    int _value_off = 1;
    int _value_on = 110;
};
#endif