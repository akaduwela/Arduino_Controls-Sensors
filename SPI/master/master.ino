// Adapted from http://www.gammon.com.au/spi

#include <SPI.h>

void setup (void)
{
  Serial.begin (115200);
  Serial.println ();
  pinMode(8, OUTPUT);
  
  //digitalWrite(SS, HIGH);  // ensure SS stays high for now
  digitalWrite(8, HIGH);  // ensure SS stays high for now

  // Put SCK, MOSI, SS pins into output mode
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin ();

  // Slow down the master a bit
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  
}  // end of setup

byte transferAndWait (const byte what)
{
  byte a = SPI.transfer (what);
  delayMicroseconds (100);
  return a;
} // end of transferAndWait

void loop (void)
{

  byte a, b, c, d;
  
  // enable Slave Select
  //digitalWrite(SS, LOW); 
  digitalWrite(8, LOW);   

  transferAndWait ('a');  // add command
  transferAndWait (10);
  a = transferAndWait (17);
  b = transferAndWait (33);
  c = transferAndWait (42);
  d = transferAndWait (0);

  // disable Slave Select
  //digitalWrite(SS, HIGH);
  digitalWrite(8, HIGH);

  Serial.println ("Data from slave:");
  Serial.println (a, DEC);
  Serial.println (b, DEC);
  Serial.println (c, DEC);
  Serial.println (d, DEC);
  Serial.println();
  
  delay (1000);  // 1 second delay 
}  // end of loop

