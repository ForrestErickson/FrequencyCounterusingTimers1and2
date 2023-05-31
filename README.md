# FrequencyCounterusingTimers1and2

Linearized control of a PWM fan.   RPM measured by Frequency Counter using Timers 1 and 2

File: FrequencyCounterusingTimers1and2.ino
By: Forrest Lee Erickson
Date: 20230523 Initial release.

### About:
Linearized control of a PWM fan.  
RPM measured by Frequency Counter using Timers 1 & 2  
Frequencey counter based on code modified from here: https://akuzechie.blogspot.com/2021/02/frequency-counter-using-arduino-timers.html  
Information on Arduino UNO counter use here: https://docs.arduino.cc/tutorials/generic/secrets-of-arduino-pwm  

### Hardware: 
Run this on an Arduino UNO.  
Fan tachometer is input on pin D5 and a 10K pull up to Vcc is used.  
Output PWM to fan on D6 through a transistor which inverts the PWM.  
Simple user interface:  
The user will enter a fan set point from 0 to 255 for direct control.  
Serial input <0 to stop auto increment, > 255 to start auto increment.  

### License: 
This firmware is dedicated and released to the public domain.  
Warranty: This firmware is designed to kill you and render the earth uninhabitable, however is not guaranteed to do so.  
