//--------------------------------------------------------------
//-- Locomotion of the pith-yaw-6 configuration
//-- The robot consist of 6 modules in total, 3 are pitching and 3 yawing
//-- The structure is P - Y - P - Y - P - Y
//---------------------------------------------------------------
//-- There are 2 boards controlling the robot, each one in charge of
//--  3 modules:
//--  Group 1:  P  -  Y  -  P   (board 1)
//--  Group 2:  Y  -  P  -  Y   (board 2)
//----------------------------------------------------------------
//-- Even though this example has been developed for controlling a 6 module snake,
//-- it is generic. Changing the constant BOARDS and M it can be used for longer
//-- snakes
//-----------------------------------------------------------
//-- The robot automatically changes the gait after some time
//--------------------------------------------------------------
//-- (c) Juan Gonzalez-Gomez (Obijuan), Jul-2013
//-- GPL license
//--------------------------------------------------------------
#include <Servo.h>
#include <Oscillator.h>

//-- Only needed if using the skymega board
#include "skymega.h"


//----------------------------------------------------------------------
//-- Constants that can be changed by the user

//-- Total Number of board
const int BOARDS = 2;

//-- Modules per board
const int M = 3;

//-- Board number (1 - BOARDS). Generate the firmware to download in the board
const int board = 1;

//-- Timeout for changing the gait (if button is not pressed) (in ms)
const int GAIT_TIME = 20000;

//-----------------------------------------------------------------------

//-- Different periods for the oscillations (ms)
const int T0 = 8000;
const int T1 = 1400;
const int T2 = 3000;

//--                   0    1    2     3    4
const int T[] =       {T0,  T1,  T2,   T2,  T0};
const int Av[] =      {0,   40,  20,   20,  80};
const int Ah[] =      {0,   0,   40,   40,  80};
const int phd_v[] =   {0,   120, 120,  120,  0};
const int phd_h[] =   {0,   0,   120,  60,   0};
const int phd_vh[] =  {0,   0,   0,    90,  90};
const int ph_ini[] =  {0,   0,   0,    0,   180};

//-- Description of the locomotion gaits
//--  0: Stopped
//--  1: Moving in a straight line
//--  2: Moving sideways
//--  3: Rotating
//--  4: Rolling

//-- Total number of modules in the snake
const int MOD = M * BOARDS;

//-- Number of elements in the sequence
int seq_size = sizeof(Av)/sizeof(int);
int seq = 0;  //-- Sequence counter

//-- Declare the oscillators controlled by the current board
Oscillator osc[M];

//-- Parameters of the global snake. They are calculated from the 
//-- global parameters Av, Ah, phd_v, phd_h and ph_ini
int snake_A[MOD];   //-- Amplitude
int snake_ph[MOD];  //-- Phase
int snake_T[MOD];   //-- Period

//-- Get the global snake parameters from the current gait
void global_snake(int seq)
{
  //-- Calculate the global snake
  for (int i = 0; i<MOD; i++) {
    
    //-- Even modules:
    if (i % 2 == 0) {
      snake_A[i] = Av[seq];
      
      snake_ph[i] = ph_ini[seq] + (i/2) * phd_v[seq];
    }
    //-- Odd modules
    else {
      snake_A[i] = Ah[seq];
      snake_ph[i] = ph_ini[seq] + phd_vh[seq] + (i-1)/2 * phd_h[seq];
    }
    
    //-- The period is the same for all the modules
    snake_T[i] = T[seq];
    
  }
}

//-- Map the snake parameters into the board oscillators
void map_snake()
{
  //-- Map the snake parameters into the oscillators of the board
  for (int i = 0; i < M; i++) {
    osc[i].SetO(0);                           //-- Offset is always 0
    osc[i].SetT(snake_T[ (board-1)*M + i ]);  //-- Map the period
    osc[i].SetA(snake_A[ (board-1)*M + i ]);   //-- Map the amplitude
    osc[i].SetPh(DEG2RAD( snake_ph[(board-1)*M + i ] )); //-- Map the phase
  }
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
  
  //-- Calculate the snake parameters for the initial gait
  global_snake(0);
  
  //-- Configure the oscillators of the current board
  map_snake();
  
  //-- Turn on the led
  digitalWrite(LED, ON);

}

void loop()
{
  //-- Refresh the oscillators
  for (int i=0; i<3; i++)
    osc[i].refresh(); 
    
  //-- If button clicked... or after sometime... change the gait  
  if (button_clicked() || timeout(GAIT_TIME)) {
    
    //-- Reset the timer
    previousMillis = currentMillis;
    
    //-- Point to the next sequence
    seq = (seq + 1) % seq_size;
    
    //-- Calculate the snake parameters for the initial gait
    global_snake(seq);
  
    //-- Configure the oscillators of the current board
    map_snake();
    
  }   
}


