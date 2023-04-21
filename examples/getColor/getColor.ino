/*****************************************************************************************************
File:             getColor.ino
Description:      This example demonstrates how to get the color.
Note:             The execution time of the color recognition function is related to the intensity of 
                  the ambient light. It takes longer time under low light conditions, and the maximum 
                  execution time is no more than 5ms.
                  As it takes a certain amount of time for MCU to collect the data of color sensor, 
                  the command interval of this function should be greater than 20ms.
******************************************************************************************************/
#include <BM92S2021-A.h>

BM92S2021_A Sensor;

uint16_t Color;
uint16_t EID = 2;
  
void setup()
{
  Serial.begin(9600);  
  Sensor.begin(); 
}                                     

void loop() 
{
  uint16_t color=0;
  Sensor.openLED(EID); 
  color=Sensor.getColor(EID);  
      Serial.print("The color is ");
      switch(color)  
      {
        case 0:
        {
          Serial.println("Unknow!");
          break;
        }
        case 1:
        {
          Serial.println("Red!");
          break;
        }
        case 2:
        {
          Serial.println("Orange!");
          break;
        }
        case 3:
        {
          Serial.println("Yellow!");
          break;
        }
        case 4:
        {
          Serial.println("Green!");
          break;
        }
        case 5:
        {
          Serial.println("Bule!");
          break;
        }
        case 6:
        {
          Serial.println("White!");
          break;
        }
      }
  delay(1000);
}
