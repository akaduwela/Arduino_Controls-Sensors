// I2C code for interfacing with the TI bq7692000 BMS
// UCSB Hyperloop 2016
// Tristan Seroff

// Hardware setup:
// SDA on board => A4 on Arduino (Uno)
// SCK on board => A5 on Arduino (Uno)
// GND => GND
// BATT+/BATT- on board => 18V power supply

#include <Wire.h>

// Device address for the BMS board
#define I2CADDRESS 0x08

void writeByte(byte reg_address, byte data){
  // Write a single byte to a register on the BMS.
  // reg_address => the register address to write to.
  // data => the data to write to that register.
  
  // Begin transmit session to the device
  Wire.beginTransmission(I2CADDRESS);   
  // Send register address that we want to write to
  Wire.write(reg_address);
  // Write the data byte that was given
  Wire.write(data);
  // End transmit session (and actually send the address and data buffer). Returns (Arduino-defined) error code if failed.
  byte ret = Wire.endTransmission();
  
  // Print status of operation
  if (ret != 0){
    Serial.print("Write failed! Error code: ");
    Serial.println(ret);
  }
  else{
    Serial.print("Wrote ");
    Serial.print(data, HEX);
    Serial.print(" (");
    Serial.print(data, BIN);
    Serial.print(") to address ");
    Serial.println(reg_address, HEX);
  }
}

byte readByte(byte reg_address){
  // Read a single byte from a register on the BMS.
  // reg_address => address of the register to read from.
  
  // Begin transmit session to the device
  Wire.beginTransmission(I2CADDRESS);   
  // Send register address that we want to read from
  Wire.write(reg_address);
  // End transmit session (and actually send the register address). Returns (Arduino-defined) error code if failed.
  byte ret = Wire.endTransmission();
  
  // Request the actual data (1 byte)
  Wire.requestFrom(I2CADDRESS, 1);

  byte data = 0;

  // Get the data from the receive buffer
  if (!Wire.available()){
    Serial.print("Received no data back from the slave device for address ");
    Serial.print(reg_address, HEX);
    Serial.println("!");
  }
  else{
    // Receive the byte
    data = Wire.read();
    // Print it
    //Serial.println(data, BIN);
  }
  
  return data;
}

int read14Bits(byte first_reg_address){
  // Read a 14-bit data value from two adjacent registers on the BMS.
  // first_reg_address = address of first register to read from (out of two). Entering 0x0A will read registers 0x0A and 0x0B.
  
  int data = 0; 
  
  // Most significant byte has only 6 meaningful bits.
  data = (readByte(first_reg_address) & 0b00111111) << 8;
  
  // Second significant byte is a full byte.
  data |= readByte(first_reg_address + 1);
  
  Serial.print("Data read from addresses ");
  Serial.print(first_reg_address, HEX);
  Serial.print(" and ");
  Serial.print((first_reg_address + 1), HEX);
  Serial.print(": ");
  Serial.print(data, HEX);
  Serial.print(" (");
  Serial.print(data, BIN);
  Serial.println(")");
  
  return data;
}

void setup()
{
  // Init I^2C bus
  Wire.begin(I2CADDRESS);
  // Init serial connection to terminal
  Serial.begin(115200);
  Serial.println("Setup finished.");
}

void loop()
{ 
  // Read chip die temperature (TS1_HI and TS1_LO)
  read14Bits(0x2C);
  
  // Read cell 1 voltage (VC1_HI and VC1_LO)
  read14Bits(0x0C);
  
  delay(500);
}
