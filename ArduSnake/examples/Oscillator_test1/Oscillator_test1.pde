//--------------------------------------------------------------
//-- Oscillator_test1.pde
//-- Example of use of the Oscillator library
//-- The 4 servos oscillates with the default parameters
//--------------------------------------------------------------
//-- (c) Juan Gonzalez-Gomez (Obijuan), Dec 2011
//-- GPL license
//--------------------------------------------------------------
#include <Servo.h>
#include <Oscillator.h>
#include "skymega.h"

//-- Declare the 4 oscillators to be used
Oscillator osc[4];

void setup()
{
  //-- Attach the oscillators to the servos
  osc[0].attach(SERVO2);
  osc[1].attach(SERVO4);
  osc[2].attach(SERVO6);
  osc[3].attach(SERVO8);
  
  //-- They will start oscillating with the
  //-- default parameters
}

void loop()
{
  //-- Refresh the oscillators
  for (int i=0; i<4; i++)
    osc[i].refresh();
}


