#include "Button.h"
Button::Button(int pcc,int ppin)
{
    _button  = Bounce();
    _pin=ppin;
    _cc=pcc;
    //set the pin connected to the button to read input
    pinMode(_pin, INPUT);
    //attaches the bounce reader to the pin for the button
    _button.attach(_pin);
    // sets the interval during which all signals from the button will be reduced to a single signal (debouncer interval)
    _button.interval(5);
    //set momentary switches to always send an on signal
};