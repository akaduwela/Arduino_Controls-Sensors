//I2C Parameters
//Hyperloop
//Kevin Kha

/*
Device Addressing (7-bit addressing):
ADC LTC2309: 0 ...						-0??10??-	//Tri-state Inputs A0 and A1, however we'll not use float (don't need that many addresses)
IO MCP23017: 0 1 0 0 A2 A1 A0			-0100???-
DAC MCP4725: 1 1 0 0 A2(0) A1(0) A0		-110000?-

		   _________ADC LTC2309 (Thermistors, Ammeter)
		   ||  _____IO MCP23017 (Tachometer)
		   ||  |||__DAC MCP4725 (Throttle)
		   vv  vvvv
I2C_DIP: 0b??XX????   //X = don't cares; can be anything. They're not connected.*/

const int ADC_Address[4] = {0x8, 0xA, 0x1A, 0x28};
const int IOX_Address[8] = {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27};
const int DAC_Address[2] = {0x60, 0x61};

typedef struct{
	int I2C_DIP;
	//ADC LTC2309 - 
	int ADC_device_0;
	//IOX MCP23017 - Tachometer
	int IOX_device_0;
	//DAC MCP4725 - Throttle
	int DAC_device_0;
} Engine_Control_System;

Engine_Control_System ENGINE_0{
	I2C_DIP = ;
	ADC_device_0 = (I2C_DIP >> 6);
}

*Engine_Control_System Engine_Control_Init(int I2C_address_0_setting){


	return
}

/*ADC LTC2309
I2C Protocol:
	1. Master Write: Device Address
	2. Master Write: DIN (Input Data Word)
	3. 

Input Data Word (6-bit)
S/D | O/S | S1 | S0 | UNI | SLP

S/D = Single-Ended/_Differential (We'll always use Single-Ended here, so = 1)
O/S = Odd/_Sign (Used to select which channel)
S1 = Channel Select Bit 1 (Also used to select which channel)
S2 = Channel Select Bit 0 (Also used to select which channel)
UNI = Unipolar/_Bipolar (We'll always use Unipolar, so = 1)
SLP = Sleep Mode (We won't put this into sleep mode, so = 0)
*/
#define ADC_CONFIG 0x22		//0b1???10

//Single-Ended Channels
#define LTC2309_CHN_0 0x0
#define LTC2309_CHN_1 0x10
#define LTC2309_CHN_2 0x4
#define LTC2309_CHN_3 0x14
#define LTC2309_CHN_4 0x8
#define LTC2309_CHN_5 0x18
#define LTC2309_CHN_6 0xC
#define LTC2309_CHN_7 0x1C

//To select the channel, we can OR ADC_CONFIG with channel selection bits.
const int ADC_CHANNEL_SELECT[8] = {
	LTC2309_CHN_0 | ADC_CONFIG, 
	LTC2309_CHN_1 | ADC_CONFIG,
	LTC2309_CHN_2 | ADC_CONFIG,
	LTC2309_CHN_3 | ADC_CONFIG,
	LTC2309_CHN_4 | ADC_CONFIG,
	LTC2309_CHN_5 | ADC_CONFIG,
	LTC2309_CHN_6 | ADC_CONFIG,
	LTC2309_CHN_7 | ADC_CONFIG};

/*IOX MCP23017
The MCP23017 is a 16-bit IO Expander controlled via I2C; the device is split into two 8-bit ports.
The device is configured by a shared configuration register, IOCON, which consists of a byte. The settings are as follows:

IOX Configuration Byte (8-bit):
BANK | MIRROR | SEQOP | DISSLW | HAEN | ODR | INTPOL | NC

BANK = Sets the addressing of the registers of each port. (We'll want them to be sequential, so = 1)
MIRROR = Sets whether the Interrupt outputs are OR'd together. (We want this active for the BMS, so = 1) Does not affect tachometer
SEQOP = Sets whether addresses increment. (We want this active so we can read both PORTA and PORTB in one go, so = 0)

*/
#define IOX_CONFIG //0b1100010

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