//03Jan2026
#include <SPI.h>
#include <BuddySuiteESP32C3.h>
#include <./fonts/Open_Sans_Condensed_Italic_19.h>
#include <./fonts/Open_Sans_Italic_23.h> 
#include <./fonts/Open_Sans_Italic_21.h>
#include <./fonts/Roboto_Condensed_Italic_17.h>
#include <./fonts/DSEG14_Modern_Bold_Italic_17.h>  
//For ESP -> ST7789 TFT connections, see "Utils" tab
#include <./overflowJB/Utils.cpp>
#include <./overflowJB/LittleFSManager.cpp>
#include <./overflowJB/JB_Calc.cpp>
//#define INVERT_DISPLAY 0
Utils utils;
JB_Main jbMain;
LittleFSManager littleFS;
JoystickPushSwitchReader jsPushSwitchReader;

void setup() {
  Serial.begin(115200);
  jbMain.initJB();
  jbMain.startJB();
  littleFS.setup();
  jsPushSwitchReader.setup();
}

void loop() 
{	
  jbMain.loop();
}
