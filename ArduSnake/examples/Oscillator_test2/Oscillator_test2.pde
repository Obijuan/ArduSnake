//--------------------------------------------------------------
//-- ArduSnake library: Locomotion of modular snake robots
//-----------------------------------------------------------
//-- Layer: Oscillator
//------------------------------------------------------------
//-- Example of use of the Oscillator layer
//--
//-- Example 2: Setting the oscillator parameters
//-- One servo is being oscillated using the parameters set by the user
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
  
  //-------- Set the oscillator parameters
  //-- Set the offset. The servo will oscillate around this point
  //-- Units: Degrees. Default value: 0
  osc.SetO(40);
  
  //-- Set the Amplitude. How far the servo moves from the position
  //-- given by the offset. Units: degrees. Default value: 45
  osc.SetA(40);

  //-- Set the oscillation period. After one period the servo will be
  //-- in the same state. Units: ms. Default value: 2000
  osc.SetT(1000);

  //-- Set the Initial phase. It determines in which part of the cycle
  //-- the servo starts. Setting it to 90 degrees the servo will start
  //-- the oscillation from the vertical positon
  osc.SetPh(DEG2RAD(-90));

}


void loop()
{
  //-- Refresh the oscillator
  osc.refresh();
}


