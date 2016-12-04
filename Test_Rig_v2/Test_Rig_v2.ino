/*Hyperloop Hover Engine Management System
 * Stationary Test Rig Program
 * Kevin Kha
 * 
 * NOTES:
 * To allow throttle and height command, make sure that your Serial Monitor is using the "newline" setting.
 */

#include "Linear_Actuator.h"
#include "HEMS.h"

#define TEST_RIG_I2C_DIP 0b00000000   //See HEMS.h for how the DIP switch changes I2C hardware addresses

// Global variables.
String inputString = "";
float throttle_value = 0;
float height_value = 0;

#define SERIAL_BAUD_RATE 9600

HEMS* myhems;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.println("Hyperloop Hover Engine Management System");
  Serial.println("Stationary Test Rig");
  Serial.println("To allow throttle and height command, Serial Monitor must be using the newline setting.");
  Serial.println("To set the throttle voltage, type in T#### where #### is between 0.00 and 5.00 [V]");
  Serial.println("To set the engine height, type in H#### where #### is between 4.10 and 54.9 [mm]");
  inputString.reserve(5);

  //Setup Linear Actuator
  linear_actuator_initialize();
  Wire.begin();

  //Setup HEMS
  myhems = initialize_HEMS(0, TEST_RIG_I2C_DIP);
  delay(2000);
}

void loop() {
  update_HEMS(myhems);
  Serial.print(myhems->timestamp);
  Serial.print("s\t");
  Serial.print(myhems->throttle_voltage);
  Serial.print("V\t");
  Serial.print(myhems->tachometer_counter);
  Serial.print("ct\t");
  Serial.print(myhems->rpm);
  Serial.print("RPM\t");
  Serial.print(myhems->amps);
  Serial.print("A\t");
  Serial.print(myhems->temperatures[0]);
  Serial.print("C\t");
  Serial.print(myhems->temperatures[1]);
  Serial.print("C\t");
  Serial.print(myhems->temperatures[2]);
  Serial.print("C\t");
  Serial.print(myhems->temperatures[3]);
  Serial.print("C\t");
  Serial.println(myhems->alarm);
  delay(500);
}

void serialEvent() {
  while (Serial.available()) {
    char received_char = (char)Serial.read();
    if (received_char == '\n') { //Detects when a command has been entered. Requires the "newline" setting to be active (so the Serial monitor automatically appends a newline character '\n' to any inputs.
      char command_char = inputString.charAt(0); //Figure out which command, based on the first letter in the input.

      //Execute the command with the value stored in the rest of the input.
      if (command_char == 'T') {
        float throttle_value = constrain(inputString.substring(1).toFloat(), DAC_MIN, DAC_MAX); //make sure the throttle input is within allowable bounds
        Serial.print("New Throttle Value: ");
        Serial.println(throttle_value);
        myhems->throttle_voltage = throttle_value;
      }
      else if (command_char == 'H') { //Set the height
        height_value = constrain(inputString.substring(1).toFloat(), HEIGHT_MIN, HEIGHT_MAX); //make sure the height input is within allowable bounds
        Serial.print("Linear Actuator Set: ");
        Serial.println(height_value);
        linear_actuator_set(height_value);
      }
      else
        Serial.println("Unrecognized Input; T#### for Throttle, H#### for Height.");
      inputString = "";
      return;
    }
    inputString += received_char;
  }
}
