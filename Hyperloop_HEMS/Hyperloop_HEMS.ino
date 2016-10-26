//Hyperloop Hover Engine Monitoring System
//Kevin Kha

#include "HEMS.h"

#define DIAGNOSTICS_MODE	1	// 0 = OFF, 1 = ON.
/*The definitions below are used to enable or disable certain functions. ONLY WORKS DURING DIAGNOSTICS MODE.
  If Diagnostics Mode is off, all functions will be enabled regardless.*/
#define THERMOMETER_ENABLED 1
#define TACHOMETER_ENABLED 1
#define AMMETER_ENABLED 1

void setup() {
#if DIAGNOSTICS_MODE
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.println("Hyperloop Hover Engine Monitoring System");
  Serial.println("Diagnostics Mode Activated");
  print_calibration_settings();
#endif //DIAGNOSTICS_MODE

  //Setup tachometer
#if !DIAGNOSTICS_MODE || TACHOMETER_ENABLED
  pinMode(TACHOMETER_0, INPUT);
  attachInterrupt(digitalPinToInterrupt(TACHOMETER_0), &tachometer_handler, RISING);
#endif //TACHOMETER_ENABLED
}

void loop() {
  // put your main code here, to run repeatedly:
#if !DIAGNOSTICS_MODE || THERMOMETER_ENABLED
  record_temperatures();
#endif //THERMOMETER_ENABLED

#if DIAGNOSTICS_MODE
  /*----------------------------------Print Results*/
  print_temperatures();
  print_tachometer_period();
  Serial.println();
  delay(1000);
#endif //DIAGNOSTICS_MODE
}



