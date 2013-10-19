//--------------------------------------------------------------
//-- Locomotion of the PYP (Pitch-Yaw-Pitch) minimal configuration
//-- The robot consists of three modules. The module in the middle is 
//--  yawing while the modules at the ends are pitching up and down
//--
//--  When the button is pressed, the locomotion gaits is changed
//--------------------------------------------------------------
//-- (c) Juan Gonzalez-Gomez (Obijuan), Feb-2012
//-- GPL license
//--------------------------------------------------------------
#include <Servo.h>
#include <Oscillator.h>

//-- Only needed if using the skymega board
#include "skymega.h"

//-- Declare two oscillators
Oscillator osc[3];

//-- Different periods for the oscillations
const int T0 = 4000;
const int T1 = 1400;

//--                   0    1   2     3    4
const int T[] =       {T0, T1,  T1,  T1,  T0 };
const int Av[] =      {0,  40,  20,  30,  80};
const int Ah[] =      {0,   0,  20,  30,  80};
const int phd_v[] =   {0,  120, 0,   180, 0};
const int phd_h[] =   {0,   0,  90,   90, 90};
const int phd_ini[] = {0,   0,  0,    0, 180};

//-- Description of the locomotion gaits
//--  0: No locomotion. The robot is stopped. No oscillations (because the amplitude
//--     is 0
//--  1: Moving in a straight line. Only the motors at the ends are oscillating
//--  2: Moving sideways
//--  3: Rotating
//--  4: Rolling

//-- Number of elements in the sequence
int seq_size = sizeof(Av)/sizeof(int);
int seq = 0;  //-- Sequence counter



void setup()
{
  //-- Attach the oscillators to the two servos
  //-- For arduino, you can use the pin number instead of SERVO2
  osc[0].attach(SERVO2);
  osc[1].attach(SERVO4);
  osc[2].attach(SERVO6);
  
  // Test LED. For arduino uno use the pin 13
  pinMode(LED, OUTPUT);      
  
  //-- Test button. For arduino uno use a pin number
  pinMode(BUTTON, INPUT);
  
  //-- Activate the button pull-up resistor
  digitalWrite(BUTTON, HIGH); 
  

  //-- Configure the oscillators
  //-- Oscillator 0
  osc[0].SetPh(DEG2RAD(phd_ini[0]));
  osc[0].SetO(0);
  osc[0].SetA(Av[0]);
  osc[0].SetT(T[0]);
  
  //-- Oscillator 1
  osc[1].SetPh(DEG2RAD(phd_ini[0] + phd_h[0]));
  osc[1].SetO(0);
  osc[1].SetA(Ah[0]);
  osc[1].SetT(T[0]);
  
  //-- Configure the oscillators
  //-- Oscillator 0
  osc[2].SetPh(DEG2RAD(phd_ini[0] + phd_v[0]));
  osc[2].SetO(0);
  osc[2].SetA(Av[0]);
  osc[2].SetT(T[0]);

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
  for (int i=0; i<3; i++)
    osc[i].refresh(); 
    
  if (button_clicked()) {
    
    //-- Point to the next sequence
    seq = (seq + 1) % seq_size;
    
    //-- Update the oscillator with the new sequence
    osc[0].SetPh(DEG2RAD(phd_ini[seq]));
    osc[0].SetO(0);
    osc[0].SetA(Av[seq]);
    osc[0].SetT(T[seq]);
  
    //-- Oscillator 1
    osc[1].SetPh(DEG2RAD(phd_ini[seq] + phd_h[seq]));
    osc[1].SetO(0);
    osc[1].SetA(Ah[seq]);
    osc[1].SetT(T[seq]);
  
    //-- Configure the oscillators
    //-- Oscillator 0
    osc[2].SetPh(DEG2RAD(phd_ini[seq] + phd_v[seq]));
    osc[2].SetO(0);
    osc[2].SetA(Av[seq]);
    osc[2].SetT(T[seq]);
    
  }  
}




