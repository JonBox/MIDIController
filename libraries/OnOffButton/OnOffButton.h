#ifndef OnOffButton_h
#define OnOffButton_h
#include "Arduino.h"
#include "LED.h"
#include "Button.h"
class OnOffButton: Button
{
 public:
   OnOffButton(int pcc,int ppin);
   void checkState(LED led);
   bool _isOn;
   int _pcc_On;
   int _pcc_Off;
};
#endif