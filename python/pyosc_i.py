#!/usr/bin/python
# -*- coding: utf-8 -*-

#-----------------------------------------------------------------
#-- Python Oscillator client
#-- Juan Gonzalez-Gomez (obijuan).  Feb-2015
#-----------------------------------------------------------------
#-- Controlling the oscillators attached to the servos
#-- The firmware  Oscillator-server-v2 should be upload to the 
#-- zum / arduino board
#--
#--  Interactive version. Use it with ipython / ipython notebook
#--
#--  ipython -i pyosc_i.py
#-----------------------------------------------------------------

import serial
import Oscillator

#-- Change the serial port here
SERIAL_PORT = "/dev/ttyUSB0"

def serial_port(sname = "/dev/ttyUSB0"):
  """Open the serial port"""
  
  try:
    sp = serial.Serial(sname, 19200)
    return sp
  
  except serial.SerialException:
    sys.stderr.write("Error opening the port {0}".format(sname))
    sys.exit(1)

#-------- Interactive version

#-- Open serial port
sp = serial_port(SERIAL_PORT)

#-- Define the oscillators
a = Oscillator.Oscillator(sp, dir = 'a')
b = Oscillator.Oscillator(sp, dir = 'b')
c = Oscillator.Oscillator(sp, dir = 'c')
d = Oscillator.Oscillator(sp, dir = 'd')

a.pos = 20


