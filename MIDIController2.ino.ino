#include <Button.h>
#include <LED.h>
#include <OnOffButton.h>
#include <MomentaryButton.h>




LED ledYellow1(1);
MomentaryButton buttonYellow1(10,0);
LED ledRed1(3);
MomentaryButton buttonRed1(11,2);
LED ledGreen1(5);
MomentaryButton buttonGreen1(12,4);
LED ledWhite1(7);
MomentaryButton buttonWhite1(13,6);
LED ledYellow2(21);
OnOffButton buttonYellow2(14,22);
LED ledRed2(19);
OnOffButton buttonRed2(15,20);
LED ledGreen2(17);
OnOffButton buttonGreen2(16,18);
LED ledWhite2(15);
OnOffButton buttonWhite2(17,16);



void setup() 
{
  ledYellow1.turnOn();
  delay(100);
  ledYellow1.turnOff();
}


void loop() {

  buttonYellow1.checkState(ledYellow1);
  buttonRed1.checkState(ledRed1);
  buttonGreen1.checkState(ledGreen1);
  buttonWhite1.checkState(ledWhite1);
  buttonYellow2.checkState(ledYellow2);
  buttonRed2.checkState(ledRed2);
  buttonGreen2.checkState(ledGreen2);
  buttonWhite2.checkState(ledWhite2);
}
