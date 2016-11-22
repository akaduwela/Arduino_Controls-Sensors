//Hyperloop Hover Engine Monitoring System
//Kevin Kha

#include "HEMS.h"

/*The definitions below are used to enable or disable certain functions. ONLY WORKS DURING DIAGNOSTICS MODE.
  If Diagnostics Mode is off, all functions will be enabled regardless. 0 = OFF, 1 = ON.*/
#define THERMOMETER_ENABLED 1
#define THROTTLE_ENABLED 1
#define TACHOMETER_ENABLED 1
#define AMMETER_ENABLED 1

DAC_shield throttle;

String inputString = "";
int throttle_value = 0;
int linear_actuator_value = 0;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.println("Hyperloop Hover Engine Monitoring System");
  Serial.println("Diagnostics Mode Activated");
  print_calibration_settings();

#if THROTTLE_ENABLED
  //Setup throttle
  throttle.prep();
  Serial.println("Typing in a number between 0 and 255 will change the throttle.");
  inputString.reserve(5);
#endif //THROTTLE_ENABLED

  //Setup tachometer
#if TACHOMETER_ENABLED
  pinMode(TACHOMETER_0, INPUT);
  attachInterrupt(digitalPinToInterrupt(TACHOMETER_0), &tachometer_handler, RISING);
#endif //TACHOMETER_ENABLED
}

void loop() {
  // put your main code here, to run repeatedly:
#if THERMOMETER_ENABLED
  record_temperatures();
#endif //THERMOMETER_ENABLED

  /*----------------------------------Print Results*/
  print_temperatures();
  print_RPM();
  print_amps();
  Serial.println();
}

#if THROTTLE_ENABLED
void serialEvent() {
  while (Serial.available()) {
    char received_char = (char)Serial.read();
    if (received_char == '\n') {
      char command_char = inputString.charAt(0);
      if (command_char == 'T') {
        throttle_value = inputString.substring(1).toInt();
        Serial.print("New Throttle Value: ");
        throttle.set(THROTTLE_DAC_PORT, throttle_value);
      }
      else if(command_char == 'L'){
        linear_actuator_value = inputString.substring(1).toInt();
        Serial.print("Linear Actuator Set: ");
      }
      else{
        Serial.println("Unrecognized Input; T### for Throttle, L### for Linear Actuator.");
      }
      return;
    }
    inputString += received_char;
  }
}
#endif //THROTTLE_ENABLED



