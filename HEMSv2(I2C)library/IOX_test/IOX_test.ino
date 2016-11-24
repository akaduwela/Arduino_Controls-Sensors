#include "Wire.h"

#define ARDUINO

const uint8_t IOX_Address[8] = {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27};

#define IOX_CONFIG 0x42 //0b01100010

//Banked Addresses (IOCON.BANK = 0) This is also the default register mapping.
#define MCP23017_IODIRA 0x00
#define MCP23017_IPOLA 0x02
#define MCP23017_GPINTENA 0x04
#define MCP23017_DEFVALA 0x06
#define MCP23017_INTCONA 0x08
#define MCP23017_IOCONA 0x0A
#define MCP23017_GPPUA 0x0C
#define MCP23017_INTFA 0x0E
#define MCP23017_INTCAPA 0x10
#define MCP23017_GPIOA 0x12
#define MCP23017_OLATA 0x14

#define MCP23017_IODIRB 0x01
#define MCP23017_IPOLB 0x03
#define MCP23017_GPINTENB 0x05
#define MCP23017_DEFVALB 0x07
#define MCP23017_INTCONB 0x09
#define MCP23017_IOCONB 0x0B
#define MCP23017_GPPUB 0x0D
#define MCP23017_INTFB 0x0F
#define MCP23017_INTCAPB 0x11
#define MCP23017_GPIOB 0x13
#define MCP23017_OLATB 0x15

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
