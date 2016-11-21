//Hyperloop Hover Engine Monitoring System
//Kevin Kha

#include "Test_Rig.h"
volatile int recorded_RPM = 0;
int recorded_temps[NUM_THERMISTORS];
int recorded_amps = 0;

volatile unsigned long int previous_time_us = 0;
volatile unsigned long int current_time_us = 0;
volatile unsigned int tach_period_us = 0;

void setup() {
  rig_initialize();
}

void loop() {
  // put your main code here, to run repeatedly:
  record_temperatures(recorded_temps);
  record_amps(&recorded_amps);

  /*----------------------------------Print Results*/
  Serial.print(millis() / 1000.0);
  Serial.print("s\t");
  print_RPM(recorded_RPM);
  print_amps(recorded_amps);
  print_temperatures(recorded_temps);
  emergency_shutdown(error_flag);
  Serial.println();
  delay(500);
}

void tachometer_handler() {
  //This function uses micros(), which overflows (resets back to 0) after ~70 minutes.
  current_time_us = millis(); 
  tach_period_us = (tach_period_us * TACHOMETER_AVG_WEIGHT + (100 - TACHOMETER_AVG_WEIGHT) * (current_time_us - previous_time_us)) / 100;
  if (tach_period_us > MIN_PERIOD_MS) { //debouncing
    //recorded_RPM = 1000.0 / tach_period_us * 60;
    recorded_RPM++;
    previous_time_us = current_time_us + TACHOMETER_HANDLER_OVERHEAD_US;
  }
}
