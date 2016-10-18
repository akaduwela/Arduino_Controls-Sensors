//Hyperloop Hover Engine Monitoring System
//Kevin Kha

#include "HEMS.h"

#define DIAGNOSTICS_MODE	0	// 0 = OFF, 1 = ON.

void setup() {
  #if DIAGNOSTICS_MODE
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.println("Hyperloop Hover Engine Monitoring System");
  Serial.println("Diagnostics Mode Activated");
  print_calibration_settings();
  #endif //DIAGNOSTICS_MODE
}

void loop() {
  // put your main code here, to run repeatedly:
  record_temperatures();

  #ifdef DIAGNOSTICS_MODE
  //Print Results
  

  #endif //CALIBRATION_MODE
}
