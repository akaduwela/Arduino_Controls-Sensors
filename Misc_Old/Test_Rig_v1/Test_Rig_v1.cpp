//Hyperloop Hover Engine Monitoring System
//Kevin Kha

#include "Test_Rig_v1.h"

// Global variables.
DAC_shield throttle;
String inputString = "";
float Throttle_value = 0;
float height_value = 0;

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
  //Set up an interrupt on TACHOMETER_0 pin that triggers the tachometer_handler function whenever that pin changes from LOW to HIGH (RISING).
  attachInterrupt(digitalPinToInterrupt(TACHOMETER_0), &tachometer_handler, RISING); 
  delay(1000);
}

//Print the current
void print_amps(int amps){
  Serial.print(amps);
  Serial.print("A\t");
}

//Print out all of the temperatures
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

void set_Throttle(int target_Throttle) {
  Serial.print("New Throttle Value: ");
  Serial.println(target_Throttle);
  throttle.set(THROTTLE_DAC_PORT, target_Throttle);
}

void set_Height(float target_Height) {
  Serial.print("Linear Actuator Set: ");
  Serial.println(target_Height);
  linear_actuator_set(target_Height);
}

//What to do if an error is detected (overcurrent or overtemperature)
void emergency_shutdown(int error){
  if (error){
    Serial.print("STOP");

    //Shut down the engine (throttle -> 0);
    throttle.set(THROTTLE_DAC_PORT, 0);
  }
  else
  Serial.print("OK"); 
}

//Handles the Serial Commands
void serialEvent() {
  while (Serial.available()) {
    char received_char = (char)Serial.read();
    if (received_char == '\n') { //Detects when a command has been entered. Requires the "newline" setting to be active (so the Serial monitor automatically appends a newline character '\n' to any inputs.
      char command_char = inputString.charAt(0); //Figure out which command, based on the first letter in the input.

      //Execute the command with the value stored in the rest of the input.
      if (command_char == 'T'){
        Throttle_value = constrain(inputString.substring(1).toFloat(), THROTTLE_MIN, THROTTLE_MAX); //make sure the throttle input is within allowable bounds
        set_Throttle(Throttle_value);
      }
      else if (command_char == 'H'){ //Set the height
        height_value = constrain(inputString.substring(1).toFloat(), HEIGHT_MIN, HEIGHT_MAX); //make sure the height input is within allowable bounds
        set_Height(height_value);
      }
      else
        Serial.println("Unrecognized Input; T### for Throttle, H### for Height.");
      inputString = "";
      return;
    }
    inputString += received_char;
  }
}
