//--------------------------------------------------------------
//-- Locomotion of the pitch-pitch minimal configuration (PP)
//-- It consist of two modules connected as a chain. They oscillate
//-- perpendicular to the ground
//--
//-- The robot is moved using different oscillator's parameters
//-- When the test button is pressed, the locomotion gait is changed
//-- Not all the phase differences makes the robot move correctly
//--------------------------------------------------------------
//-- (c) Juan Gonzalez-Gomez (Obijuan), Jul-2013
//-- GPL license
//--------------------------------------------------------------
#include <Servo.h>
#include <Oscillator.h>

//-- Only needed if using the skymega board
#include "skymega.h"

//-- Different periods for the oscillations
const int T0 = 2000;
const int T1 = 800;
const int T2 = 8000;

//-- Locomotion gaits for the robot
//--                 0    1    2    3    4    5    6    7   8     9
//--
const int A[] =     {0,  40,  40,  40,  40,  80,  20,  40,  40,  40};
const int T[] =     {T0, T0,  T0,  T0,  T0,  T0,  T0,  T0,  T1,  T2};
const double Ph[] = {0,  120, 0,   180, 120, 120, 120, 120, 120, 120};

//-- Description of the locomotion gaits:
//-- 0:  No locomotion. The robot is stopped. No oscillations (becase the amplitude is 0)
//-- 1:  The robot moves forward. The coordination is good
//-- 2:  No locomotion, but the two modules are oscillating in phase
//-- 3:  No locomotion, but the two modules are oscillating 180 degrees out of phase
//-- 4:  Same locomotion than 1
//-- 5:  Same than 4 but with bigger amplitude. Now the steps are bigger
//-- 6:  Same than 4, but with lesser amplitude. Now the steps are smaller
//-- 7:  Same than 1
//-- 8:  Same than 1 but faster (because the frequency is higher)
//-- 9:  Same than 1 but slower (because the frequeency is lower)

//-- Number of elements in the sequence
int seq_size = sizeof(A)/sizeof(int);
int seq = 0;  //-- Sequence counter

//-- Declare two oscillators
Oscillator osc[2];

void setup()
{
  //-- Attach the oscillator to the servo
  //-- For arduino, you can use the pin number instead of SERVO2
  osc[0].attach(SERVO2);
  osc[1].attach(SERVO4);
  
  // Test LED. For arduino uno use the pin 13
  pinMode(LED, OUTPUT);      
  
  //-- Test button. For arduino uno use a pin number
  pinMode(BUTTON, INPUT);
  
  //-- Activate the button pull-up resistor
  digitalWrite(BUTTON, HIGH); 

  //-- Serial port is used for debuging
  Serial.begin(9600); 

  //-- Set the initial oscillation
  osc[0].SetO(0);
  osc[0].SetA(A[seq]);
  osc[0].SetT(T[seq]);
  osc[0].SetPh(0);

  osc[1].SetO(0);
  osc[1].SetA(A[seq]);
  osc[1].SetT(T[seq]);
  osc[1].SetPh(DEG2RAD(Ph[seq]));
  
}

//-- This function returns true when the test button
//-- is pressed
bool button_clicked()
{
  
  static int button=1;
  static int oldbutton=1;
  
  //-- Save the previous button state
  oldbutton=button;
  
  // read the button
  button = digitalRead(BUTTON);

  //-- Detect a change in the button
  if (button!=oldbutton) {
    delay(20); //-- for debouncing
    if (button==PRESSED)
      return true;
  } 
  
  return false;
}


void loop()
{
  //-- Refresh the oscillators
  for (int i=0; i<2; i++)
    osc[i].refresh();
  
  if (button_clicked()) {
    
    //-- Point to the next sequence
    seq = (seq + 1) % seq_size;
    Serial.println(seq, DEC);
    
    //-- Update the oscillator with the new sequence
    osc[0].SetO(0);
    osc[0].SetA(A[seq]);
    osc[0].SetT(T[seq]);
    osc[0].SetPh(0);

    osc[1].SetO(0);
    osc[1].SetA(A[seq]);
    osc[1].SetT(T[seq]);
    osc[1].SetPh(DEG2RAD(Ph[seq]));
    
  }
}


