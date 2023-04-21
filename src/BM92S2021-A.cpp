/*****************************************************************
File:          BM92S2021-A.cpp
Author:        BESTMODULES
Description:   UART communication with the BM92S2021-A and obtain the corresponding value
History：         
V1.0.1  -- initial version;2023-01-06;Arduino IDE : v1.8.15
******************************************************************/
#include "BM92S2021-A.h"
/******************************************************************
Description: Constructor
Parameters:       
            *theSerial : Wire object if your board has more than one UART interface        
Return:          
Others:     
********************************************************************/
BM92S2021_A::BM92S2021_A(HardwareSerial *theSerial)
{
    _theSerial = theSerial;	
}
/********************************************************************
Description: Module Initial
Parameters:       
            band : Set the Module  band(Unique Value 9600)         
Return:          
Others:   If the hardware UART is initialized, the _softSerial 
          pointer is null, otherwise it is non-null       
*********************************************************************/
void BM92S2021_A::begin(uint32_t band)
{
  _theSerial->begin(band, SERIAL_9N1);
	delay(100);	
}

/**********************************************************
Description: Reset all modules on the bus.
Parameters:               
Return: 
Others:          
**********************************************************/
void BM92S2021_A::reset(void)
{
  _command_type = _Broadcast;
  sendData(0, _RESET, _tx_buf, 4);  
}

/**********************************************************
Description: Reset a single module.
Parameters:      
            EID: The EID of module,EID_Value is accetable between 0 and 15.       
Return:      true or false
Others:          
**********************************************************/
bool BM92S2021_A::reset(uint16_t EID)
{	
	_command_type = _Non_Broadcast;
	sendData(EID, _RESET, _tx_buf, 4); 	
	delay(20);
 if(readBytes(_rx_buf,4))
  { 
   if(_status == 0)
   {
     return true;
    }
    else
    {
     return false;
     }
  }
  else  
  {
    return false; 
  }
}

/**********************************************************
Description: Put all modules on the bus into standby mode
Parameters:                
Return: 
Others:          
**********************************************************/
void BM92S2021_A::standby(void)//UID = 0;UID = MID + EID;
{
	_command_type = _Broadcast;
	sendData(0, _standby, _tx_buf, 4);	
}

/**********************************************************
Description: Get the version information 
Parameters: 
            EID : The EID of module,EID_Value is accetable between 0 and 15.     
Return:      0:fail
             FWVer:Version information
Others:      
***********************************************************/
uint16_t BM92S2021_A::getFWVer(uint16_t EID)
{
	_command_type = _Non_Broadcast;
 uint16_t FWVer=0;
	sendData(EID, _GETFWVER, _tx_buf, 4);
	delay(20);
	if(readBytes(_rx_buf,6))
	{
		if(_status == 0)
		{
     FWVer=_rx_buf[4]<<8|_rx_buf[3];
     return FWVer;
    }
    else
    {
     return 0;
    }
  }
  else  
  {
    return 0; 
  }
}
/*************************************************************
Description: Wake up host enables/disables control.
Parameters:      
             EID : The EID of module,EID_Value is accetable between 0 and 15.
             isEnable: 
                  0 : DISABLE
                  1 : ENABLE      
Return:     true or false
Others:      
**************************************************************/
bool BM92S2021_A::remoteWU(uint16_t EID, uint16_t isEnable)
{
	_command_type = _Non_Broadcast;
	_tx_buf[3] = isEnable;
	sendData(EID, _REMOTEWU, _tx_buf, 5);
	delay(20);
  if(readBytes(_rx_buf,4))
  { 
   if(_status == 0)
   {
     return true;
    }
    else
    {
     return false;
     }
  }
  else	
  {
    return false; 
  }
}

/***************************************************************
Description: Turn on the LED auxiliary light.
Parameters:       
            EID : The EID of module,EID_Value is accetable between 0 and 15.     
Return:     true or false
Others:      
****************************************************************/
bool BM92S2021_A::openLED(uint16_t EID)
{
	_command_type = _Non_Broadcast;
	sendData(EID, _OPEN_LED, _tx_buf, 4);
    delay(20);	
  if(readBytes(_rx_buf,4))
  { 
   if(_status == 0)
   {
     return true;
    }
    else
    {
     return false;
     }
  }
  else  
  {
    return false; 
  }
}

/****************************************************************
Description: Turn off the LED auxiliary light.
Parameters:       
            EID : The EID of module,EID_Value is accetable between 0 and 15.     
Return:     true or false
Others:      
****************************************************************/
bool BM92S2021_A::closeLED(uint16_t EID)
{
	_command_type = _Non_Broadcast;
	sendData(EID, _CLOSE_LED, _tx_buf, 4); 
	delay(20);
   if(readBytes(_rx_buf,4))
  { 
   if(_status == 0)
   {
     return true;
    }
    else
    {
     return false;
     }
  }
  else  
  {
    return false; 
  }
	
}

/***************************************************************
Description: Get color information 
Parameters:   
            EID : The EID of module,EID_Value is accetable between 0 and 15.    
Return:    _rx_buf[3]: color information
           0x00 : other color
           0x01 : red
           0x02 : orange
           0x03 : yellow
           0x04 : green
           0x05 : bule
           0x06 : white
Others:      
****************************************************************/
uint16_t BM92S2021_A::getColor(uint16_t EID)
{
	_command_type = _Non_Broadcast;
	sendData(EID, _GET_COLOR, _tx_buf, 4); 
	delay(20);
  if(readBytes(_rx_buf,5))
  { 
   if(_status == 0)
   {
     return _rx_buf[3];
    }
    else
    {
     return 0;
     }
  }
  else  
  {
    return 0; 
  }
}
/*****************************************************************
Description: Get ambient light data 
Parameters:  
             EID : The EID of module,EID_Value is accetable between 0 and 15.    
Return:      _rx_buf[3]: ambient light data
Others:      
*******************************************************************/
uint16_t BM92S2021_A::readAmbientLight(uint16_t EID)
{
	_command_type = _Non_Broadcast;
	sendData(EID, _GET_LUM, _tx_buf, 4); 
	delay(20);
  if(readBytes(_rx_buf,5))
  { 
   if(_status == 0)
   {
     return _rx_buf[3];
    }
    else
    {
     return 0;
     }
  }
  else  
  {
    return 0; 
  }
}
/******************************************************************
Description: Get Full color information 
Parameters:   
              EID : The EID of module,EID_Value is accetable between 0 and 15.    
             buffer : Store Full color information
              buffer : 
             buffer[0] : R
             buffer[1] : G
             buffer[2] : B
Return:      true or false 
Others:      
******************************************************************/
bool BM92S2021_A::readRGBColor(uint16_t EID, uint16_t buffer[])
{
	_command_type = _Non_Broadcast;
	sendData( EID, _GET_FULL_COLOR, _tx_buf, 4);
    delay(20);	
  if(readBytes(_rx_buf,7))
	{
		if(0 == _status)
		{
			buffer[0] = _rx_buf[3]; //Red
			buffer[1] = _rx_buf[4]; //Green
			buffer[2] = _rx_buf[5]; //Bule
      return true;
		}
   else
   {
    return false;
   }
	}
	else
   {
    return false;
   }
}

/**************************************************************
Description: Set a single module EID (EID range: 0 to 15)
Parameters:       
              EID_Value : EID is to be set. 
Return:    true or false 
Others:      
***************************************************************/
bool BM92S2021_A::setEID(uint16_t EID_Value)//UID = 0
{
  _command_type = _Broadcast;
  sendData(0, _SETEID + EID_Value, _tx_buf, 4);
    delay(20);  
  if(readBytes(_rx_buf,4))
  { 
   if(_status == 0)
   {
     return true;
    }
    else
    {
     return false;
     }
  }
  else  
  {
    return false; 
  }
}

/******************************************************************
Description: Calibrated white balance 
Parameters:       
            EID : The EID of module,EID_Value is accetable between 0 and 15.     
Return:     true or false 
Others:      
******************************************************************/
bool BM92S2021_A::calibrateWhiteBalance(uint16_t EID)
{
	_command_type = _Non_Broadcast;
	sendData(EID, _SET_WB, _tx_buf, 4); 
	delay(20);
  if(readBytes(_rx_buf,4))
  { 
   if(_status == 0)
   {
     return true;
    }
    else
    {
     return false;
     }
  }
  else  
  {
    return false; 
  }
}
/*****************************************************************
Description: Set the upper and lower thresholds for wakeup
Parameters:       
             EID : The EID of module,EID_Value is accetable between 0 and 15.
             HighThre : Upper threshold
             LowThre : Lower threshold      
Return:     true or false
Others:      
******************************************************************/
bool BM92S2021_A::setRemoteWUThre(uint16_t EID, uint16_t LowThre, uint16_t HighThre)
{
	_command_type = _Non_Broadcast;
	_tx_buf[3] = LowThre;
	_tx_buf[4] = HighThre;
	sendData(EID, _RemoteWUThre, _tx_buf, 6); 
	delay(20);
  if(readBytes(_rx_buf,4))
  { 
   if(_status == 0)
   {
     return true;
    }
    else
    {
     return false;
     }
  }
  else  
  {
    return false; 
  }
}
/*-----------------------Private function -----------------------------*/
/********************************************************************
Description: The delay command is set for each module and the SyncAction command
             is used to synchronize the actions of different modules.
Parameters:              
Return: 
Others:          
*********************************************************************/
void BM92S2021_A::SyncAction(void)//UID = 0;
{
  _command_type = _Broadcast;
  sendData(0, _SYNCACTION, _tx_buf, 4);
}
/*********************************************************************
Description: Set the command to "delay execution", after which the module will execute the preset command 
             when it receives the SyncAction command.
Parameters:       
            EID : The EID of module,EID_Value is accetable between 0 and 15.     
Return:    true or false
Others:      
*********************************************************************/
uint16_t BM92S2021_A::closeLED_DELAY(uint16_t EID)
{
  _command_type = _Non_Broadcast;
  sendData(EID, _CLOSE_LED_DELAY, _tx_buf, 4); 
  delay(20);
  if(readBytes(_rx_buf,4))
  { 
   if(_status == 0)
   {
     return true;
    }
    else
    {
     return false;
     }
  }
  else  
  {
    return false; 
  }
}
/********************************************************************
Description: Set the command to "delay execution", after which the module will execute the preset command 
             when it receives the SyncAction command.
Parameters:       
            EID : The EID of module,EID_Value is accetable between 0 and 15.      
Return:      true or false
Others:      
*********************************************************************/
uint16_t BM92S2021_A::openLED_DELAY(uint16_t EID)
{
  _command_type = _Non_Broadcast;
  sendData( EID, _OPEN_LED_DELAY, _tx_buf, 4); 
  delay(20);
  if(readBytes(_rx_buf,4))
  { 
   if(_status == 0)
   {
     return true;
    }
    else
    {
     return false;
     }
  }
  else  
  {
    return false; 
  }
}
/********************************************************************
Description: Write data to the module through UART communication
Parameters:      
             EID : The EID of module,EID_Value is accetable between 0 and 15.
             Instr : Command code
             *buffer : The command parameter
             bufferSize : Number of parameters
    
Return:      true or false 
Others:      
********************************************************************/
bool BM92S2021_A::sendData(uint16_t EID, uint16_t Instr, uint16_t buffer[], uint16_t bufferSize)
{
	if(_Non_Broadcast == _command_type)
	{
		buffer[0] = _MID;
		buffer[1] = ((bufferSize - 2) << 4) + EID;  //Tlen&EID
	}
	else //broadcast command:UID = 0;UID = MID + EID;
	{
		buffer[0] = 0;
		buffer[1] = ((bufferSize - 2) << 4) + 0;  //Tlen&EID
	}
	buffer[2] = Instr;
	buffer[bufferSize - 1] = 0;
	for(uint8_t i = 0; i < bufferSize - 1; i++)
	{
		buffer[bufferSize - 1] += buffer[i];
	}
	buffer[bufferSize - 1] = (~buffer[bufferSize - 1]) & 0x00ff;   //CheckSum = ~(MID + EID&TLen + Instr + Param0 + ...ParamN)
	buffer[0] += 0x0100;  
	
  writeBytes(buffer,bufferSize);
  return true;
}
/********************************************************************
Description: UART writeData
Parameters:      
            wBuf: Used to store received data
            wLen: Length of data to be written
Return:      none      
Others:      
********************************************************************/
void BM92S2021_A:: writeBytes(uint16_t wBuf[],uint8_t wLen)
{
  _theSerial->SetTxStatus(ENABLE);
  _theSerial->SetRxStatus(DISABLE);
  for(uint8_t i = 0; i < wLen; i++)
  {    
    _theSerial->write(wBuf[i]);
    delayMicroseconds(200);
  } 
  _theSerial->flush();
  _theSerial->SetRxStatus(ENABLE);
  _theSerial->SetTxStatus(DISABLE);
}
/********************************************************************
Description: Read data from the module through UART communication
Parameters:  rbuf : Store read data   
Return:      true or false 
Others:      
*********************************************************************/
bool BM92S2021_A::readBytes(uint16_t rbuf[],uint8_t rlen,uint8_t waitTime)
{
  uint8_t i = 0,delayCnt = 0;;
	uint16_t CheckSum = 0;
                               	
  for (i = 0; i < rlen; i++)
  {
    while (_theSerial->available() == 0)
    {
      if (delayCnt > waitTime)
      {
        return false; // Timeout error
      }
      delay(1);
      delayCnt++;
    }
    rbuf[i] = _theSerial->read();
    CheckSum += rbuf[i];
  }
	/*Check sum*/
	CheckSum = CheckSum - rbuf[i - 1] - 0x0100;
	CheckSum = (~CheckSum) & 0x00ff; 
	if(CheckSum != rbuf[i - 1])
	{
		return false;		
	}
 else
  {	
  	_status = rbuf[2];
  	//Received:MID + Tlen&EID + Status + Parm0 + ....ParamN + CheckSum.
  	return true;	
  }
}
