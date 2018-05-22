/*
Code by Cameron May, www.cameronmay.co.nz
camerondmay@gmail.com
v.003, last updated 2018

This code is used to independently strobe/pulse two separate pins (2 and 4) at 
frequencies less than 1 millisecond, which is too fast for basic digitalwrite codes.
Code utilises direct port manipulation, and is based on the following tutorial 
- https://forum.arduino.cc/index.php?topic=355427.0

In addition, this code allows for two strobes to concurrently run at the same time. 
To achive this, two millis counters are recorded in two local states.
And those states are used by 4 statements to read 1 of 4 potential global states 
(ON-ON, ON-OFF, OFF-ON, OFF-OFF)

*/

// strobe 1 information

unsigned long freqStr1 = 30000; // pulse frequency (including the off Cycle) in Microseconds
unsigned long duraStr1 = 300; // duration between each pulse (the on Cycle) in Microseconds.
unsigned long previousMicros1 = 0; // used to reset counter
int pulseState1 = LOW; // initial stored state for pulse on pin 1

// strobe 2 information

unsigned long freqStr2 = 100000; // as above, but for strobe 2
unsigned long duraStr2 = 300; // as above, but for strobe 2
unsigned long previousMicros2 = 0; // used to reset counter
int pulseState2 = LOW;  // initial stored state for pulse on pin 2

void setup() {
  pinMode (2, OUTPUT);
  pinMode (4, OUTPUT);
}

void loop() {

  unsigned long currentMicros = micros();

  // Pulse cycle 1
  if (currentMicros - previousMicros1 > duraStr1)
    pulseState1 = LOW;
  else
    pulseState1 = HIGH;
  if (currentMicros - previousMicros1 > freqStr1)
  {
    previousMicros1 = currentMicros;
  }

  // Pulse Cycle 2
  if (currentMicros - previousMicros2 > duraStr2)
    pulseState2 = LOW;
  else
    pulseState2 = HIGH;
  if (currentMicros - previousMicros2 > freqStr2)
  {
    previousMicros2 = currentMicros;
  }

  // Now we state those pulse states from the code above, and use them to inform one of 4 global states.

  if (pulseState1 == 1 && pulseState2 == 1)
    PORTD = PORTD | 0b00010100; // Arduino Digital port 2 and 4 on

  if (pulseState1 == 1 && pulseState2 == 0)
    PORTD = PORTD | 0b00010000; // Arduino Digital port 2 off, 4 on

  if (pulseState1 == 0 && pulseState2 == 1)
    PORTD = PORTD | 0b00000100; // Arduino Digital port 2 on, 4 off

  if (pulseState1 == 0 && pulseState2 == 0)
    PORTD = PORTD & 0b00000000; // Arduino Digital port 2 and 4 off

}
