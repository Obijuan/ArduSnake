//--------------------------------------------------------------
//-- ArduSnake library: Locomotion of modular snake robots
//-----------------------------------------------------------
//-- Layer: Oscillator
//------------------------------------------------------------
//-- OSCILLATOR SERVER.
//-- This firmware is for contrilling the oscillators from the PC
//-- It offers some services to the PC by a serial channel.
//-- Example of use of the Oscillator layer
//-- Controlling the oscillations from the PC.
//--------------------------------------------------------------
//-- (c) Juan Gonzalez-Gomez (Obijuan), Feb-2012
//-- GPL license
//--------------------------------------------------------------
#include <Servo.h>
#include <Oscillator.h>
#include "skymega.h"
#include "freeleds.h"

//-- Serial commands
const unsigned char CMD_STOP = 'S';  //-- Stop the oscillaltor
const unsigned char CMD_PLAY = 'P';  //-- Play the oscillator

//-- Declare the oscillators
Oscillator osc[4];

void setup()
{
  freeleds_setup();
  
  //-- Configure the serial comunication with PC
  Serial.begin(9600);

  //-- Attach the oscillator to servo
  osc[0].attach(SERVO2);

  //-- Initially the oscillator is stoped
  osc[0].Stop();

  //-- The oscillator is configured with the default parameters
  freeleds_display(0xAA);
}

//-- Incoming byte from the PC
unsigned char inbyte;
char nosc;  //-- Oscillator number
char cmd;   //-- Command
void loop()
{
  //-- refresh the oscillators
  osc[0].refresh();

  //-- When a byte is received from the PC
  if (Serial.available()) {

    //-- Process the frame
    //-- The first byte is the oscillator number (in ASCII), characters '0'-'7'
    
    //-- Read the oscillator number
    nosc = Serial.read() - '0';
    freeleds_display(nosc);
    
    //-- Read the command
    cmd = Serial.read();
    freeleds_display(cmd);
    //osc[nosc].Play();
    
  /*  
    switch(cmd){
      case CMD_STOP:     //-- Stop command
        osc[nosc].Stop();
        break;
      case CMD_PLAY:     //-- Play command
        osc[nosc].Play();
        break;
    }
  */  
    
  }
}


