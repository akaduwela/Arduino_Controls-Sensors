//Hyperloop Hover Engine Monitoring System
//Kevin Kha

#include "Test_Rig.h"

// Global variables.
DAC_shield throttle;
String inputString = "";
int RPM_value = 0;
int height_value = 0;

void rig_initialize(){
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.println("Hyperloop Hover Engine Monitoring System");
  Serial.println("Diagnostics Mode Activated");

  //Setup throttle
  throttle.prep();
  throttle.set(THROTTLE_DAC_PORT, 0);
  //Serial.println("Typing in a number between 0 and 255 will change the throttle.");
  inputString.reserve(5);

  //Setup Linear Actuator
  linear_actuator_initialize();

  //Setup tachometer
  pinMode(TACHOMETER_0, INPUT);
  attachInterrupt(digitalPinToInterrupt(TACHOMETER_0), &tachometer_handler, RISING);
  delay(1000);
}

void print_amps(int amps){
  Serial.print(amps);
  Serial.print("A\t");
}

void print_temperatures(int *recorded_temps) {
  for (int temp_counter = 0; temp_counter < NUM_THERMISTORS; temp_counter++) {
    Serial.print(recorded_temps[temp_counter]);
    Serial.print("C\t");
  }
}

void print_RPM(int RPM) {
  Serial.print(RPM);
  Serial.print("RPM\t");
}

void set_RPM(int target_RPM) {
  Serial.print("New Throttle Value: ");
  Serial.println(target_RPM);
  throttle.set(THROTTLE_DAC_PORT, target_RPM);
}

void set_Height(int target_Height) {
  Serial.print("Linear Actuator Set: ");
  Serial.println(target_Height);
  linear_actuator_set(target_Height);
}

void emergency_shutdown(int error){
  if (error){
    Serial.print("STOP");
    throttle.set(THROTTLE_DAC_PORT, 0);
  }
  else
  Serial.print("OK"); 
}

void serialEvent() {
  while (Serial.available()) {
    char received_char = (char)Serial.read();
    if (received_char == '\n') {
      char command_char = inputString.charAt(0);
      if (command_char == 'T'){
        RPM_value = constrain(inputString.substring(1).toInt(), RPM_MIN, RPM_MAX);
        set_RPM(RPM_value);
      }
      else if (command_char == 'H'){
        height_value = constrain(inputString.substring(1).toInt(), HEIGHT_MIN, HEIGHT_MAX);
        set_Height(height_value);
      }
      else
        Serial.println("Unrecognized Input; T### for Throttle, L### for Linear Actuator.");
      inputString = "";
      return;
    }
    inputString += received_char;
  }
}
