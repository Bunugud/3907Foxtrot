//
//    FILE: tca9548_search_device.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo TCA9548 I2C multiplexer
//     URL: https://github.com/RobTillaart/TCA9548


#include "TCA9548.h"
#define offset 52
TCA9548 MP_0(0x70);
TCA9548 MP_1(0x71);

uint8_t searchAddress = 0x29;   //  dummy, adjust to your needs.


void setup()
{
  pinMode(offset, OUTPUT);
  digitalWrite(offset, HIGH);
  Serial.begin(9600);
  Serial.println(__FILE__);
  Serial.println();

  Wire.begin();
  if (MP_0.begin() == false)
  {
    Serial.println("Could not connect to TCA9548 multiplexer.");
  }

  Serial.println("\nScan the channels of the multiplexer for searchAddress.\n");
  for (int chan = 0; chan < 8; chan++)
  {
    MP_0.selectChannel(chan);
    bool b = MP_0.isConnected(searchAddress);
    Serial.print("CHAN: ");
    Serial.print(chan);
    Serial.print("\t");
    Serial.print( b ? "found!" : "x");
  }
  Serial.println();

  Serial.println("done...");
  MP_0.disableChannel(7);


  if (MP_1.begin() == false)
  {
    Serial.println("Could not connect to TCA9548 multiplexer.");
  }

  Serial.println("\nScan the channels of the multiplexer for searchAddress.\n");
  for (int chan = 0; chan < 8; chan++)
  {
    MP_1.selectChannel(chan);
    bool b = MP_1.isConnected(searchAddress);
    Serial.print("CHAN: ");
    Serial.print(chan);
    Serial.print("\t");
    Serial.print( b ? "found!" : "x");
  }
  Serial.println();

  Serial.println("done...");
}

void loop()
{
}


//  -- END OF FILE --
