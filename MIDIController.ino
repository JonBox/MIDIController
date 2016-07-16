#include <Bounce2.h>
const int onboardLED = LED_BUILTIN;
class LED
{
  public:
  LED(int ppin);
  //method to turn on the LED
  void turnOn();
  //method to turn off the LED
  void turnOff();
  private:
  //the pin on the board to which the LED is connected
  int _pin;
};

LED::LED(int pin)
{
  _pin=pin;
  //sets the LED pin to deliever output data
  pinMode(_pin, OUTPUT);
}
void LED::turnOn()
{
  //set output voltage on LED pin to 5v
  digitalWrite(_pin, HIGH);
}
void LED::turnOff()
{
  //set output voltage on LED pin to 0v
  digitalWrite(_pin, LOW);
}


class Pot
{
  public:
  Pot(int pcc, int ppin);
  //checks the current state of the pot and sends a corresponding cc value if changed
  void CheckState();
  protected:
    //the cc to send to the DAW
    int _cc;
    //the pin that the button input is running to
    int _pin;
    //what the last position of the pot was
    int _lastCC;

    // midi channel
    int _channel = 1;
};
Pot::Pot(int pcc, int ppin)
{
  //set the cc to send
  _cc=pcc;
  //set the input pin
  _pin=ppin;
  //set the initial state of the pot
  _lastCC=0;
  //sets the pin used by the pot to input
 //   pinMode(_pin, INPUT);
}
void Pot::CheckState()
{
  //read the current potentiometer value
 int  currentCC = (analogRead(_pin)/8);

   //if it is different from the last value sent....
  if (currentCC!=_lastCC )//check if button was pressed or released
  {
        //send the value over the current midi channel...
        usbMIDI.sendControlChange(_cc, currentCC, _channel);
        //and update the last value sent
        _lastCC=currentCC;
      
   }
  
}

class Button
{ 

    public:
    Button(int pcc, int ppin, bool momentary, bool channelchanger);
    Button(int ccon,int ccoff, int ppin);
    //function to see if button is pressed
    void CheckState(LED led);
    void SetChannel(int channel);
    void SetMomentary(bool Momentary);
    protected:
    //the cc to send to the DAW with an On command
    int _ccOn;
    //the cc to send to the DAW with an Off command
    int _ccOff;
    //the pin that the button input is running to
    int _pin;
    //whether the button is currently toggled on
    bool _isOn;
    //bounce object used to reduce noise
    Bounce _button;
    // midi channel
    int _channel = 1;
    // cc values
    int _value_off = 1;
    int _value_on = 110;
    bool _momentary=false;
    bool _channelchanger=false;
};

Button::Button(int pcc, int ppin, bool momentary=false,bool channelchanger=false)
{
    _button  = Bounce();
    _ccOn=pcc;
    _ccOff=pcc;
    _pin=ppin;
    _isOn=false;
    _momentary=momentary;
    //set the pin connected to the button to read input
    pinMode(_pin, INPUT);
    //attaches the bounce reader to the pin for the button
    _button.attach(_pin);
    // sets the interval during which all signals from the button will be reduced to a single signal (debouncer interval)
    _button.interval(5);
    //set momentary switches to always send an on signal
    if (momentary){_value_off=_value_on;}
    if (channelchanger){_channelchanger=channelchanger;}
}

Button::Button(int ccon,int ccoff, int ppin)
{
    _button  = Bounce();
    _ccOn=ccon;
    _ccOff=ccoff;
    _pin=ppin;
    _isOn=false;
    //set the pin connected to the button to read input
    pinMode(_pin, INPUT);
    //attaches the bounce reader to the pin for the button
    _button.attach(_pin);
    // sets the interval during which all signals from the button will be reduced to a single signal (debouncer interval)
    _button.interval(5);
    //set momentary switches to always send an on signal
}

int CurrentChannel=1;

//sets the current channel for a button
void Button::SetChannel(int channel)
{
  _channel=channel;
}

//changes a switch to be momentary or on/off
void Button::SetMomentary(bool Momentary)
{
  _momentary=Momentary;
}



LED ledYellow1(1);
Button buttonYellow1(10,0);
LED ledRed1(3);
Button buttonRed1(11,2);
LED ledGreen1(5);
Button buttonGreen1(12,4);
LED ledWhite1(7);
Button buttonWhite1(13,6,false,true);
LED ledYellow2(21);
Button buttonYellow2(14,22,true);
LED ledRed2(19);
Button buttonRed2(15,25,20);
LED ledGreen2(17);
Button buttonGreen2(16,25,18);
LED ledWhite2(15);
Button buttonWhite2(17,16);
//Pot pot1(40,29);

//increments the channel by one, resets if it would go over 8
void ChangeChannel()
{
  
  if (CurrentChannel<8)
  {
    CurrentChannel=CurrentChannel+1;
  }
  else
  {
    CurrentChannel=1;
  }
  digitalWrite(onboardLED, HIGH);
  delay(100);
  digitalWrite(onboardLED, LOW);
}

void BlinkChannel()
{
  switch (CurrentChannel) 
  {
    case 1:
      ledYellow1.turnOn();
      delay(100);
      ledYellow1.turnOff();
      break;
    case 2:
      ledRed1.turnOn();
      delay(100);
      ledRed1.turnOff();
      break;
    case 3:
      ledGreen1.turnOn();
      delay(100);
      ledGreen1.turnOff();
      break;
    case 4:
      ledWhite1.turnOn();
      delay(100);
      ledWhite1.turnOff();
      break;
    case 5:
      ledYellow2.turnOn();
      delay(100);
      ledYellow2.turnOff();
      break;
    case 6:
      ledRed2.turnOn();
      delay(100);
      ledRed2.turnOff();
      break;
    case 7:
      ledGreen2.turnOn();
      delay(100);
      ledGreen2.turnOff();
      break;
    case 8:
      ledWhite2.turnOn();
      delay(100);
      ledWhite2.turnOff();
      break;

  }
}

void UpdateCurrentChannel()
{
  ChangeChannel();
  BlinkChannel();
  buttonWhite2.SetChannel(CurrentChannel);
  buttonRed2.SetChannel(CurrentChannel);
  buttonGreen2.SetChannel(CurrentChannel);
  bool momentary= (CurrentChannel!=1);
  buttonWhite2.SetMomentary(momentary);
  buttonRed2.SetMomentary(momentary);
  buttonGreen2.SetMomentary(momentary);
  if ( CurrentChannel==2 ||CurrentChannel==4 )
  {
    buttonGreen1.SetChannel(CurrentChannel);
  }
  else
  {
    buttonGreen1.SetChannel(1);
  }
}


//event that handles recieving CC from the computer, currently sets certain buttons to have other functions on other channels
void OnControlChange(byte channel, byte control, byte value)
{
  if (control==122 && value==127)
  {
    UpdateCurrentChannel();
  }
}

void Button::CheckState(LED led)
{
  // put your main code here, to run repeatedly:
  if (_button.update() )//check if button was pressed or released
  {
    if (_button.fallingEdge()) // check if it was just pressed in, this should filter out button releases
    {
      if (_momentary)
      {
        usbMIDI.sendControlChange(_ccOn, _value_on, _channel);
        led.turnOn();
        delay(50);
        led.turnOff();
      }
      if (_channelchanger)
      {
        UpdateCurrentChannel();
      }
      
      else
      {
        if (_isOn) 
        {
          usbMIDI.sendControlChange(_ccOff, _value_off, _channel);
          _isOn=false;
          led.turnOff();
        }
        else 
        {
          usbMIDI.sendControlChange(_ccOn, _value_on, _channel);
          _isOn=true;
          led.turnOn();
        }
      }
    }
  }
}


void setup() {
  // flash the LEDs on and off on startup
  ledYellow1.turnOn();
  ledRed1.turnOn();
  ledGreen1.turnOn();
  ledWhite1.turnOn();
  ledYellow2.turnOn();
  ledRed2.turnOn();
  ledGreen2.turnOn();
  ledWhite2.turnOn();
  delay(100);
  ledYellow1.turnOff();
  ledRed1.turnOff();
  ledGreen1.turnOff();
  ledWhite1.turnOff();
  ledYellow2.turnOff();
  ledRed2.turnOff();
  ledGreen2.turnOff();
  ledWhite2.turnOff();
  usbMIDI.setHandleControlChange(OnControlChange);
}



void loop() {
  // check each button state every millisecond
  buttonYellow1.CheckState(ledYellow1);
  buttonRed1.CheckState(ledRed1);
  buttonGreen1.CheckState(ledGreen1);
  buttonWhite1.CheckState(ledWhite1);
  buttonYellow2.CheckState(ledYellow2);
  buttonRed2.CheckState(ledRed2);
  buttonGreen2.CheckState(ledGreen2);
  buttonWhite2.CheckState(ledWhite2);
 // pot1.CheckState();
  while (usbMIDI.read());
  delay(1);
}


