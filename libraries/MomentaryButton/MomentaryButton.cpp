#include "MomentaryButton.h"
#include "Button.h"
MomentaryButton::MomentaryButton(int pcc,int ppin) : Button (pcc,ppin)
{
};

void MomentaryButton::checkState(LED led)
{
  if (_button.update() )//check if button was pressed or released
  {
    if (_button.fallingEdge()) // check if it was just pressed in, this should filter out button releases
    {
        usbMIDI.sendControlChange(_cc, _value_on, _channel);
        led.turnOn();
        delay(50);
        led.turnOff();
    }
  }
};
