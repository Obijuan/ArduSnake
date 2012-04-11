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
char A=20;

//-- Serial commands for the oscillator
char CMD_STOP = 'S';  //-- Stop the oscillaltor
char CMD_PLAY = 'P';  //-- Play the oscillator
char CMD_SET_A = 'A'; //-- Set Amplitude

char nosc='2';  //-- Active oscillator

PFont myFont;

Handle2[] handles;
int num=1;

void setup()
{
  size(400, 200);
  
  // create a font with the second font available to the system:
  myFont = createFont(PFont.list()[0], 14);
  textFont(myFont);
  
  // list all the serial ports:
  //println(Serial.list());
  
  //-- Open the serial port
  //String portName = Serial.list()[0];
  //myPort = new Serial(this, portName, 9600);
  
  //-- Display the information
  fill(16,35,229);
  text("Basic controll of one oscillator",20,30);
  text("Type p to Play", 10, 60);
  text("Type s to Stop", 10, 80);
  
  handles = new Handle2[num];
  int hsize = 10;
  for(int i=0; i<num; i++) {
    handles[i] = new Handle2(width/2, 10+i*15, 50-hsize/2, 10, handles);
  }
  
  
  //-- Sync the software oscillator state with the real
  //-- hardware oscillator (in the Arduino)
  updateState();
}

void draw()
{
  
  background(200);
  
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
  
  //-- Print the active oscillator
  fill(255);
  rect(240,60,30,20);
  fill(0);
  text(nosc,250,75);
  
  for(int i=0; i<num; i++) {
    handles[i].update();
    handles[i].display();
  }
}

void mouseReleased() 
{
  for(int i=0; i<num; i++) {
    handles[i].release();
  }
}

void keyPressed()
{
  if (key>='1' && key <='8') {
    nosc = key;
    return;
  }  
  
  //-- Change the state depending on the key pressed
  switch(key) {
    case 'p': 
      state=RUNNING;
      break;
    case 's':
      state=STOPPED;
      break;  
    case 'q':
      A=80;
      break;
    case 'a':
      A=20;
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
    //myPort.write(nosc);
    //myPort.write(CMD_PLAY);
  }  
  else {
    //myPort.write(nosc);
    //myPort.write(CMD_STOP);
  }  
  
  //-- Send the amplitude
  //myPort.write(nosc);
  //myPort.write(CMD_SET_A);
  //myPort.write(A);
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


