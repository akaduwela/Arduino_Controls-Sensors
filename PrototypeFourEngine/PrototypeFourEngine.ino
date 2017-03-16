/*Hyperloop Hover Engine Management System
   Stationary Test Rig Program
   Kevin Kha

   NOTES:
   To allow throttle and height command, make sure that your Serial Monitor is using the "newline" setting.
*/

#include "HEMS.h"

//#define TEST_RIG_I2C_DIP 0b00000000   //See HEMS.h for how the DIP switch changes I2C hardware addresses

// Global variables.
String inputString = "";
float throttle_value = 0;
float height_value = 0;
float stoptime = 0.0;
float current_throttle_voltage = 0;
float target_throttle_voltage = 0;
uint8_t combined_alarm;

#define SERIAL_BAUD_RATE 9600

//Run Parameters
#define MAX_RUNTIME 60.0
#define THROTTLE_PRECISION 0.1
#define ON_THRESHOLD 1.0
#define TARGET_THROTTLE 1.0

#define SAFETIES 0


HEMS* engineFwdLeft;
HEMS* engineBackLeft;
HEMS* engineFwdRight;
HEMS* engineBackRight;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  //Serial.println(TWI_FREQ);
  Serial.println("Hyperloop Hover Engine Management System");
  Serial.println("Stationary Test Rig");
  Serial.println("To allow throttle and height command, Serial Monitor must be using the newline setting.");
  Serial.println("To set the throttle voltage, type in T#### where #### is between 0.00 and 5.00 [V]");
  //Serial.println("To set the engine height, type in H#### where #### is between 4.10 and 54.9 [mm]");
  inputString.reserve(10);

  //Setup Linear Actuator
  //linear_actuator_initialize();
  Wire.begin();
  Wire1.begin();

  //Setup HEMS
  engineFwdLeft = initialize_HEMS(0, 0b00000000);
  engineBackLeft = initialize_HEMS(0, 0b01001001);
  engineFwdRight = initialize_HEMS(1, 0b00000000);
  engineBackRight = initialize_HEMS(1, 0b01001001);
  delay(2000);
}

void loop() {
  if (abs(target_throttle_voltage - current_throttle_voltage) >  THROTTLE_PRECISION / 2) {
    if (current_throttle_voltage < target_throttle_voltage)
      current_throttle_voltage += THROTTLE_PRECISION;
    else
      current_throttle_voltage -= THROTTLE_PRECISION;
  }
  if(runtime() > stoptime){
    current_throttle_voltage = 0;
  }

  Serial.print("Target Throttle: ");
  Serial.println(target_throttle_voltage);

  engineFwdLeft->throttle_voltage = current_throttle_voltage;
  engineBackLeft->throttle_voltage = current_throttle_voltage;
  engineFwdRight->throttle_voltage = current_throttle_voltage;
  engineBackRight->throttle_voltage = current_throttle_voltage;

  update_HEMS(engineFwdLeft);
  update_HEMS(engineBackLeft);
  update_HEMS(engineFwdRight);
  update_HEMS(engineBackRight);

  Serial.print("FL:\t");
  printHEMSdata(engineFwdLeft);
  Serial.print("BL:\t");
  printHEMSdata(engineBackLeft);
  Serial.print("FR:\t");
  printHEMSdata(engineFwdRight);
  Serial.print("BR:\t");
  printHEMSdata(engineBackRight);

  #if SAFETIES
  combined_alarm = engineFwdLeft->alarm | engineBackLeft->alarm | engineFwdRight | engineBackRight;
  if(combined_alarm > 0){
    target_throttle_voltage = 0;
    current_throttle_voltage = 0;
  }
  #endif
  Serial.println();
}

void serialEvent() {
  while (Serial.available()) {
    char received_char = (char)Serial.read();
    if (received_char == '\n') { //Detects when a command has been entered. Requires the "newline" setting to be active (so the Serial monitor automatically appends a newline character '\n' to any inputs.
      char command_char = inputString.charAt(0); //Figure out which command, based on the first letter in the input.

      if (inputString == "START") {
        Serial.println("Initializing Test Sequence...");
        Serial.print("Max Runtime [s]: \t");
        Serial.println(MAX_RUNTIME);
        Serial.print("Max Temperature [C]: \t");
        Serial.println(SAFE_TEMPERATURE);
        Serial.print("Max Current [A]: \t");
        Serial.println(SAFE_TEMPERATURE);
        current_throttle_voltage = ON_THRESHOLD;
        target_throttle_voltage = TARGET_THROTTLE;
        stoptime = runtime() + MAX_RUNTIME;
      }
      else if (inputString == "STOP") {
        Serial.println("Stopping...");
        target_throttle_voltage = 0;
      }

      //Execute the command with the value stored in the rest of the input.
      else if (command_char == 'T') {
        float throttle_value = constrain(inputString.substring(1).toFloat(), DAC_MIN, DAC_MAX); //make sure the throttle input is within allowable bounds
        Serial.print("New Throttle Value: ");
        Serial.println(throttle_value);
        target_throttle_voltage = throttle_value;
      }
      else if (command_char == 'H') { //Set the height
        //height_value = constrain(inputString.substring(1).toFloat(), HEIGHT_MIN, HEIGHT_MAX); //make sure the height input is within allowable bounds
        Serial.print("Linear Actuator Set: ");
        Serial.println(height_value);
        //linear_actuator_set(height_value);
      }
      else
        Serial.println("Unrecognized Input; T#### for Throttle, H#### for Height.");
      inputString = "";
      return;
    }
    inputString += received_char;
  }
}

void printHEMSdata(HEMS* engine) {
  Serial.print(engine->timestamp);
  Serial.print("s\t");
  Serial.print(engine->throttle_voltage);
  Serial.print("V\t");
  Serial.print(engine->tachometer_counter);
  Serial.print("ct\t");
  Serial.print(engine->rpm);
  Serial.print("RPM\t");
  Serial.print(engine->amps);
  Serial.print("A\t");
  Serial.print(engine->temperatures[0]);
  Serial.print("C\t");
  Serial.print(engine->temperatures[1]);
  Serial.print("C\t");
  Serial.print(engine->temperatures[2]);
  Serial.print("C\t");
  Serial.print(engine->temperatures[3]);
  Serial.print("C\t");
  Serial.println(engine->alarm);
}

