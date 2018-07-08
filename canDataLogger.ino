/*
  CAN-BUS data logger with time stamp on SD card

 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

 created   Feb 2018
 by Farshid Abdollahi
 */
#include <mcp_can.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "RTClib.h"

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

MCP_CAN CAN0(4);                               // Set CS to pin 4
RTC_DS1307 rtc;

void setup()
{
  Serial.begin(115200);
  CAN0.begin(CAN_500KBPS);                       // init can bus : baudrate = 500k 
  pinMode(2, INPUT);                            // Setting pin 2 for /INT input
  Serial.print("Initializing SD card...");
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
  }
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    return;
  }
  // if (! rtc.isrunning()) {
  //   /*Serial.println("RTC is NOT running!");
  //   following line sets the RTC to the date & time this sketch was compiled
  //   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //   This line sets the RTC with an explicit date & time, for example to set
  //   January 21, 2018 at 11:30am you would call:*/
  //   rtc.adjust(DateTime(2018, 1, 21, 11, 30, 00));
  // }
}

void loop()
{
    DateTime now = rtc.now();
    String dataString = "";
    String dateTime = "";
    dateTime += String(now.year(), DEC);
    dateTime += "/";
    dateTime += String(now.month(), DEC);
    dateTime += "/";
    dateTime += String(now.day(), DEC);
    dateTime += " (";
    dateTime += String(daysOfTheWeek[now.dayOfTheWeek()]);
    dateTime += ") ";
    dateTime += String(now.hour(), DEC);
    dateTime += ":";
    dateTime += String(now.minute(), DEC);
    dateTime += ":";
    dateTime += String(now.second(), DEC);
    dateTime += " - ";
    if(!digitalRead(2))                         // If pin 2 is low, read receive buffer
    {
      dataString += "ID: ";
      CAN0.readMsgBuf(&len, rxBuf);              // Read data: len = data length, buf = data byte(s)
      rxId = CAN0.getCanId();                    // Get message ID
      dataString += String(rxId, HEX);
      dataString += " Data: ";
      for(int i = 0; i<len; i++)                // Process each byte of the data
      {
        if(rxBuf[i] < 0x10)                     // If data byte is less than 0x10, add a leading zero
        {
          dataString += "0";
        }
        dataString += String(rxBuf[i], HEX);
        dataString += " ";
      }
      dateTime += dataString;
      File dataFile = SD.open("datalog.txt", FILE_WRITE);
      if (dataFile) {
        dataFile.println(dateTime);
        dataFile.close();
        Serial.println(dateTime);
      } else
      {
        Serial.println("else");
      }
      
    }

}
