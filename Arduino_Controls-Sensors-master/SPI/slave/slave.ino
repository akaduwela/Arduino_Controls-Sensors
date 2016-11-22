// Adapted from http://www.gammon.com.au/spi


// what to do with incoming data
byte command = 0;

// start of transaction, no command yet
void ss_falling ()
{
  command = 0;
}  // end of interrupt service routine (ISR) ss_falling

void setup (void)
{

  Serial.begin(115200);
  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);

  // turn on SPI in slave mode
  SPCR |= _BV(SPE);

  // turn on interrupts
  SPCR |= _BV(SPIE);

  // interrupt for SS falling edge
  attachInterrupt (0, ss_falling, FALLING);
  
}  // end of setup

//byte c;

// SPI interrupt routine
ISR (SPI_STC_vect)
{
  byte c = SPDR;
  
  SPDR = byte((millis() >> 8) & 0xFF);
  Serial.println(c);


}  // end of interrupt service routine (ISR) SPI_STC_vect


void loop (void)
{
// all done with interrupts
}  // end of loop
