//--------------------------------------------------------------
//-- Experiment: The wave
//-- 9 independent modules generate a big wave
//-- The modules are divided into 3 groups. Each group is connected
//--  to one skymega board
//--
//--  After some oscillations, the number of waves (k) are increased
//--------------------------------------------------------------
//-- (c) Juan Gonzalez-Gomez (Obijuan), Jul-2013
//-- GPL license
//--------------------------------------------------------------
#include <Servo.h>
#include <Oscillator.h>

//-- Only needed if using the skymega board
#include "skymega.h"


//-- Osillation parameters (fixed)
const int T = 2000;
const int A = 40;
const int O = 40;

//-- Number of waves for every sequence
const int k[] = {0, 1, 2, 3};

const double Ph = 0;

//-- Total number of modules
const int M = 9;

//-- Current group!  Possible values are: 1, 2 and 3
//-- Group 1 is downloaded into board 1, group 2 into board 2 and group 3 into board 3
const int group = 1; 

//-- Number of elements in the sequence
int seq_size = sizeof(k)/sizeof(int);
int seq = 0;  //-- Sequence counter

//-- Three oscillators. There are 3 modules connected to the each board
Oscillator osc[3];

//-- Calculate the phase difference
inline double get_ph() 
{
  return 360 * k[seq] / M;
}

void setup()
{
  //-- Attach the oscillator to the servo
  //-- For arduino, you can use the pin number 
  osc[0].attach(SERVO2);
  osc[1].attach(SERVO4);
  osc[2].attach(SERVO6);
  
  // Test LED. For arduino uno use the pin 13
  pinMode(LED, OUTPUT);      
  
  //-- Test button. For arduino uno use a pin number
  pinMode(BUTTON, INPUT);
  
  //-- Activate the button pull-up resistor
  digitalWrite(BUTTON, HIGH); 

  //-- Serial port is used for debuging
  Serial.begin(9600); 

  //-- Set the initial oscillation
  osc[0].SetO(O);
  osc[0].SetA(A);
  osc[0].SetT(T);
  osc[0].SetPh(DEG2RAD(get_ph()*(group - 1)*3));

  osc[1].SetO(O);
  osc[1].SetA(A);
  osc[1].SetT(T);
  osc[1].SetPh(DEG2RAD(get_ph() * ((group - 1)*3 + 1)));
  
  osc[2].SetO(O);
  osc[2].SetA(A);
  osc[2].SetT(T);
  osc[2].SetPh(DEG2RAD(get_ph() * ((group - 1)*3 + 2)));
  
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


static long previousMillis = 0; 
static long currentMillis;
  
//-- This function returns true when the time "time"
//-- has passed since the last call
bool timeout(long time)
{
  //-- Read current time
  currentMillis = millis();
 
  //-- Check if the timeout has passed
  if(currentMillis - previousMillis > time) {
    previousMillis = currentMillis;   

    return true;
  }
  
  return false;
}



void loop()
{
  //-- Refresh the oscillators
  for (int i=0; i<3; i++)
    osc[i].refresh();
  
  //-- after 5 oscillations or after the button is pressed....
  if (timeout(T*5) || button_clicked()) {
    Serial.println("Event!");
    
    //-- Reset the timer
    previousMillis = currentMillis;
    
    //-- Point to the next sequence
    seq = (seq + 1) % seq_size;
    
    //-- Debug....
    Serial.println(seq, DEC);
    Serial.println(get_ph() * (group - 1)*3);
    Serial.println(get_ph() * ((group - 1)*3 + 1));
    Serial.println(get_ph() * ((group - 1)*3 + 2));
   
    //-- Update the oscillators with the new phase differences
    osc[0].SetPh(DEG2RAD(get_ph() * (group - 1)*3));
    osc[1].SetPh(DEG2RAD(get_ph() * ((group - 1)*3 + 1)));
    osc[2].SetPh(DEG2RAD(get_ph() * ((group - 1)*3 + 2)));
  }
}


