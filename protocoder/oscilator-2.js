/*
*   Client for the Oscillator server v2
*   
*   Control the oscillators with Sliders
*   
*   (c) Juan Gonzalez Gomez (Obijuan). Feb-2015
*   GPL v2 license
*   
*/

const CMD_PLAY = 'P';
const CMD_STOP = 'S';
const CMD_SET_A = 'A';
const CMD_SET_O = 'O';
const CMD_SET_Ph = 'H';
const CMD_SET_T = 'T';
const CMD_END = '\r';

//-- Setup the bluetooth connection
network.connectBluetoothSerialByUi(
function(m, data) {
      console.log(data);
});

//-- Create the oscillators
var a = new Oscillator('a');
var b = new Oscillator('b');


//------------------ Sliders for controlling the Oscillator
//-- A: amplitude
var aslider_A = ui.addSlider(20, 20, ui.sw - 20, -1, 0, 90,
function(progress){
    a.set_A(progress);
});

//-- O: offset
var aslider_O = ui.addSlider(20, 150, ui.sw - 20, -1, -90, 90,
function(progress){
    a.set_O(progress);
});

//-- Ph: Phase
var aslider_Ph = ui.addSlider(20, 280, ui.sw - 20, -1, -180, 180,
function(progress){
    a.set_Ph(progress);
});

var aslider_T = ui.addSlider(20, 410, ui.sw - 20, -1, 200, 5000,
function(progress){
    a.set_T(progress);
});

ui.addButton("Play", 20, 540, 300, 120, function() { 
	a.play();
});

ui.addButton("Stop", 310, 540, 300, 120, function() { 
	a.stop();
});

//------------------ Sliders for controlling the Oscillator
//-- A: amplitude
var bslider_A = ui.addSlider(20, 700, ui.sw - 20, -1, 0, 90,
function(progress){
    b.set_A(progress);
});

//-- O: offset
var bslider_O = ui.addSlider(20, 850, ui.sw - 20, -1, -90, 90,
function(progress){
    b.set_O(progress);
});

//-- Ph: Phase
var bslider_Ph = ui.addSlider(20, 980, ui.sw - 20, -1, -180, 180,
function(progress){
    b.set_Ph(progress);
});

var bslider_T = ui.addSlider(20, 1100, ui.sw - 20, -1, 200, 5000,
function(progress){
    b.set_T(progress);
});

ui.addButton("Play", 20, 1240, 300, 120, function() { 
	b.play();
});

ui.addButton("Stop", 310, 1240, 300, 120, function() { 
	b.stop();
});

//-- Set the initial value for the sliders
aslider_A.setValue(45);
aslider_O.setValue(0);
aslider_Ph.setValue(0);
aslider_T.setValue(2000);

bslider_A.setValue(45);
bslider_O.setValue(0);
bslider_Ph.setValue(0);
bslider_T.setValue(2000);

//--------- Oscillator Cass
function Oscillator(dir)
{
    this.dir = dir;    //-- Servo identificator
    this._A = 45;     //-- Current amplitude
    this._O = 0;
    this._Ph = 0;
    this._T = 2000;
    
    //-- Play
    this.play = function() {
        var frame = this.dir + CMD_PLAY + CMD_END;
        network.sendBluetoothSerial(frame);
        console.log(frame);
    }
    
    //-- Stop
    this.stop = function() {
        var frame = this.dir + CMD_STOP + CMD_END;
        network.sendBluetoothSerial(frame);
        console.log(frame);
    }
    
    //-- Set the amplitude
    this.set_A = function(A) {
        
        //-- Only integer values
        A = Math.round(A);
        
        //-- Update the servo only if there is a change
        if (A != this._A) {
            var frame = this.dir + CMD_SET_A + A + CMD_END
            network.sendBluetoothSerial(frame);
            this._A = A;
            console.log(frame);
        }
    }
    
    //-- Set the offset
    this.set_O = function(O) {
        
        //-- Only integer values
        O = Math.round(O);
        
        //-- Update the servo only if there is a change
        if (O != this._O) {
            var frame = this.dir + CMD_SET_O + O + CMD_END
            network.sendBluetoothSerial(frame);
            this._O = O;
            console.log(frame);
        }
    }
    
    //-- Set the offset
    this.set_Ph = function(Ph) {
        
        //-- Only integer values
        Ph = Math.round(Ph);
        
        //-- Update the servo only if there is a change
        if (Ph != this._Ph) {
            var frame = this.dir + CMD_SET_Ph + Ph + CMD_END
            network.sendBluetoothSerial(frame);
            this._Ph = Ph;
            console.log(frame);
        }
    }
    
    //-- Set the offset
    this.set_T = function(T) {
        
        //-- Only integer values
        T = Math.round(T);
        
        //-- Update the servo only if there is a change
        if (T != this._T) {
            var frame = this.dir + CMD_SET_T + T + CMD_END
            network.sendBluetoothSerial(frame);
            this._T = T;
            console.log(frame);
        }
    }

}


