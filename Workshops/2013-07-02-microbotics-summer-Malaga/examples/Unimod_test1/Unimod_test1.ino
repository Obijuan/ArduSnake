//--------------------------------------------------------------
//-- Different oscillations for unimod
//-- When the test button is pressed, the oscillation is changed
//--
//-- This example is quite usefull for showing the effect of the
//-- parameters Amplitude, offset and period in one module
//--------------------------------------------------------------
//-- (c) Juan Gonzalez-Gomez (Obijuan), Jul-2013
//-- GPL license
//--------------------------------------------------------------
#include <Servo.h>
#include <Oscillator.h>

//-- Only needed if using the skymega board
#include "skymega.h"    

const int T0 = 2000;
const int T1 = 1000;

//-- Sequence of oscillations for unimod
//-- Oscillation n is defined by amplitude A[n], offset O[n] and period T[n]
//-- Add more oscillation examples by inserting a new A, O and T

//-- If the Amplitude is 0, there is no oscillation. The servo will remain 
//-- at a fixed position

//-- Oscillation no.
//--             0,   1,  2,   3,   4,   5,   6  -- Add more if needed
const int A[] = {0,  40, 80,  40,  40,  40,  40};
const int O[] = {0,  0,   0,   0,   0,   0,  40};
const int T[] = {T0, T0, T0,  T0,   T1, T0,  T0};


//-- Number of elements in the sequence
int seq_size = sizeof(A)/sizeof(int);
int seq = 0;  //-- Sequence counter

//-- Declare an oscillator
Oscillator osc;

void setup()
{
  //-- Attach the oscillator to the servo
  //-- For arduino, you can use the pin number instead of SERVO2 (for example 8)
  osc.attach(SERVO2);
  
  // Test LED. For arduino uno use the pin 13
  pinMode(LED, OUTPUT);      
  
  //-- Test button. For arduino uno use a pin number
  pinMode(BUTTON, INPUT);
  
  //-- Activate the button pull-up resistor
  digitalWrite(BUTTON, HIGH); 

  //-- Serial port is used for debuging
  Serial.begin(9600);  
 
  //-- Set the initial oscillation
  osc.SetO(O[0]);
  osc.SetA(A[0]);
  osc.SetT(T[0]); 
  
  //-- Turn on the led
  digitalWrite(LED, ON);
  
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
  //-- Refresh the oscillator
  osc.refresh();
  
  if (button_clicked()) {
    Serial.println("clicked!");  //-- debugging...
    
    //-- Point to the next sequence
    seq = (seq + 1) % seq_size;
    Serial.println(seq, DEC);
    
    //-- Update the oscillator with the new sequence
    osc.SetO(O[seq]);
    osc.SetA(A[seq]);
    osc.SetT(T[seq]);
  }
}


