//Hyperloop Hover Engine Monitoring System
//Kevin Kha

#include "HEMS.h"

#define SERIAL_BAUD_RATE 9600

void setup() {
  //Select appropriate calibration data stored in LEMS.h
  select_engine(CURRENT_ENGINE);

  #ifdef CALIBRATION_MODE
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.println("Hyperloop Hover Engine Monitoring System");
  Serial.println("Calibration Mode Activated");
  Serial.println("Current Calibration Settings:");

  #endif //CALIBRATION_MODE
}

void loop() {
  // put your main code here, to run repeatedly:
  record_temperatures();

  #ifdef CALIBRATION_MODE
  //Print Results
  

  #endif //CALIBRATION_MODE
}
