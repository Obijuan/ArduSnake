//--------------------------------------------------------------
//-- skymega.h
//-- Documentation with the pins available in the skymega board
//--------------------------------------------------------------
//-- (c) Juan Gonzalez-Gomez (Obijuan), Dec 2011
//-- GPL license
//--------------------------------------------------------------

#ifndef skymega_h
#define skymega_h

#include "WProgram.h"

//-- Mapping between the servo name (in the skymega board) and the
//-- arduino pins
const int SERVO1 = A0;
const int SERVO2 = 8;
const int SERVO3 = A1;
const int SERVO4 = 9;
const int SERVO5 = A2;
const int SERVO6 = 10;
const int SERVO7 = A3;
const int SERVO8 = 11;

//-- Skymega's test button is attached to pin 12
//--   It has no pull-up resistor
const int BUTTON = 12;
//-- Button states
const int PRESSED = LOW;
const int NOT_PRESSED = HIGH; 

//-- The skymega's led is attached to pin 13
//-- Same as Arduino
const int LED=13;

//-- LED sates:
const int ON = HIGH;
const int OFF = LOW;

#endif
