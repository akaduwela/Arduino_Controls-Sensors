/*Hyperloop Hover Engine Management System
 * Stationary Test Rig Program
 * Kevin Kha
 * 
 * NOTES:
 * To allow throttle and height command, make sure that your Serial Monitor is using the "newline" setting.
 */

#include "I2CPERIPHS.h"

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
  //Serial.println("To set the engine height, type in H#### where #### is between 4.10 and 54.9 [mm]");
  inputString.reserve(5);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  delay(1000);
  
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
  Serial.print(myhems->DAC_diagnostic);
  Serial.print("V\t");
  Serial.print(myhems->tachometer_counter[0]);
  Serial.print("ct\t");
  Serial.print(myhems->rpm[0]);
  Serial.print("RPM\t");
  Serial.print(myhems->tachometer_counter[1]);
  Serial.print("ct\t");
  Serial.print(myhems->rpm[1]);
  Serial.print("RPM\t");
  Serial.print(myhems->temperatures[0]);
  Serial.print("C\t");
  Serial.print(myhems->temperatures[1]);
  Serial.print("C\t");
  Serial.print(myhems->temperatures[2]);
  Serial.print("C\t");
  Serial.print(myhems->temperatures[3]);
  Serial.print("C\t");
  Serial.print(myhems->amps);
  Serial.print("A\t");
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
      else
        Serial.println("Unrecognized Input; T#### for Throttle.");
      inputString = "";
      return;
    }
    inputString += received_char;
  }
}
