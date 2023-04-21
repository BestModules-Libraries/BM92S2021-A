/*****************************************************************
File:             BM92S2021-A.h
Author:           BESTMODULES
Description:      Define classes and required variables
History：         
V1.0.0   -- initial version；2023-01-06；Arduino IDE : v1.8.16
*******************************************************************/
#ifndef _BM92S2021_A_H
#define _BM92S2021_A_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class BM92S2021_A
{
	public:	
	  BM92S2021_A(HardwareSerial *theSerial = &Serial1);
		void begin(uint32_t band = 9600);
		void reset();
    bool reset(uint16_t EID);
		void standby();
		uint16_t getFWVer(uint16_t EID);
	  bool remoteWU(uint16_t EID, uint16_t isEnable);
		bool openLED(uint16_t EID);
		bool closeLED(uint16_t EID);   
		uint16_t getColor(uint16_t EID);
		uint16_t readAmbientLight(uint16_t EID);
		bool readRGBColor(uint16_t EID, uint16_t buffer[]);
    bool setEID(uint16_t EID_Value);
		bool calibrateWhiteBalance(uint16_t EID);
		bool setRemoteWUThre(uint16_t EID, uint16_t LowThre, uint16_t HighThre);
	private:
	    /*System commands are classified into broadcast commands and non-broadcast commands.
 		The UID of broadcast commands is always 0 and is valid for all modules*/
	    typedef enum
		{
			_Broadcast,           //broadcast command
			_Non_Broadcast		
		} CMD_TYPE_t;
		CMD_TYPE_t _command_type = _Non_Broadcast;
		
	    //The MID of this module is factory configured and the value is 0x0016.
	    const uint16_t _MID = 0x0016;
	    /*SYSTEM COMMAND*/
	    const uint16_t _RESET = 0x0000;
		const uint16_t _standby = 0x0001;
		const uint16_t _SYNCACTION = 0x0002;
		const uint16_t _GETFWVER = 0x0003;
		const uint16_t _REMOTEWU = 0x0004;
		const uint16_t _SETEID = 0x0080;
		/*FUNCTION COMMAND*/    
		const uint16_t _OPEN_LED = 0x0009;
		const uint16_t _CLOSE_LED = 0x000A;
		const uint16_t _OPEN_LED_DELAY = 0x0029;
		const uint16_t _CLOSE_LED_DELAY = 0x002A;
		const uint16_t _GET_COLOR = 0x000B;
		const uint16_t _GET_LUM = 0x000C;
		const uint16_t _GET_FULL_COLOR = 0x000D;
		const uint16_t _SET_WB = 0x000E;
		const uint16_t _RemoteWUThre = 0x000F;
		
		HardwareSerial *_theSerial = NULL;  		
		uint16_t _tx_buf[10] = {0};
		uint16_t _rx_buf[10] = {0};
		uint16_t _status = 1;
		uint16_t _DummyRead;
    
    void SyncAction(void);    
    uint16_t openLED_DELAY(uint16_t EID);
    uint16_t closeLED_DELAY(uint16_t EID);
    void writeBytes(uint16_t wBuf[],uint8_t wLen);
    bool readBytes(uint16_t rbuf[],uint8_t rlen,uint8_t waitTime = 10);
    bool sendData( uint16_t EID, uint16_t Instr, uint16_t buffer[], uint16_t bufferSize);

};
#endif
