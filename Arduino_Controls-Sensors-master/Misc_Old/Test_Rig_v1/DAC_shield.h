//DAC_shield
//Soldering Lab
//Kevin Kha F2015

#ifndef DAC_shield_H_
#define DAC_shield_H_

#include "Arduino.h"

class DAC_shield
{
public:
  void prep();
  void set(byte output_select, byte output_value);
private:
  const int DATA = 8;
  const int CLOCK = 9;
  const int LATCH = 10;
  const int OUT_SEL_0 = 12;
  const int OUT_SEL_1 = 11;
};

#endif