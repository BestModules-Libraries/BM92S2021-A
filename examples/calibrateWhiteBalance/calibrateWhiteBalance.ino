/*****************************************************************************************************
File:          calibrateWhiteBalance.ino
Description:    The method of white balance calibration is to place a standard white object on the module sensor with a 
                distance of about 10mm, light up the four LED lights of the module and call the white balance calibration 
                command.
******************************************************************************************************/
#include <BM92S2021-A.h>

BM92S2021_A Sensor;
uint16_t EID = 2;
  
void setup()
{
  Serial.begin(9600);  
  Sensor.begin(); 
  Sensor.openLED(EID);
  if(Sensor.calibrateWhiteBalance(EID))
  {
    Serial.println("setWhiteBalance scuess");
   }
    else Serial.println("setWhiteBalance fail");
}                                     


void loop() 
{  
}
