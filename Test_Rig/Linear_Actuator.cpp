#include "Arduino.h"
#include "Linear_Actuator.h"

int currentPosition = 0;
int destination = 0;
int difference = 0;//values for knowing location

void linear_actuator_initialize()
{
  pinMode(H_BRIDGE_0, OUTPUT);
  pinMode(H_BRIDGE_1, OUTPUT);
  digitalWrite(H_BRIDGE_0, HIGH);
  digitalWrite(H_BRIDGE_1, HIGH);
}

void linear_actuator_set(float height_value) {
  //Calculate the feedback potentiometer value that corresponds to the height
  int destination = map(height_value, HEIGHT_MAX, HEIGHT_MIN, FEEDBACK_MIN, FEEDBACK_MAX);
  Serial.print("Feedback Destination:\t");
  Serial.println(destination);
  if (abs(destination - analogRead(LINEAR_FEEDBACK)) > PRECISION) {
    currentPosition = analogRead(LINEAR_FEEDBACK); //check where you are
    Serial.print("Current Height:\t");
    Serial.println(map(currentPosition, HEIGHT_MAX, HEIGHT_MIN, FEEDBACK_MIN, FEEDBACK_MAX));
    
    // choose what action to take
    if (currentPosition < destination) 
      pullActuatorUntilStop(destination);
    else if(currentPosition > destination)
      pushActuatorUntilStop(destination);
  }
  Serial.println("In position!");
  stopActuator();
}//end void loop

void pushActuatorUntilStop(int destination) {
  while (abs(destination - analogRead(LINEAR_FEEDBACK)) > PRECISION)
    pushActuator();
  delay(25);
  stopActuator();
}//end pushActuatorUntilStop

void pullActuatorUntilStop(int destination) {
  while (abs(destination - analogRead(LINEAR_FEEDBACK)) > PRECISION)
    pullActuator();
  delay(25);
  stopActuator();
}//end pullActuatorUntilStop

void stopActuator() {
  digitalWrite(H_BRIDGE_0, HIGH);
  digitalWrite(H_BRIDGE_1, HIGH);
}//end stopActuator

void pushActuator() {
  digitalWrite(H_BRIDGE_0, HIGH);
  digitalWrite(H_BRIDGE_1, LOW);
}//end pushActuator

void pullActuator() {
  digitalWrite(H_BRIDGE_0, LOW);
  digitalWrite(H_BRIDGE_1, HIGH);
}//end pullActuator


