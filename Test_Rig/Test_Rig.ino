//Hyperloop Hover Engine Monitoring System
//Kevin Kha

#include "Test_Rig.h"
volatile int recorded_RPM = 0;
volatile uint16_t rotation_count = 0;
uint16_t old_rotation_count = 0;
uint8_t counts = 0;
int recorded_temps[NUM_THERMISTORS];
int recorded_amps = 0;

volatile unsigned long int previous_time_us = 0;
volatile unsigned long int current_time_us = 0;
volatile unsigned int tach_period_us = 0;

void setup() {
  rig_initialize();
  /*
  int start_time = millis();
  for (int i = 0; i < 1000; i++){
    tachometer_handler();
  }
  int end_time = millis();
  Serial.println(end_time - start_time);
  */
}

void loop() {

  // put your main code here, to run repeatedly:
  record_temperatures(recorded_temps);
  record_amps(&recorded_amps);

  /*----------------------------------Print Results*/
  Serial.print(millis() / 1000.0);
  Serial.print("s\t");

  current_time_us = millis(); 
  counts = ((rotation_count - old_rotation_count) * (100 - TACHOMETER_AVG_WEIGHT) + counts * TACHOMETER_AVG_WEIGHT) / 100;
  recorded_RPM = 60000.0 * counts / (current_time_us - previous_time_us);
  old_rotation_count = rotation_count;
  previous_time_us = current_time_us;

  Serial.print(rotation_count);
  Serial.print("\t");
  print_RPM(recorded_RPM);

  //Calculate RPM
  
  print_amps(recorded_amps);
  print_temperatures(recorded_temps);
  emergency_shutdown(error_flag);
  Serial.println();
  delay(500);
}

void tachometer_handler() {
  //This function uses micros(), which overflows (resets back to 0) after ~70 minutes.
  rotation_count++;
  /*
  current_time_us = micros(); 
  tach_period_us = (tach_period_us * TACHOMETER_AVG_WEIGHT + (100 - TACHOMETER_AVG_WEIGHT) * (current_time_us - previous_time_us)) / 100;
  if (tach_period_us > MIN_PERIOD_US) { //debouncing
    recorded_RPM = (1000000.0 / tach_period_us) * 60.0;
    //recorded_RPM++; //counter 
    previous_time_us = current_time_us  + TACHOMETER_HANDLER_OVERHEAD_US;
  }
  */
}

