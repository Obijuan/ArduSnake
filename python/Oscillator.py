#!/usr/bin/python
# -*- coding: utf-8 -*-

#-----------------------------------------------------------------
#-- Oscillator class
#-- Juan Gonzalez-Gomez (obijuan).  Feb-2015
#-----------------------------------------------------------------
#-- Class for controlling oscillators attached to servos
#-- The firmware  Oscillator-server-v2 should be upload to the 
#-- zum / arduino board
#-----------------------------------------------------------------

#--Command definitions
CMD_PLAY = 'P'
CMD_STOP = 'S'
CMD_SET_A = 'A'
CMD_SET_O = 'O'
CMD_END = '\r'

class IncorrectAngle():
  pass

class Oscillator(object):
  """Oscillator class, for accessing to all the oscillators"""
  
  def __init__(self, sp, dir):
    """Arguments: serial port and servo id"""
    
    self.sp = sp     #--- Serial device
    self.dir = dir   #--- Servo id
    self._A  = 45    #--- default amplitude
    self._O  = 0     #--- default offset
    self._T  = 2000  #--- default period
    self._Ph = 0     #--- default phase
    
  def __str__(self):
    str1 = "Oscillator: {}\n".format(self.dir)
    str2 = "Serial port: {}".format(self.sp.name)
    return str1 + str2
  
  def play(self):
    """Start the oscillator"""
    
    #-- Build the frame
    frame = self.dir + CMD_PLAY + CMD_END
    
    #-- Debug
    print(frame)
    
    #-- Send the frame
    self.sp.write(frame)
    
  def stop(self):
    """Stop de oscillator"""
    
    #-- Build the frame
    frame = self.dir + CMD_STOP + CMD_END
    
    #-- Debug
    print(frame)
    
    #-- Send the frame
    self.sp.write(frame)
    
  def set_A(self, A):
    """Set the oscillator amplitude"""
    
    #-- Check that the amplitude in the range [0, 90] 
    if not (0 <= A <= 90): 
      raise IncorrectAngle()
      return
    
    #-- Build the frame
    frame = self.dir + CMD_SET_A + str(A) + CMD_END
    
    #-- Debug
    print(frame)
    
    #-- Send the frame
    self.sp.write(frame)
    
    #-- Store the current amplitude
    self._A = A
    
  @property
  def A(self):
    """Attribute: Return the current amplitude"""
    print("Amplitude")
    return self._A
  
  @A.setter
  def A(self, value):
    """Attribute: Set the amplitude"""
    self.set_A(value)

  def set_O(self, O):
    """Set the oscillator offset"""
    
    #-- Check that the offset is in the range [-90, 90] 
    if not (-90 <= O <= 90): 
      raise IncorrectAngle()
      return
    
    #-- Build the frame
    frame = self.dir + CMD_SET_O + str(O) + CMD_END
    
    #-- Debug
    print(frame)
    
    #-- Send the frame
    self.sp.write(frame)
    
    #-- Store the current offset
    self._O = O
    
  @property
  def O(self):
    """Attribute: Return the current offset"""
    return self._O
  
  @O.setter
  def O(self, value):
    """Attribute: Set the offset"""
    self.set_O(value)
