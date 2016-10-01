#include "OnOffButton.h"
#include "Button.h"
OnOffButton::OnOffButton(int pcc,int ppin): Button (pcc,ppin)
{
  _isOn=false;
};

void OnOffButton::checkState(LED led)
{
 if (_button.update() )//check if button was pressed or released
 {
   if (_button.fallingEdge()) // check if it was just pressed in, this should filter out button releases
   {
       if (_isOn) 
       {
         usbMIDI.sendControlChange(_pin, _value_off, _channel);
         _isOn=false;
         led.turnOff();
       }
       else 
       {
         usbMIDI.sendControlChange(_pin, _value_on, _channel);
         _isOn=true;
         led.turnOn();
       }
   }
 }
};