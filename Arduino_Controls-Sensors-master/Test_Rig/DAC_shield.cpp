//DAC_shield
//Soldering Lab
//Kevin Kha F2015

#include "DAC_shield.h"

void DAC_shield::prep()
{
	pinMode(DATA, OUTPUT);
	pinMode(CLOCK, OUTPUT);
	pinMode(LATCH, OUTPUT);
	pinMode(OUT_SEL_0, OUTPUT);
	pinMode(OUT_SEL_1, OUTPUT);

  //Preset outputs to 0V
  set(0, 0);
  set(1, 0);
  set(2, 0);
  set(3, 0);
}

void DAC_shield::set(byte output_select, byte output_value)
{
  //Switch to the selected DAC
  digitalWrite(OUT_SEL_0, bitRead(output_select, 0));
  digitalWrite(OUT_SEL_1, bitRead(output_select, 1));
  
  //Enable transparency (Selected DAC can be updated)
  digitalWrite(LATCH, LOW);
  
  //Write value to the inputs and update DAC
  shiftOut(DATA, CLOCK, MSBFIRST, output_value);
  
  //Disable transparency (Selected DAC cannot be updated anymore, saving the current input values)
  digitalWrite(LATCH, HIGH);
}