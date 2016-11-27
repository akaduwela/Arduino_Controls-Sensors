#include "Wire.h"
#include "HEMS.h"

#define ARDUINO

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  IOX_setup(IOX_Address[0]);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(IOX_read(IOX_Address[0]));
  delay(1000);
}

void IOX_setup(uint8_t IOX_address){
  #ifdef ARDUINO
  Wire.beginTransmission(IOX_address);
  Wire.write(MCP23017_IOCONA); //IOCON register location
  Wire.write(IOX_CONFIG);
  Wire.endTransmission(true);
  
  #else //LPC code

  #endif //ARDUINO
}

uint16_t IOX_read(uint8_t IOX_address){
  #ifdef ARDUINO
  Wire.beginTransmission(IOX_address);
  Wire.write(MCP23017_GPIOA); //GPIOAB register location
  Wire.endTransmission(false);
  Wire.requestFrom(IOX_address, 2, true);
  uint16_t IOX_value = (Wire.read() << 8) | (Wire.read()); //A7 A6 A5 A4 A3 A2 A1 A0 B7 B6 B5 B4 B3 B2 B1 B0
  #else //LPC code

  #endif //ARDUINO
  return IOX_value;
}
