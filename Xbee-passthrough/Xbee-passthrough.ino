#include <SoftwareSerial.h>

SoftwareSerial XBee(2, 3);

void setup()
{
  // Setup serial for communication with Xbee
  XBee.begin(9600);

  // Setup serial for communication with PC
  Serial.begin(9600);
}

void loop()
{
  // Forward all data from PC to Xbee
  while(Serial.available()){
    XBee.write(Serial.read());
  }
  
  // Forward all data from Xbee to PC
  while(XBee.available())
  { 
    Serial.write(XBee.read());
  }
}
