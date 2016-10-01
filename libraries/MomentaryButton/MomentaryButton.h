#ifndef MomentaryButton_h
#define MomentaryButton_h
#include "Arduino.h"
#include "LED.h"
#include "Button.h"
class MomentaryButton :  Button
{
	public:
		MomentaryButton(int ppin,int cc);
		void checkState(LED led);
};
#endif
