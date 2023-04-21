/*****************************************************************************************************
File:             setEID.ino
Description:      This example demonstrates how to initialize the BM92S and then set the EID.
Note:             1. The EID Default value is 0. Set the EID to the expected value before using the module.
                  2. When the EID is set, only one module can exist on the bus of the same interface.
                  3. After the EID is configured, a maximum of 16 modules with the same MID can be cascaded.
******************************************************************************************************/
#include <BM92S2021-A.h>
                                             //The EID of this module is factory configured and the value is 0.
uint16_t EID = 2;                            //The EID is used to distinguish between different modules with the same MID. EID by User configuration.
                                             //The EID is valued from 0 to 15
                                             //When broadcasting commands, mid and EID are zero.
BM92S2021_A Sensor;

void setup()
{
  Serial.begin(9600);
  Sensor.begin(); 
  
  if(Sensor.setEID(EID) == true)                                                           
  {  
     Serial.println("Set EID succeeded!");                                            
  }
  else
  {
     Serial.println("Set EID failed!"); 
  }
    Serial.print("FW Version is ");
    Serial.println(Sensor.getFWVer(EID),HEX);
}

void loop() {
}
