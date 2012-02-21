//--------------------------------------------------------------
//-- ArduSnake library: Locomotion of modular snake robots
//-----------------------------------------------------------
//-- Layer: Oscillator
//------------------------------------------------------------
//-- Example of use of the Oscillator layer
//-- HELLO WORLD EXAMPLE!
//-- A Servo is oscillated using the default parameters
//--------------------------------------------------------------
//-- (c) Juan Gonzalez-Gomez (Obijuan), Feb-2012
//-- GPL license
//--------------------------------------------------------------
#include <Servo.h>
#include <Oscillator.h>

//-- This file contains the pin names for the skymega board
//-- If using arduino you can comment it out
#include "skymega.h"

//-- Declare an oscillator
Oscillator osc;

void setup()
{
  //-- Attach the oscillator to the servo
  //-- If skymega.h is included, you can indicate the
  //-- servo number as read on the board silkscreen
  osc.attach(SERVO2);

  //-- For standar arduino boards you can use the pin number
  //osc.attach(8);
}

//-- The servo will oscillate with the
//-- default parameters
void loop()
{
  //-- Refresh the oscillator
  osc.refresh();
}


