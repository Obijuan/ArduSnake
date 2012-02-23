//--------------------------------------------------------------
//-- ArduSnake library: Locomotion of modular snake robots
//-----------------------------------------------------------
//-- Layer: Oscillator
//------------------------------------------------------------
//-- Example of controlling one oscillator from the PC
//--
//-- In this example the oscillator can only the either played or 
//-- stopped by means of a GUI
//-- The program Oscillator_serial_1 should be uploaded into the
//-- Arduino/Skymega board.
//--------------------------------------------------------------
//-- (c) Juan Gonzalez-Gomez (Obijuan), Feb-2012
//-- GPL license
//--------------------------------------------------------------

import processing.serial.*;

Serial myPort;

//-- Oscillaltor states
int STOPPED=0;
int RUNNING=1;

//-- Oscillator current state
int state=STOPPED;

//-- Serial commands for the oscillator
char CMD_STOP = 'S';  //-- Stop the oscillaltor
char CMD_PLAY = 'P';  //-- Play the oscillator

PFont myFont;

void setup()
{
  size(300, 100);
  
  // create a font with the second font available to the system:
  myFont = createFont(PFont.list()[0], 14);
  textFont(myFont);
  
  // list all the serial ports:
  println(Serial.list());
  
  //-- Open the serial port
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  
  //-- Display the information
  fill(16,35,229);
  text("Basic controll of one oscillator",20,30);
  text("Type p to Play", 10, 60);
  text("Type s to Stop", 10, 80);
  
  //-- Sync the software oscillator state with the real
  //-- hardware oscillator (in the Arduino)
  updateState();
}

void draw()
{
  //-- Change the GUI according to the oscillator state
  if (state==RUNNING) {
    fill(0,255,0);
    rect(150, 60, 70, 20);
    fill(0,0,255);
    text("Running",155, 75);
  }
  else {
    fill(255,0,0);
    rect(150, 60, 70, 20);
    fill(0,0,255);
    text("Stopped",155, 75);
  }
}

void keyPressed()
{
  //-- Change the state depending on the key pressed
  switch(key) {
    case 'p': 
      state=RUNNING;
      break;
    case 's':
      state=STOPPED;
      break;  
  }
  updateState();
}

//-- Check if the GUI button is pressed. If so,
//-- the oscillator state is changed
void mousePressed()
{
  if (overRect(150,60,70,20)) {
    if (state==RUNNING) 
      state=STOPPED;
    else 
      state=RUNNING;
      
    updateState();
  }
}

//-- Play or stop the servo according to the oscillator state
void updateState()
{
  if (state==RUNNING) {
    myPort.write(CMD_PLAY);
  }  
  else
    myPort.write(CMD_STOP);
}

//-- Detect if the mouse is over a rectangular region
boolean overRect(int x, int y, int width, int height) 
{
  if (mouseX >= x && mouseX <= x+width && 
      mouseY >= y && mouseY <= y+height) {
    return true;
  } else {
    return false;
  }
}


